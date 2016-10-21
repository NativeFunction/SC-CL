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

#include "RDRconsts.h"

#else
#ifdef	__GTAV__

#include "GTAVconsts.h"

#endif
#endif