#pragma once
#include <stdint.h>

enum RDR_Opcodes : uint8_t
{
	  RO_Nop = 0
	, RO_Add = 1
	, RO_Sub = 2
	, RO_Mult = 3
	, RO_Div = 4
	, RO_Mod = 5
	, RO_Not = 6
	, RO_Neg = 7
	, RO_CmpEq = 8
	, RO_CmpNe = 9
	, RO_CmpGt = 10
	, RO_CmpGe = 11
	, RO_CmpLt = 12
	, RO_CmpLe = 13
	, RO_fAdd = 14
	, RO_fSub = 15
	, RO_fMult = 16
	, RO_fDiv = 17
	, RO_fMod = 18
	, RO_fNeg = 19
	, RO_fCmpEq = 20
	, RO_fCmpNe = 21
	, RO_fCmpGt = 22
	, RO_fCmpGe = 23
	, RO_fCmpLt = 24
	, RO_fCmpLe = 25
	, RO_vAdd = 26
	, RO_vSub = 27
	, RO_vMult = 28
	, RO_vDiv = 29
	, RO_vNeg = 30
	, RO_And = 31
	, RO_Or = 32
	, RO_Xor = 33
	, RO_ItoF = 34
	, RO_FtoI = 35
	, RO_FtoV = 36
	, RO_PushB = 37
	, RO_PushB2 = 38
	, RO_PushB3 = 39
	, RO_Push = 40
	, RO_PushF = 41
	, RO_Dup = 42
	, RO_Drop = 43
	, RO_CallNative = 44
	, RO_Function = 45
	, RO_Return = 46
	, RO_pGet = 47
	, RO_pSet = 48
	, RO_pPeekSet = 49
	, RO_ToStack = 50
	, RO_FromStack = 51
	, RO_GetArrayP1 = 52
	, RO_GetArray1 = 53
	, RO_SetArray1 = 54
	, RO_GetFrameP1 = 55
	, RO_GetFrame1 = 56
	, RO_SetFrame1 = 57
	, RO_GetStaticP1 = 58
	, RO_GetStatic1 = 59
	, RO_SetStatic1 = 60
	, RO_Add1 = 61
	, RO_GetImm1 = 62
	, RO_SetImm1 = 63
	, RO_Mult1 = 64
	, RO_PushS = 65
	, RO_Add2 = 66
	, RO_GetImm2 = 67
	, RO_SetImm2 = 68
	, RO_Mult2 = 69
	, RO_GetArrayP2 = 70
	, RO_GetArray2 = 71
	, RO_SetArray2 = 72
	, RO_GetFrameP2 = 73
	, RO_GetFrame2 = 74
	, RO_SetFrame2 = 75
	, RO_GetStaticP2 = 76
	, RO_GetStatic2 = 77
	, RO_SetStatic2 = 78
	, RO_GetGlobalP2 = 79
	, RO_GetGlobal2 = 80
	, RO_SetGlobal2 = 81
	, RO_Call2 = 82
	, RO_Call2h1 = 83
	, RO_Call2h2 = 84
	, RO_Call2h3 = 85
	, RO_Call2h4 = 86
	, RO_Call2h5 = 87
	, RO_Call2h6 = 88
	, RO_Call2h7 = 89
	, RO_Call2h8 = 90
	, RO_Call2h9 = 91
	, RO_Call2hA = 92
	, RO_Call2hB = 93
	, RO_Call2hC = 94
	, RO_Call2hD = 95
	, RO_Call2hE = 96
	, RO_Call2hF = 97
	, RO_Jump = 98
	, RO_JumpFalse = 99
	, RO_JumpNE = 100
	, RO_JumpEQ = 101
	, RO_JumpLE = 102
	, RO_JumpLT = 103
	, RO_JumpGE = 104
	, RO_JumpGT = 105
	, RO_GetGlobalP3 = 106
	, RO_GetGlobal3 = 107
	, RO_SetGlobal3 = 108
	, RO_PushI24 = 109
	, RO_Switch = 110
	, RO_PushString = 111
	, RO_PushArrayP = 112
	, RO_PushStringNull = 113
	, RO_StrCopy = 114
	, RO_ItoS = 115
	, RO_StrAdd = 116
	, RO_StrAddi = 117
	, RO_MemCopy = 118
	, RO_Catch = 119
	, RO_Throw = 120
	, RO_pCall = 121
	, RO_ReturnP0R0 = 122
	, RO_ReturnP0R1 = 123
	, RO_ReturnP0R2 = 124
	, RO_ReturnP0R3 = 125
	, RO_ReturnP1R0 = 126
	, RO_ReturnP1R1 = 127
	, RO_ReturnP1R2 = 128
	, RO_ReturnP1R3 = 129
	, RO_ReturnP2R0 = 130
	, RO_ReturnP2R1 = 131
	, RO_ReturnP2R2 = 132
	, RO_ReturnP2R3 = 133
	, RO_ReturnP3R0 = 134
	, RO_ReturnP3R1 = 135
	, RO_ReturnP3R2 = 136
	, RO_ReturnP3R3 = 137
	, RO_Push_Neg1 = 138
	, RO_Push_0 = 139
	, RO_Push_1 = 140
	, RO_Push_2 = 141
	, RO_Push_3 = 142
	, RO_Push_4 = 143
	, RO_Push_5 = 144
	, RO_Push_6 = 145
	, RO_Push_7 = 146
	, RO_PushF_Neg1 = 147
	, RO_PushF_0 = 148
	, RO_PushF_1 = 149
	, RO_PushF_2 = 150
	, RO_PushF_3 = 151
	, RO_PushF_4 = 152
	, RO_PushF_5 = 153
	, RO_PushF_6 = 154
	, RO_PushF_7 = 155
};

