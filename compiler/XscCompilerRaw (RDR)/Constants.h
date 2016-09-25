#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


#define STACK_OP_Add 2
#define STACK_OP_Sub 2
#define STACK_OP_Mult 2
#define STACK_OP_Div 2
#define STACK_OP_Mod 2
#define STACK_OP_Not 1
#define STACK_OP_Neg 1
#define STACK_OP_CmpEQ 2
#define STACK_OP_CmpNE 2
#define STACK_OP_CmpGT 2
#define STACK_OP_CmpGE 2
#define STACK_OP_CmpLT 2
#define STACK_OP_CmpLE 2
#define STACK_OP_fAdd 2
#define STACK_OP_fSub 2
#define STACK_OP_fMult 2
#define STACK_OP_fDiv 2
#define STACK_OP_fMod 2
#define STACK_OP_fNeg 1
#define STACK_OP_fCmpEQ 2
#define STACK_OP_fCmpNE 2
#define STACK_OP_fCmpGT 2
#define STACK_OP_fCmpGE 2
#define STACK_OP_fCmpLT 2
#define STACK_OP_fCmpLE 2
#define STACK_OP_vAdd 6
#define STACK_OP_vSub 6
#define STACK_OP_vMult 6
#define STACK_OP_vDiv 6
#define STACK_OP_vNeg 3
#define STACK_OP_And 2
#define STACK_OP_Or 2
#define STACK_OP_Xor 2
#define STACK_OP_ItoF 1
#define STACK_OP_FtoI 1
#define STACK_OP_FtoV 1
#define STACK_OP_Dup 1
#define STACK_OP_Drop 1
#define STACK_OP_pGet 1
#define STACK_OP_pSet 2
#define STACK_OP_pPeekSet 2
#define STACK_OP_GetArrayP1 2
#define STACK_OP_GetArray1 2
#define STACK_OP_SetArray1 3
#define STACK_OP_SetFrame1 1
#define STACK_OP_SetStatic1 1
#define STACK_OP_Add1 1
#define STACK_OP_GetImm1 1
#define STACK_OP_SetImm1 2
#define STACK_OP_Mult1 1
#define STACK_OP_Add2 1
#define STACK_OP_GetImm2 1
#define STACK_OP_SetImm2 2
#define STACK_OP_Mult2 1
#define STACK_OP_GetArrayP2 2
#define STACK_OP_GetArray2 2
#define STACK_OP_SetArray2 3
#define STACK_OP_SetFrame2 1
#define STACK_OP_SetStatic2 1
#define STACK_OP_SetGlobal2 1
#define STACK_OP_JumpFalse 1
#define STACK_OP_JumpNE 2
#define STACK_OP_JumpEQ 2
#define STACK_OP_JumpLE 2
#define STACK_OP_JumpLT 2
#define STACK_OP_JumpGE 2
#define STACK_OP_JumpGT 2
#define STACK_OP_SetGlobal3 1
#define STACK_OP_StrCopy 2
#define STACK_OP_ItoS 2
#define STACK_OP_StrAdd 2
#define STACK_OP_StrAddI 2
#define STACK_OP_MemCopy 3
#define STACK_OP_FromStack 2
#define STACK_OP_ToStack 2

