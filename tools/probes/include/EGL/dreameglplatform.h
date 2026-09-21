/*
 * Copyright (C) 2017 Dream Property GmbH, Germany
 *                    https://dreambox.de/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __dmeglplatform_h_
#define __dmeglplatform_h_

#include <stdint.h>

struct dmegl_mem_handle {
	unsigned int magic;	/* Must be set to DMEGL_PIXMAP_MAGIC */
	unsigned long length;	/* Length of the allocated memory in bytes */
	unsigned long offset;	/* Offset passed to mmap() or 0 */
	int fd;			/* Mappable file descriptor or -1 */
	uintptr_t phys;		/* Physical address of the allocated memory */
	void *addr;		/* Virtual address of the allocated memory or NULL */
};

#define DMEGL_PIXMAP_MAGIC	0xF1548173U
struct dmegl_pixmap_handle {
	struct dmegl_mem_handle mem;
	unsigned int width;	/* Width in pixels */
	unsigned int height;	/* Height in pixels */
	unsigned int pitch;	/* Pitch in bytes */
	unsigned int format;	/* Pixel format as fourcc code (drm/drm_fourcc.h) */
};

#endif /* __dmeglplatform_h_ */