enum GTAV_Opcodes : uint8_t
{
	  VO_Nop = 0
	, VO_Add = 1
	, VO_Sub = 2
	, VO_Mult = 3
	, VO_Div = 4
	, VO_Mod = 5
	, VO_Not = 6
	, VO_Neg = 7
	, VO_CmpEq = 8
	, VO_CmpNe = 9
	, VO_CmpGt = 10
	, VO_CmpGe = 11
	, VO_CmpLt = 12
	, VO_CmpLe = 13
	, VO_fAdd = 14
	, VO_fSub = 15
	, VO_fMult = 16
	, VO_fDiv = 17
	, VO_fMod = 18
	, VO_fNeg = 19
	, VO_fCmpEq = 20
	, VO_fCmpNe = 21
	, VO_fCmpGt = 22
	, VO_fCmpGe = 23
	, VO_fCmpLt = 24
	, VO_fCmpLe = 25
	, VO_vAdd = 26
	, VO_vSub = 27
	, VO_vMult = 28
	, VO_vDiv = 29
	, VO_vNeg = 30
	, VO_And = 31
	, VO_Or = 32
	, VO_Xor = 33
	, VO_ItoF = 34
	, VO_FtoI = 35
	, VO_FtoV = 36
	, VO_PushB = 37
	, VO_PushB2 = 38
	, VO_PushB3 = 39
	, VO_Push = 40
	, VO_PushF = 41
	, VO_Dup = 42
	, VO_Drop = 43
	, VO_CallNative = 44
	, VO_Function = 45
	, VO_Return = 46
	, VO_pGet = 47
	, VO_pSet = 48
	, VO_pPeekSet = 49
	, VO_ToStack = 50
	, VO_FromStack = 51
	, VO_GetArrayP1 = 52
	, VO_GetArray1 = 53
	, VO_SetArray1 = 54
	, VO_GetFrameP1 = 55
	, VO_GetFrame1 = 56
	, VO_SetFrame1 = 57
	, VO_GetStaticP1 = 58
	, VO_GetStatic1 = 59
	, VO_SetStatic1 = 60
	, VO_Add1 = 61
	, VO_Mult1 = 62
	, VO_GetImmP = 63
	, VO_GetImmP1 = 64
	, VO_GetImm1 = 65
	, VO_SetImm1 = 66
	, VO_PushS = 67
	, VO_Add2 = 68
	, VO_Mult2 = 69
	, VO_GetImmP2 = 70
	, VO_GetImm2 = 71
	, VO_SetImm2 = 72
	, VO_GetArrayP2 = 73
	, VO_GetArray2 = 74
	, VO_SetArray2 = 75
	, VO_GetFrameP2 = 76
	, VO_GetFrame2 = 77
	, VO_SetFrame2 = 78
	, VO_GetStaticP2 = 79
	, VO_GetStatic2 = 80
	, VO_SetStatic2 = 81
	, VO_GetGlobalP2 = 82
	, VO_GetGlobal2 = 83
	, VO_SetGlobal2 = 84
	, VO_Jump = 85
	, VO_JumpFalse = 86
	, VO_JumpNE = 87
	, VO_JumpEQ = 88
	, VO_JumpLE = 89
	, VO_JumpLT = 90
	, VO_JumpGE = 91
	, VO_JumpGT = 92
	, VO_Call = 93
	, VO_GetGlobalp3 = 94
	, VO_GetGlobal3 = 95
	, VO_SetGlobal3 = 96
	, VO_PushI24 = 97
	, VO_Switch = 98
	, VO_PushString = 99
	, VO_GetHash = 100
	, VO_StrCopy = 101
	, VO_ItoS = 102
	, VO_StrAdd = 103
	, VO_StrAddi = 104
	, VO_Memcopy = 105
	, VO_Catch = 106
	, VO_Throw = 107
	, VO_pCall = 108
	, VO_Push_Neg1 = 109
	, VO_Push_0 = 110
	, VO_Push_1 = 111
	, VO_Push_2 = 112
	, VO_Push_3 = 113
	, VO_Push_4 = 114
	, VO_Push_5 = 115
	, VO_Push_6 = 116
	, VO_Push_7 = 117
	, VO_PushF_Neg1 = 118
	, VO_PushF_0 = 119
	, VO_PushF_1 = 120
	, VO_PushF_2 = 121
	, VO_PushF_3 = 122
	, VO_PushF_4 = 123
	, VO_PushF_5 = 124
	, VO_PushF_6 = 125
	, VO_PushF_7 = 126

};

