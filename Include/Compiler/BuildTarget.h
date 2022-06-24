#pragma once
typedef enum
{
	P_XBOX,
	P_PSX,
	P_PC
} Platform;

typedef enum
{
	BT_GTAIV,
	BT_GTAIV_TLAD,
	BT_GTAIV_TBOGT,
	BT_RDR_XSC,
	BT_RDR_SCO,
	BT_GTAV,
    BT_RDR2
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