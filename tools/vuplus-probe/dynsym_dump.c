/*
 * dynsym_dump - list the dynamic (exported/imported) symbols of an ELF32 shared library, without needing nm/readelf/objdump on the box
 * (several of these boxes have none of the three). Reads the file directly: walks the PT_DYNAMIC program header's tags to find
 * DT_SYMTAB/DT_STRTAB/DT_HASH/DT_GNU_HASH, converts their *virtual* addresses to *file* offsets via the PT_LOAD segments (this is
 * reading the file cold, not a mapped process, so addresses in the dynamic section are not directly usable as file offsets), and prints
 * every symbol name - or, with a filter argument, only names containing it (case-insensitive). Read-only: opens O_RDONLY, never writes.
 *
 *   build (any ARMv7 hf cross compiler): arm-...-gcc -Os -Wall dynsym_dump.c -o dynsym_dump
 *   run:  ./dynsym_dump /usr/lib/libnexus.so [filter-substring]
 */
#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    unsigned char e_ident[16];
    uint16_t e_type, e_machine;
    uint32_t e_version, e_entry, e_phoff, e_shoff, e_flags;
    uint16_t e_ehsize, e_phentsize, e_phnum, e_shentsize, e_shnum, e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    uint32_t p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align;
} Elf32_Phdr;

typedef struct {
    int32_t d_tag;
    uint32_t d_val; /* union with d_ptr in the real ELF spec; only used as an integer/address here */
} Elf32_Dyn;

typedef struct {
    uint32_t st_name;
    uint32_t st_value;
    uint32_t st_size;
    unsigned char st_info, st_other;
    uint16_t st_shndx;
} Elf32_Sym;

#define PT_LOAD 1
#define PT_DYNAMIC 2
#define DT_NULL 0
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_STRSZ 10
#define DT_GNU_HASH 0x6ffffef5

static unsigned char *file_base;
static size_t file_size;
static Elf32_Phdr *phdrs;
static int phnum;

/* the dynamic section's addresses are *virtual*: translate via whichever PT_LOAD segment's vaddr range contains them */
static uint32_t vaddr_to_offset(uint32_t vaddr)
{
    for (int i = 0; i < phnum; i++) {
        if (phdrs[i].p_type == PT_LOAD && vaddr >= phdrs[i].p_vaddr && vaddr < phdrs[i].p_vaddr + phdrs[i].p_filesz)
            return phdrs[i].p_offset + (vaddr - phdrs[i].p_vaddr);
    }
    return 0;
}

