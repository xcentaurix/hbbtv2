/*
 * orb_compat.h - force-included (-include) when building ORB's application manager outside RDK/Android.
 *
 * components/application_manager/log.h only defines DBGLOG/ERRLOG in its ANDROID branch (its RDK branch defines
 * LOG() but not these), yet application_manager.cpp uses them. Provide simple stderr versions.
 */
#pragma once
#include <stdio.h>

#ifndef DBGLOG
#define DBGLOG(x, ...) fprintf(stderr, "[ORB/AppMgr] %s:%u " x "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif
#ifndef ERRLOG
#define ERRLOG(x, ...) fprintf(stderr, "[ORB/AppMgr][ERROR] %s:%u " x "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif
