#pragma once

#ifdef __RDR__

	#include "RDR/natives32.h"
	
#elif defined(__GTAV__)

	#ifdef __YSC__
		#include "GTAV/natives64.h"
	#else
		#include "GTAV/natives32.h"
	#endif
	
#elif defined(__GTAIV__)

	#define _NewNatives 1
	
	#if _NewNatives == 1
		#include "GTAIV/natives32.h"//1.0.7.0
	#else
		#include "GTAIV/natives32Old.h"//1.0.4.0
	#endif
	
#endif