#pragma once

#ifdef __RDR__

	#include "RDR/natives32.h"

#else
	#ifdef __GTAV__

		#ifdef __YSC__
			#include "GTAV/natives64.h"
		#else
			#include "GTAV/natives32.h"
		#endif
		
	#endif
#endif