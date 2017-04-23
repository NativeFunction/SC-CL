#pragma once

#if TARGET == TARGET_RDR

#include "RDR/natives32.h"

#elif TARGET == TARGET_GTAV

#if PTRWIDTH == 64
#include "GTAV/natives64.h"
#else
#include "GTAV/natives32.h"
#endif

#elif TARGET == TARGET_GTAIV

#if PLATFORM == PLATFORM_X360 || PLATFORM_PS3
#include "GTAIV/natives32Old.h"//1.0.4.0
#else
#include "GTAIV/natives32.h"//1.0.7.0
#endif

#endif