enum GTAIV_Opcodes
{
	  IVO_Nop = 0
	, IVO_Add = 1
	, IVO_Sub = 2
	, IVO_Mult = 3
	, IVO_Div = 4
	, IVO_Mod = 5
	, IVO_Not = 6
	, IVO_Neg = 7
	, IVO_CmpEq = 8
	, IVO_CmpNe = 9
	, IVO_CmpGt = 10
	, IVO_CmpGe = 11
	, IVO_CmpLt = 12
	, IVO_CmpLe = 13
	, IVO_fAdd = 14
	, IVO_fSub = 15
	, IVO_fMult = 16
	, IVO_fDiv = 17
	, IVO_fMod = 18
	, IVO_fNeg = 19
	, IVO_fCmpEq = 20
	, IVO_fCmpNe = 21
	, IVO_fCmpGt = 22
	, IVO_fCmpGe = 23
	, IVO_fCmpLt = 24
	, IVO_fCmpLe = 25
	, IVO_vAdd = 26
	, IVO_vSub = 27
	, IVO_vMult = 28
	, IVO_vDiv = 29
	, IVO_vNeg = 30
	, IVO_And = 31
	, IVO_Or = 32
	, IVO_Xor = 33
	, IVO_Jump = 34
	, IVO_JumpFalse = 35
	, IVO_JumpTrue = 36
	, IVO_ItoF = 37
	, IVO_FtoI = 38
	, IVO_FtoV = 39
	, IVO_PushS = 40
	, IVO_Push = 41
	, IVO_PushF = 42
	, IVO_Dup = 43
	, IVO_Drop = 44
	, IVO_CallNative = 45
	, IVO_Call = 46
	, IVO_Function = 47
	, IVO_Return = 48
	, IVO_pGet = 49
	, IVO_pSet = 50
	, IVO_pPeekSet = 51
	, IVO_ToStack = 52
	, IVO_FromStack = 53
	, IVO_GetFrameP0 = 54
	, IVO_GetFrameP1 = 55
	, IVO_GetFrameP2 = 56
	, IVO_GetFrameP3 = 57
	, IVO_GetFrameP4 = 58
	, IVO_GetFrameP5 = 59
	, IVO_GetFrameP6 = 60
	, IVO_GetFrameP7 = 61
	, IVO_GetFrameP = 62
	, IVO_GetStaticP = 63
	, IVO_GetGlobalP = 64
	, IVO_GetArrayP = 65
	, IVO_Switch = 66
	, IVO_PushString = 67
	, IVO_PushStringNull = 68
	, IVO_StrCopy = 69
	, IVO_ItoS = 70
	, IVO_StrAdd = 71
	, IVO_StrAddi = 72
	, IVO_Catch = 73
	, IVO_Throw = 74
	, IVO_MemCopy = 75
	, IVO_GetXProtect = 76//PC Only  -- Console refer to Exit
	, IVO_SetXProtect = 77//PC Only  -- Console refer to Exit
	, IVO_RefXProtect = 78//PC Only  -- Console refer to Exit
	, IVO_Exit = 79//this op is unhandled and the vm exits on an unhandled op
	, IVO_Push_Neg16 = 80
	, IVO_Push_Neg15 = 81
	, IVO_Push_Neg14 = 82
	, IVO_Push_Neg13 = 83
	, IVO_Push_Neg12 = 84
	, IVO_Push_Neg11 = 85
	, IVO_Push_Neg10 = 86
	, IVO_Push_Neg9  = 87
	, IVO_Push_Neg8  = 88
	, IVO_Push_Neg7  = 89
	, IVO_Push_Neg6  = 90
	, IVO_Push_Neg5  = 91
	, IVO_Push_Neg4  = 92
	, IVO_Push_Neg3  = 93
	, IVO_Push_Neg2  = 94
	, IVO_Push_Neg1 = 95
	, IVO_Push_0 = 96
	, IVO_Push_1 = 97
	, IVO_Push_2 = 98
	, IVO_Push_3 = 99
	, IVO_Push_4 = 100
	, IVO_Push_5 = 101
	, IVO_Push_6 = 102
	, IVO_Push_7 = 103
	, IVO_Push_8 = 104
	, IVO_Push_9 = 105
	, IVO_Push_10 = 106
	, IVO_Push_11 = 107
	, IVO_Push_12 = 108
	, IVO_Push_13 = 109
	, IVO_Push_14 = 110
	, IVO_Push_15 = 111
	, IVO_Push_16 = 112
	, IVO_Push_17 = 113
	, IVO_Push_18 = 114
	, IVO_Push_19 = 115
	, IVO_Push_20 = 116
	, IVO_Push_21 = 117
	, IVO_Push_22 = 118
	, IVO_Push_23 = 119
	, IVO_Push_24 = 120
	, IVO_Push_25 = 121
	, IVO_Push_26 = 122
	, IVO_Push_27 = 123
	, IVO_Push_28 = 124
	, IVO_Push_29 = 125
	, IVO_Push_30 = 126
	, IVO_Push_31 = 127
	, IVO_Push_32 = 128
	, IVO_Push_33 = 129
	, IVO_Push_34 = 130
	, IVO_Push_35 = 131
	, IVO_Push_36 = 132
	, IVO_Push_37 = 133
	, IVO_Push_38 = 134
	, IVO_Push_39 = 135
	, IVO_Push_40 = 136
	, IVO_Push_41 = 137
	, IVO_Push_42 = 138
	, IVO_Push_43 = 139
	, IVO_Push_44 = 140
	, IVO_Push_45 = 141
	, IVO_Push_46 = 142
	, IVO_Push_47 = 143
	, IVO_Push_48 = 144
	, IVO_Push_49 = 145
	, IVO_Push_50 = 146
	, IVO_Push_51 = 147
	, IVO_Push_52 = 148
	, IVO_Push_53 = 149
	, IVO_Push_54 = 150
	, IVO_Push_55 = 151
	, IVO_Push_56 = 152
	, IVO_Push_57 = 153
	, IVO_Push_58 = 154
	, IVO_Push_59 = 155
	, IVO_Push_60 = 156
	, IVO_Push_61 = 157
	, IVO_Push_62 = 158
	, IVO_Push_63 = 159
	, IVO_Push_64 = 160
	, IVO_Push_65 = 161
	, IVO_Push_66 = 162
	, IVO_Push_67 = 163
	, IVO_Push_68 = 164
	, IVO_Push_69 = 165
	, IVO_Push_70 = 166
	, IVO_Push_71 = 167
	, IVO_Push_72 = 168
	, IVO_Push_73 = 169
	, IVO_Push_74 = 170
	, IVO_Push_75 = 171
	, IVO_Push_76 = 172
	, IVO_Push_77 = 173
	, IVO_Push_78 = 174
	, IVO_Push_79 = 175
	, IVO_Push_80 = 176
	, IVO_Push_81 = 177
	, IVO_Push_82 = 178
	, IVO_Push_83 = 179
	, IVO_Push_84 = 180
	, IVO_Push_85 = 181
	, IVO_Push_86 = 182
	, IVO_Push_87 = 183
	, IVO_Push_88 = 184
	, IVO_Push_89 = 185
	, IVO_Push_90 = 186
	, IVO_Push_91 = 187
	, IVO_Push_92 = 188
	, IVO_Push_93 = 189
	, IVO_Push_94 = 190
	, IVO_Push_95 = 191
	, IVO_Push_96 = 192
	, IVO_Push_97 = 193
	, IVO_Push_98 = 194
	, IVO_Push_99 = 195
	, IVO_Push_100 = 196
	, IVO_Push_101 = 197
	, IVO_Push_102 = 198
	, IVO_Push_103 = 199
	, IVO_Push_104 = 200
	, IVO_Push_105 = 201
	, IVO_Push_106 = 202
	, IVO_Push_107 = 203
	, IVO_Push_108 = 204
	, IVO_Push_109 = 205
	, IVO_Push_110 = 206
	, IVO_Push_111 = 207
	, IVO_Push_112 = 208
	, IVO_Push_113 = 209
	, IVO_Push_114 = 210
	, IVO_Push_115 = 211
	, IVO_Push_116 = 212
	, IVO_Push_117 = 213
	, IVO_Push_118 = 214
	, IVO_Push_119 = 215
	, IVO_Push_120 = 216
	, IVO_Push_121 = 217
	, IVO_Push_122 = 218
	, IVO_Push_123 = 219
	, IVO_Push_124 = 220
	, IVO_Push_125 = 221
	, IVO_Push_126 = 222
	, IVO_Push_127 = 223
	, IVO_Push_128 = 224
	, IVO_Push_129 = 225
	, IVO_Push_130 = 226
	, IVO_Push_131 = 227
	, IVO_Push_132 = 228
	, IVO_Push_133 = 229
	, IVO_Push_134 = 230
	, IVO_Push_135 = 231
	, IVO_Push_136 = 232
	, IVO_Push_137 = 233
	, IVO_Push_138 = 234
	, IVO_Push_139 = 235
	, IVO_Push_140 = 236
	, IVO_Push_141 = 237
	, IVO_Push_142 = 238
	, IVO_Push_143 = 239
	, IVO_Push_144 = 240
	, IVO_Push_145 = 241
	, IVO_Push_146 = 242
	, IVO_Push_147 = 243
	, IVO_Push_148 = 244
	, IVO_Push_149 = 245
	, IVO_Push_150 = 246
	, IVO_Push_151 = 247
	, IVO_Push_152 = 248
	, IVO_Push_153 = 249
	, IVO_Push_154 = 250
	, IVO_Push_155 = 251
	, IVO_Push_156 = 252
	, IVO_Push_157 = 253
	, IVO_Push_158 = 254
	, IVO_Push_159 = 255
};