static int matches(const char *name, const char *filter)
{
    if (!filter || !*filter)
        return 1;
    size_t i, j, fn = strlen(filter), nn = strlen(name);
    if (fn > nn)
        return 0;
    for (i = 0; i + fn <= nn; i++) {
        for (j = 0; j < fn; j++)
            if (tolower((unsigned char)name[i + j]) != tolower((unsigned char)filter[j]))
                break;
        if (j == fn)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <path-to-.so> [filter-substring]\n", argv[0]);
        return 1;
    }
    const char *path = argv[1];
    const char *filter = argc > 2 ? argv[2] : NULL;

    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        return 1;
    }
    file_size = (size_t)st.st_size;
    file_base = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file_base == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    Elf32_Ehdr *eh = (Elf32_Ehdr *)file_base;
    if (memcmp(eh->e_ident, "\x7f""ELF", 4) != 0 || eh->e_ident[4] != 1 /* ELFCLASS32 */) {
        fprintf(stderr, "not a 32-bit ELF file\n");
        return 1;
    }
    printf("ELF32, machine=%u (40=ARM), type=%u (2=EXEC 3=DYN)\n", eh->e_machine, eh->e_type);

    phdrs = (Elf32_Phdr *)(file_base + eh->e_phoff);
    phnum = eh->e_phnum;

    Elf32_Dyn *dyn = NULL;
    for (int i = 0; i < phnum; i++) {
        if (phdrs[i].p_type == PT_DYNAMIC) {
            dyn = (Elf32_Dyn *)(file_base + phdrs[i].p_offset);
            break;
        }
    }
    if (!dyn) {
        fprintf(stderr, "no PT_DYNAMIC segment (not a shared object / static binary?)\n");
        return 1;
    }

    uint32_t symtab_vaddr = 0, strtab_vaddr = 0, hash_vaddr = 0, gnu_hash_vaddr = 0, strsz = 0;
    for (Elf32_Dyn *d = dyn; d->d_tag != DT_NULL; d++) {
        switch (d->d_tag) {
        case DT_SYMTAB: symtab_vaddr = d->d_val; break;
        case DT_STRTAB: strtab_vaddr = d->d_val; break;
        case DT_HASH: hash_vaddr = d->d_val; break;
        case DT_GNU_HASH: gnu_hash_vaddr = d->d_val; break;
        case DT_STRSZ: strsz = d->d_val; break;
        }
    }
    if (!symtab_vaddr || !strtab_vaddr) {
        fprintf(stderr, "no DT_SYMTAB/DT_STRTAB in the dynamic section\n");
        return 1;
    }
    uint32_t symtab_off = vaddr_to_offset(symtab_vaddr);
    uint32_t strtab_off = vaddr_to_offset(strtab_vaddr);
    if (!symtab_off || !strtab_off) {
        fprintf(stderr, "could not translate DT_SYMTAB/DT_STRTAB virtual address to a file offset\n");
        return 1;
    }
    Elf32_Sym *symtab = (Elf32_Sym *)(file_base + symtab_off);
    const char *strtab = (const char *)(file_base + strtab_off);

    /* how many entries does .dynsym have? old-style DT_HASH's header is [nbucket, nchain] and nchain == symbol count (every symbol,
     * defined or not, gets a hash chain slot) - the traditional, reliable way to get this without section headers. GNU hash tables
     * (DT_GNU_HASH) do not directly give a full count the same way; fall back to scanning until strtab/file bounds if only that is
     * present (approximate but safe: stop at the first entry whose name pointer is out of range). */
    unsigned nsyms = 0;
    if (hash_vaddr) {
        uint32_t hash_off = vaddr_to_offset(hash_vaddr);
        if (hash_off && hash_off + 8 <= file_size) {
            uint32_t *h = (uint32_t *)(file_base + hash_off);
            nsyms = h[1]; /* nchain */
        }
    }
    if (!nsyms) {
        /* Fallback: walk until a symbol's name offset is clearly bogus, or we run off the mapped file. Cap generously. */
        for (unsigned i = 0; i < 200000; i++) {
            if (symtab_off + (i + 1) * sizeof(Elf32_Sym) > file_size)
                break;
            if (symtab[i].st_name >= strsz && strsz)
                break;
            nsyms = i + 1;
        }
        printf("(no DT_HASH; estimated %u symbols by scanning until an out-of-range name offset)\n", nsyms);
    }

    printf("%u dynamic symbols%s%s:\n", nsyms, filter ? ", filtered by \"" : "", filter ? filter : "");
    unsigned shown = 0;
    for (unsigned i = 0; i < nsyms; i++) {
        if (symtab_off + (i + 1) * sizeof(Elf32_Sym) > file_size)
            break;
        uint32_t nameoff = symtab[i].st_name;
        if (strsz && nameoff >= strsz)
            continue;
        if (strtab_off + nameoff >= file_size)
            continue;
        const char *name = strtab + nameoff;
        if (!*name)
            continue;
        if (!matches(name, filter))
            continue;
        printf("  %-50s value=0x%08x size=%u shndx=%u\n", name, symtab[i].st_value, symtab[i].st_size, symtab[i].st_shndx);
        shown++;
    }
    printf("(%u shown)\n", shown);
    return 0;
}