#define Nop_L 1
#define Add_L 1
#define Sub_L 1
#define Mult_L 1
#define Div_L 1
#define Mod_L 1
#define Not_L 1
#define Neg_L 1
#define CmpEQ_L 1
#define CmpNE_L 1
#define CmpGT_L 1
#define CmpGE_L 1
#define CmpLT_L 1
#define CmpLE_L 1
#define fAdd_L 1
#define fSub_L 1
#define fMult_L 1
#define fDiv_L 1
#define fMod_L 1
#define fNeg_L 1
#define fCmpEQ_L 1
#define fCmpNE_L 1
#define fCmpGT_L 1
#define fCmpGE_L 1
#define fCmpLT_L 1
#define fCmpLE_L 1
#define vAdd_L 1
#define vSub_L 1
#define vMult_L 1
#define vDiv_L 1
#define vNeg_L 1
#define And_L 1
#define Or_L 1
#define Xor_L 1
#define ItoF_L 1
#define FtoI_L 1
#define FtoV_L 1
#define Dup_L 1
#define Drop_L 1
#define pGet_L 1
#define pSet_L 1
#define pPeekSet_L 1
#define ToStack_L 1
#define FromStack_L 1
#define GetImmP_L 1
#define PushString_L 2
#define PushArrayP_L 5
#define GetHash_L 1
#define MemCopy_L 1
#define Catch_L 1
#define Throw_L 1
#define pCall_L 1
#define Push_Neg1_L 1
#define Push_0_L 1
#define Push_1_L 1
#define Push_2_L 1
#define Push_3_L 1
#define Push_4_L 1
#define Push_5_L 1
#define Push_6_L 1
#define Push_7_L 1
#define PushF_Neg1_L 1
#define PushF_0_L 1
#define PushF_1_L 1
#define PushF_2_L 1
#define PushF_3_L 1
#define PushF_4_L 1
#define PushF_5_L 1
#define PushF_6_L 1
#define PushF_7_L 1
#define PushB_L 2
#define GetArrayP1_L 2
#define GetArray1_L 2
#define SetArray1_L 2
#define GetFrameP1_L 2
#define GetFrame1_L 2
#define SetFrame1_L 2
#define GetStaticP1_L 2
#define GetStatic1_L 2
#define SetStatic1_L 2
#define Add1_L 2
#define Mult1_L 2
#define GetImm1_L 2
#define SetImm1_L 2
#define StrCopy_L 2
#define ItoS_L 2
#define StrAdd_L 2
#define StrAddI_L 2
#define PushB2_L 3
#define Return_L 3
#define PushS_L 3
#define Add2_L 3
#define Mult2_L 3
#define GetImm2_L 3
#define SetImm2_L 3
#define GetArrayP2_L 3
#define GetArray2_L 3
#define SetArray2_L 3
#define GetFrameP2_L 3
#define GetFrame2_L 3
#define SetFrame2_L 3
#define GetStaticP2_L 3
#define GetStatic2_L 3
#define SetStatic2_L 3
#define GetGlobalP2_L 3
#define GetGlobal2_L 3
#define SetGlobal2_L 3
#define Jump_L 3
#define JumpFalse_L 3
#define JumpEQ_L 3
#define JumpNE_L 3
#define JumpGE_L 3
#define JumpGT_L 3
#define JumpLE_L 3
#define JumpLT_L 3
#define CallNative_L 3
#define Call_L 3
#define PushB3_L 4
#define GetGlobalP3_L 4
#define GetGlobal3_L 4
#define SetGlobal3_L 4
#define PushI24_L 4
#define Push_L 5
#define PushF_L 5



#define RSC85_Flags_ReadBuffer4096 0x80 //100000000000
#define RSC85_Flags_ReadBuffer65536 0xC0//110000000000
#define RSC85_Flags_ReadBuffer16384 0xA0//101000000000
#define RSC85_Flags_ReadBuffer8192 0x90 //100100000000

#define RSC85_Flags_ReadBuffer4096_32 0x80000000 //100000000000
#define RSC85_Flags_ReadBuffer65536_32 0xC0000000    //110000000000
#define RSC85_Flags_ReadBuffer16384_32 0xA0000000//101000000000
#define RSC85_Flags_ReadBuffer8192_32 0x90000000 //100100000000


namespace Constants
{

    const int XboxPageSize = 16384;
    const int XboxBaseSize = 8192;
    const int PS3BaseSize = 4096;