#pragma warning( disable : 4201 )//unnamed struct extention
typedef union OpCodes {
	const uint8_t A[176];
	struct {
		const uint8_t
			Nop
			, Add
			, Sub
			, Mult
			, Div
			, Mod
			, Not
			, Neg
			, CmpEq
			, CmpNe
			, CmpGt
			, CmpGe
			, CmpLt
			, CmpLe
			, fAdd
			, fSub
			, fMult
			, fDiv
			, fMod
			, fNeg
			, fCmpEq
			, fCmpNe
			, fCmpGt
			, fCmpGe
			, fCmpLt
			, fCmpLe
			, vAdd
			, vSub
			, vMult
			, vDiv
			, vNeg
			, And
			, Or
			, Xor
			, ItoF
			, FtoI
			, FtoV
			, PushB
			, PushB2
			, PushB3
			, Push
			, PushF
			, Dup
			, Drop
			, CallNative
			, Function
			, Return
			, pGet
			, pSet
			, pPeekSet
			, ToStack
			, FromStack
			, GetArrayP1
			, GetArray1
			, SetArray1
			, GetFrameP1
			, GetFrame1
			, SetFrame1
			, GetStaticP1
			, GetStatic1
			, SetStatic1
			, Add1
			, Mult1
			, GetImm1
			, SetImm1
			, PushS
			, Add2
			, Mult2
			, GetImm2
			, SetImm2
			, GetArrayP2
			, GetArray2
			, SetArray2
			, GetFrameP2
			, GetFrame2
			, SetFrame2
			, GetStaticP2
			, GetStatic2
			, SetStatic2
			, GetGlobalP2
			, GetGlobal2
			, SetGlobal2
			, Jump
			, JumpFalse
			, JumpNE
			, JumpEQ
			, JumpLE
			, JumpLT
			, JumpGE
			, JumpGT
			, Call
			, GetGlobalP3
			, GetGlobal3
			, SetGlobal3
			, PushI24
			, Switch
			, PushString
			, StrCopy
			, ItoS
			, StrAdd
			, StrAddi
			, MemCopy
			, Catch
			, Throw
			, pCall
			, Push_Neg1
			, Push_0
			, Push_1
			, Push_2
			, Push_3
			, Push_4
			, Push_5
			, Push_6
			, Push_7
			, PushF_Neg1
			, PushF_0
			, PushF_1
			, PushF_2
			, PushF_3
			, PushF_4
			, PushF_5
			, PushF_6
			, PushF_7

			///Extra GTAV Opcodes
			, GetImmP
			, GetImmP1
			, GetImmP2
			, GetHash


			///Extra RDR Opcodes
			, Call2
			, Call2h1
			, Call2h2
			, Call2h3
			, Call2h4
			, Call2h5
			, Call2h6
			, Call2h7
			, Call2h8
			, Call2h9
			, Call2hA
			, Call2hB
			, Call2hC
			, Call2hD
			, Call2hE
			, Call2hF
			, PushArrayP
			, ReturnP0R0
			, ReturnP0R1
			, ReturnP0R2
			, ReturnP0R3
			, ReturnP1R0
			, ReturnP1R1
			, ReturnP1R2
			, ReturnP1R3
			, ReturnP2R0
			, ReturnP2R1
			, ReturnP2R2
			, ReturnP2R3
			, ReturnP3R0
			, ReturnP3R1
			, ReturnP3R2
			, ReturnP3R3

			///RDR and GTAIV Opcodes
			, PushStringNull

			///GTAIV Extra Opcodes
			, JumpTrue
			, GetFrameP0
			, GetFrameP3
			, GetFrameP4
			, GetFrameP5
			, GetFrameP6
			, GetFrameP7
			, GetFrameP
			, GetGlobalP
			, GetStaticP
			, GetArrayP
			, GetXProtect//PC
			, SetXProtect//PC
			, RefXProtect//PC
			, Exit

			;
	};
} OpCodes;