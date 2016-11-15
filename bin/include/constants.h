#pragma once

#define TRUE 1
#define FALSE 0
#define true 1
#define false 0
#define NULL 0
#define null 0
#define nullptr 0

#define PI 3.14159265

#ifdef __RDR__

#include "RDR/consts32.h"

#else
	#ifdef	__GTAV__
		#include "GTAV/constsShared.h"
		
		#ifdef __YSC__
			#include "GTAV/consts64.h"
		#else
			#include "GTAV/consts32.h"
		#endif
		
	#endif
#endif