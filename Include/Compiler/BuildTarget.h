#pragma once
typedef enum
{
	P_X360,
	P_PS3,
	P_PC
} Platform;

typedef enum
{
	BT_GTAIV,
	BT_GTAIV_TLAD,
	BT_GTAIV_TBOGT,
	BT_RDR_XSC,
	BT_RDR_SCO,
	BT_GTAV
} BuildType;

typedef enum
{
	END_BIG,
	END_LITTLE
} Endian;

typedef enum OptimisationLevel
{
	OL_None,
	OL_Trivial,
	OL_Normal,
	OL_Full
} OptimisationLevel;

typedef enum GTAIVSCRFlags
{
    SCRF_CompressedEncrypted,
    SCRF_Standard,
    SCRF_Encrypted
} GTAIVSCRFlags;