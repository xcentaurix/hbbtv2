/*
 * mock_fix.cpp - ORB's platform-mock declares ORBPlatformMockImpl::Network_ResolveNetworkError() (it is a pure
 * virtual in ORBPlatform.h) but never defines it, so libORBPlatformImpl.so cannot be dlopen()ed: the vtable refers
 * to an undefined symbol. Provide it here.
 *
 * Contract: map the status text of a failed network response to the DVB-DASH error code string. The mock has no
 * network stack, so it returns an empty string ("unknown"). A real platform layer needs a real mapping.
 */
#include "ORBPlatformMockImpl.h"

std::string ORBPlatformMockImpl::Network_ResolveNetworkError(std::string responseText)
{
    (void)responseText;
    return std::string();
}
