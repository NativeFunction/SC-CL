#pragma once

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define NULL 0
#define null 0
#define nullptr 0
#define nullstr ""

#define PI 3.14159265

#if TARGET == TARGET_RDR

#include "RDR/consts32.h"

#elif TARGET == TARGET_GTAV
	#include "GTAV/constsShared.h"

	#if PLATFORM == PLATFORM_PC
		#include "GTAV/consts64.h"
	#else
		#include "GTAV/consts32.h"
	#endif

#elif TARGET == TARGET_GTAIV
	#include "GTAIV/consts32.h"
#endif