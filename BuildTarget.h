#pragma once
typedef enum Platform
{
	P_XBOX,
	P_PS3,
	P_PC
} Platform;

typedef enum BuildType
{
	BT_GTAIV,
	BT_RDR_XSC,
	BT_RDR_SCO,
	BT_GTAV
} BuildType;

typedef enum Endian
{
	END_BIG,
	END_LITTLE
} Endian;