#pragma once
#include "types.h"
#define _native __attribute((native))
#define _native32(hash) __attribute((native(hash)))

#ifdef __RDR__

#include "RDR/natives.h"

#else
	
#ifdef __GTAV__

#include "GTAV/natives.h"

#endif
#endif

#undef _native
#undef _native32