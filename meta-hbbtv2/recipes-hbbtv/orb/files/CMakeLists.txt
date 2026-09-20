# Build of the ORB (Open Red Button) engine for an enigma2 box, and of the pieces that connect it to WPE WebKit:
#
#   libORBCore      ORB engine, request handlers and application manager (sources of the ORB tree, RDK flavour)
#   libORBHost      C interface for an embedder that hosts the engine in-process (orb_host.cpp)
#   libORBPlatformImpl.so   ORBPlatform implementation the engine loads with dlopen (ORB's platform mock + orb_platform_wpe.cpp)
#   libORBWebExt.so         WPE web process extension: the bridge between the polyfill and the engine (orb_ext.c)
#
# ORB's own rdk/ORB/library/CMakeLists.txt is not used: it lacks ORB_HBBTV_VERSION and the compatibility header for the application
# manager, has no host and needs its bundled libxml2/curl/jsoncpp checkouts.
cmake_minimum_required(VERSION 3.10)
project(orb-hbbtv2 C CXX)

set(ORB_SRC "" CACHE PATH "the OpenRedButtonProject/orb source tree")
if(NOT ORB_SRC)
    message(FATAL_ERROR "set ORB_SRC to the orb source tree")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(XML2 REQUIRED IMPORTED_TARGET libxml-2.0)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)
pkg_check_modules(UUID REQUIRED IMPORTED_TARGET uuid)
pkg_check_modules(WPE REQUIRED IMPORTED_TARGET wpe-webkit-2.0 wpe-platform-2.0 gmodule-2.0)

set(ORB_LIB ${ORB_SRC}/rdk/ORB/library)
set(ORB_MOCK ${ORB_SRC}/rdk/ORB/platform-mock)
set(ORB_APPMGR ${ORB_SRC}/components/application_manager)

set(ORB_DEFINITIONS RDK ANDROID_DEBUG ORB_HBBTV_VERSION=203)
set(ORB_INCLUDES
    ${ORB_LIB}/src
    ${ORB_LIB}/src/core
    ${ORB_LIB}/src/core/api
    ${ORB_LIB}/src/core/dataTypes
    ${ORB_LIB}/src/core/requestHandlers
    ${ORB_LIB}/src/core/utilities
    ${ORB_LIB}/src/platform
    ${ORB_LIB}/src/platform/dataTypes
    ${ORB_LIB}/src/thirdparty
    ${ORB_LIB}/src/thirdparty/nlohmann
    ${ORB_APPMGR})
set(ORB_COMPAT ${CMAKE_CURRENT_SOURCE_DIR}/orb_compat.h)

# ORB is C++14 code (it also needs <cstdint> in every file, which newer compilers no longer pull in)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:SHELL:-include cstdint>" -Wno-deprecated-declarations)

# ---- libORBCore ----
file(GLOB CORE_SOURCES
    ${ORB_LIB}/src/core/*.cpp
    ${ORB_LIB}/src/core/dataTypes/*.cpp
    ${ORB_LIB}/src/core/requestHandlers/*.cpp
    ${ORB_LIB}/src/core/utilities/*.cpp)
set(APPMGR_SOURCES
    ${ORB_APPMGR}/ait.cpp
    ${ORB_APPMGR}/app.cpp
    ${ORB_APPMGR}/application_manager.cpp
    ${ORB_APPMGR}/utils.cpp
    ${ORB_APPMGR}/xml_parser.cpp)
# application_manager/log.h only defines DBGLOG/ERRLOG for Android, but the sources use them
set_source_files_properties(${APPMGR_SOURCES} PROPERTIES COMPILE_OPTIONS "SHELL:-include ${ORB_COMPAT}")

add_library(ORBCore SHARED ${CORE_SOURCES} ${APPMGR_SOURCES})
target_compile_definitions(ORBCore PRIVATE ${ORB_DEFINITIONS})
target_include_directories(ORBCore PRIVATE ${ORB_INCLUDES})
target_link_libraries(ORBCore PRIVATE PkgConfig::XML2 PkgConfig::CURL PkgConfig::UUID dl)
set_target_properties(ORBCore PROPERTIES VERSION 1.0.0 SOVERSION 1)

# ---- libORBHost ----
add_library(ORBHost SHARED orb_host.cpp)
target_compile_definitions(ORBHost PRIVATE ${ORB_DEFINITIONS})
target_include_directories(ORBHost PRIVATE ${ORB_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ORBHost PRIVATE ORBCore PkgConfig::XML2 PkgConfig::CURL pthread)
set_target_properties(ORBHost PROPERTIES VERSION 1.0.0 SOVERSION 1)

# ---- libORBPlatformImpl.so (dlopen'ed by the engine; ORB_PLATFORM_LIB names it) ----
# orb_platform_wpe.cpp comes first and overrides members of the mock implementation that the mock also defines (--allow-multiple-definition
# keeps the first). Its references to the host (orb_host_platform_*) and to the engine resolve in the embedder process at load time.
add_library(ORBPlatformImpl MODULE
    orb_platform_wpe.cpp
    ${ORB_MOCK}/src/DVB.cpp
    ${ORB_MOCK}/src/ORBPlatformMockImpl.cpp
    mock_fix.cpp)
target_compile_definitions(ORBPlatformImpl PRIVATE ${ORB_DEFINITIONS})
target_compile_options(ORBPlatformImpl PRIVATE "SHELL:-include ${ORB_COMPAT}")
target_include_directories(ORBPlatformImpl PRIVATE
    ${ORB_LIB}/src/platform ${ORB_LIB}/src/platform/dataTypes ${ORB_MOCK}/src ${ORB_LIB}/src/thirdparty ${ORB_LIB}/src/thirdparty/nlohmann
    ${CMAKE_CURRENT_SOURCE_DIR})
target_link_options(ORBPlatformImpl PRIVATE -Wl,--allow-multiple-definition -Wl,--allow-shlib-undefined)

# ---- libORBWebExt.so (loaded by the WPE web process) ----
add_library(ORBWebExt MODULE orb_ext.c)
set_target_properties(ORBWebExt PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
target_compile_options(ORBWebExt PRIVATE -Wall)
target_link_libraries(ORBWebExt PRIVATE PkgConfig::WPE)

include(GNUInstallDirs)
install(TARGETS ORBCore ORBHost LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ORBPlatformImpl LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/orb/wpe)
install(TARGETS ORBWebExt LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/orb/ext)
install(FILES orb_host.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/orb)