    enum Platform
    {
        Xbox = 8192,
        PS3 = 4096
    };
    enum OpCode : uint8_t
    {
        OP_Nop,
        OP_Add,
        OP_Sub,
        OP_Mult,
        OP_Div,
        OP_Mod,
        OP_Not,
        OP_Neg,
        OP_CmpEQ,
        OP_CmpNE,
        OP_CmpGT,
        OP_CmpGE,
        OP_CmpLT,
        OP_CmpLE,
        OP_fAdd,
        OP_fSub,
        OP_fMult,
        OP_fDiv,
        OP_fMod,
        OP_fNeg,
        OP_fCmpEQ,
        OP_fCmpNE,
        OP_fCmpGT,
        OP_fCmpGE,
        OP_fCmpLT,
        OP_fCmpLE,
        OP_vAdd,
        OP_vSub,
        OP_vMult,
        OP_vDiv,
        OP_vNeg,
        OP_And,
        OP_Or,
        OP_Xor,
        OP_ItoF,
        OP_FtoI,
        OP_FtoV,
        OP_PushB,
        OP_PushB2,
        OP_PushB3,
        OP_Push,
        OP_PushF,
        OP_Dup,
        OP_Drop,
        OP_CallNative,
        OP_Function,
        OP_Return,
        OP_pGet,
        OP_pSet,
        OP_pPeekSet,
        OP_ToStack,
        OP_FromStack,
        OP_GetArrayP1,
        OP_GetArray1,
        OP_SetArray1,
        OP_GetFrameP1,
        OP_GetFrame1,
        OP_SetFrame1,
        OP_GetStaticP1,
        OP_GetStatic1,
        OP_SetStatic1,
        OP_Add1,
        OP_GetImm1,
        OP_SetImm1,
        OP_Mult1,
        OP_PushS,
        OP_Add2,
        OP_GetImm2,
        OP_SetImm2,
        OP_Mult2,
        OP_GetArrayP2,
        OP_GetArray2,
        OP_SetArray2,
        OP_GetFrameP2,
        OP_GetFrame2,
        OP_SetFrame2,
        OP_GetStaticP2,
        OP_GetStatic2,
        OP_SetStatic2,
        OP_GetGlobalP2,
        OP_GetGlobal2,
        OP_SetGlobal2,
        OP_Call2,
        OP_Call2h1,
        OP_Call2h2,
        OP_Call2h3,
        OP_Call2h4,
        OP_Call2h5,
        OP_Call2h6,
        OP_Call2h7,
        OP_Call2h8,
        OP_Call2h9,
        OP_Call2hA,
        OP_Call2hB,
        OP_Call2hC,
        OP_Call2hD,
        OP_Call2hE,
        OP_Call2hF,
        OP_Jump,
        OP_JumpFalse,
        OP_JumpNE,
        OP_JumpEQ,
        OP_JumpLE,
        OP_JumpLT,
        OP_JumpGE,
        OP_JumpGT,
        OP_GetGlobalP3,
        OP_GetGlobal3,
        OP_SetGlobal3,
        OP_PushI24,
        OP_Switch,
        OP_PushString,
        OP_PushArrayP,
        OP_PushStringNull,
        OP_StrCopy,
        OP_ItoS,
        OP_StrAdd,
        OP_StrAddI,
        OP_MemCopy,
        OP_Catch,
        OP_Throw,
        OP_pCall,
        OP_ReturnP0R0,
        OP_ReturnP0R1,
        OP_ReturnP0R2,
        OP_ReturnP0R3,
        OP_ReturnP1R0,
        OP_ReturnP1R1,
        OP_ReturnP1R2,
        OP_ReturnP1R3,
        OP_ReturnP2R0,
        OP_ReturnP2R1,
        OP_ReturnP2R2,
        OP_ReturnP2R3,
        OP_ReturnP3R0,
        OP_ReturnP3R1,
        OP_ReturnP3R2,
        OP_ReturnP3R3,
        OP_Push_Neg1,
        OP_Push_0,
        OP_Push_1,
        OP_Push_2,
        OP_Push_3,
        OP_Push_4,
        OP_Push_5,
        OP_Push_6,
        OP_Push_7,
        OP_PushF_Neg1,
        OP_PushF_0,
        OP_PushF_1,
        OP_PushF_2,
        OP_PushF_3,
        OP_PushF_4,
        OP_PushF_5,
        OP_PushF_6,
        OP_PushF_7

    };

    enum CustomOpCodes
    {
        JumpTrue
    };
    enum DataTableType
    {
        CODE,
        STRING
    };
    enum EnumType
    {
        Int,
        Float,
        String
    };
    enum DecompileType : uint8_t
    {
        Type_None = 0,
        DecompileStrings = 1,
        OutputNativeHashes = 2
    };
    enum DecompileFlag
    {
        None = 0,
        ShowPC = 1,
        ShowCallPosition = 2,
        ShowJumpPosition = 4,
        ShowNativeInfo = 8,
        ShowStringsPC = 16
    };

}
#endif // CONSTANTS_H_INCLUDED
