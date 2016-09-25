#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

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
#define IToF_L 1
#define FToI_L 1
#define FToV_L 1
#define Dup_L 1
#define Drop_L 1
#define pGet_L 1
#define pSet_L 1
#define pPeekSet_L 1
#define ToStack_L 1
#define FromStack_L 1
#define GetImmP_L 1
#define PushString_L 1
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
#define GetImmP1_L 2
#define GetImm1_L 2
#define SetImm1_L 2
#define StrCopy_L 2
#define IToS_L 2
#define StrAdd_L 2
#define StrAddI_L 2
#define PushB2_L 3
#define Return_L 3
#define PushS_L 3
#define Add2_L 3
#define Mult2_L 3
#define GetImmP2_L 3
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
#define PushB3_L 4
#define CallNative_L 4
#define Call_L 4
#define GetGlobalP3_L 4
#define GetGlobal3_L 4
#define SetGlobal3_L 4
#define PushI24_L 4
#define Push_L 5
#define PushF_L 5

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
        Nop,
        Add,
        Sub,
        Mult,
        Div,
        Mod,
        Not,
        Neg,
        CmpEQ,
        CmpNE,
        CmpGT,
        CmpGE,
        CmpLT,
        CmpLE,
        fAdd,
        fSub,
        fMult,
        fDiv,
        fMod,
        fNeg,
        fCmpEQ,
        fCmpNE,
        fCmpGT,
        fCmpGE,
        fCmpLT,
        fCmpLE,
        vAdd,
        vSub,
        vMult,
        vDiv,
        vNeg,
        And,
        Or,
        Xor,
        IToF,
        FToI,
        FToV,
        PushB,
        PushB2,
        PushB3,
        Push,
        PushF,
        Dup,
        Drop,
        CallNative,
        Function,
        Return,
        pGet,
        pSet,
        pPeekSet,
        ToStack,
        FromStack,
        GetArrayP1,
        GetArray1,
        SetArray1,
        GetFrameP1,
        GetFrame1,
        SetFrame1,
        GetStaticP1,
        GetStatic1,
        SetStatic1,
        Add1,
        Mult1,
        GetImmP,
        GetImmP1,
        GetImm1,
        SetImm1,
        PushS,
        Add2,
        Mult2,
        GetImmP2,
        GetImm2,
        SetImm2,
        GetArrayP2,
        GetArray2,
        SetArray2,
        GetFrameP2,
        GetFrame2,
        SetFrame2,
        GetStaticP2,
        GetStatic2,
        SetStatic2,
        GetGlobalP2,
        GetGlobal2,
        SetGlobal2,
        Jump,
        JumpFalse,
        JumpNE,
        JumpEQ,
        JumpLE,
        JumpLT,
        JumpGE,
        JumpGT,
        Call,
        GetGlobalP3,
        GetGlobal3,
        SetGlobal3,
        PushI24,
        Switch,
        PushString,
        GetHash,
        StrCopy,
        IToS,
        StrAdd,
        StrAddI,
        MemCopy,
        Catch,
        Throw,
        pCall,
        Push_Neg1,
        Push_0,
        Push_1,
        Push_2,
        Push_3,
        Push_4,
        Push_5,
        Push_6,
        Push_7,
        PushF_Neg1,
        PushF_0,
        PushF_1,
        PushF_2,
        PushF_3,
        PushF_4,
        PushF_5,
        PushF_6,
        PushF_7
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
