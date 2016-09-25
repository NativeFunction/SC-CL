#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <string>
#include <fstream>
#include "Utils.h"
#include "Constants.h"


using namespace std;

namespace Utils{


    int GetSizeFromFlag(int flag, int baseSize)
    {
        baseSize <<= (flag & 0xF);
        int size = (int)((((flag >> 17) &0x7f) +(((flag >> 11) & 0x3f) << 1) +(((flag >> 7) &0xf) << 2) +(((flag >> 5) &0x3) << 3) +(((flag >> 4) &0x1) << 4)) * baseSize);
        for (int i = 0; i < 4; i++)
        {
            size += (((flag >> (24 + i)) &1) == 1) ? (baseSize >> (1 + i)) : 0;
        }
        return size;
    }
    int GetFlagFromSize(int size, int baseSize)
    {
        for (int i = 0; i < 0x7FFFFFFF;i++)
        {
            if (GetSizeFromFlag(i, baseSize) == size)
                return i;
        }
        return 0;
    }
    int CountOffNextBlockSize(int size, int blockSize)
    {
        return blockSize - (size % blockSize);
    }
    int NextBlockSize(int size, int blockSize)
    {
        int sizeLeft = CountOffNextBlockSize(size, blockSize);
        if (sizeLeft == 0)
            return size;
        return size + sizeLeft;
    }
    vector<char> GiveDataBlock(vector<char> data, int blockSize)
    {
        int sizeLeft = 0x10 - (data.size() % 0x10);
        if (sizeLeft == 0)
            return data;

        vector<char> newData(data.size() + sizeLeft);
        memcpy(&newData,&data,data.size());

        return newData;
    }
    vector<char> GiveDataBlock(char* data, int blockSize)
    {
        return GiveDataBlock(data + '\0', blockSize);
    }
    vector<char> GiveDataBlock(int size, int blockSize)
    {
        vector<char> temp(size);
        return GiveDataBlock(temp , blockSize);
    }
    int GetPointerInt(int x)
    {
        if (x == 0)
            return 0;
        return 0x50000000 | x;
    }
    unsigned int Joaat(char* key)
    {
        unsigned int hash, i;
        for (hash = i = 0; i < strlen(key); i++)
        {
            hash += tolower(key[i]);
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash;
    }



    float SwapEndian(float* x)
    {
        float out = 0;
        *(int8_t*)&out = *((int8_t*)x + 3);
        *((int8_t*)&out + 1) = *((int8_t*)x + 2);
        *((int8_t*)&out + 2) = *((int8_t*)x + 1);
        *((int8_t*)&out + 3) = *(int8_t*)x;
        return out;
    }

    char* IntToHex(uint32_t val)
    {
        const char hex_str[]= "0123456789ABCDEF";
        uint8_t* bin = (uint8_t*)&val;

        char* str = new char [9];

        for (uint32_t i = 0; i < 4; i++)
        {
            str[i * 2 + 0] = hex_str[(bin[i] >> 4) & 0x0F];
            str[i * 2 + 1] = hex_str[(bin[i]) & 0x0F];
        }
        str[8] = '\0';
        return str;
    }


    DLX LoadData(char* loc) {
        ifstream is(loc, std::ios::in|std::ios::binary|std::ios::ate);
        is.seekg(0, is.end);
        size_t datasize = is.tellg();
        is.seekg(0, is.beg);
        DLX File;
        File.data = new char [datasize];
        File.length = datasize;
        is.read((char*)File.data, datasize);
        is.close();
        return File;
    }
    void Throw(string str)
    {
        cout << "Exception: " << str << "\r\nPress ENTER to exit...\r\n" << flush;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
        exit(0);
    }
    void Pause()
    {
        cout << "Press ENTER to continue..." << flush;
        cin.clear();
        cin.ignore( numeric_limits<streamsize>::max(), '\n' );
    }
    int GetPageLenAtPage(int pgCount, int totalLen, int pg, int maxPageSize)
    {
        return (pg == pgCount - 0x1) ? (totalLen % maxPageSize) : maxPageSize;
    }
    int GetOpCodeLengthDefault(Constants::OpCode opCode)
    {
        //Lengths include the opCode byte
        switch (opCode)
        {
            case Constants::OpCode::Nop:
            case Constants::OpCode::Add:
            case Constants::OpCode::Sub:
            case Constants::OpCode::Mult:
            case Constants::OpCode::Div:
            case Constants::OpCode::Mod:
            case Constants::OpCode::Not:
            case Constants::OpCode::Neg:
            case Constants::OpCode::CmpEQ:
            case Constants::OpCode::CmpNE:
            case Constants::OpCode::CmpGT:
            case Constants::OpCode::CmpGE:
            case Constants::OpCode::CmpLT:
            case Constants::OpCode::CmpLE:
            case Constants::OpCode::fAdd:
            case Constants::OpCode::fSub:
            case Constants::OpCode::fMult:
            case Constants::OpCode::fDiv:
            case Constants::OpCode::fMod:
            case Constants::OpCode::fNeg:
            case Constants::OpCode::fCmpEQ:
            case Constants::OpCode::fCmpNE:
            case Constants::OpCode::fCmpGT:
            case Constants::OpCode::fCmpGE:
            case Constants::OpCode::fCmpLT:
            case Constants::OpCode::fCmpLE:
            case Constants::OpCode::vAdd:
            case Constants::OpCode::vSub:
            case Constants::OpCode::vMult:
            case Constants::OpCode::vDiv:
            case Constants::OpCode::vNeg:
            case Constants::OpCode::And:
            case Constants::OpCode::Or:
            case Constants::OpCode::Xor:
            case Constants::OpCode::IToF:
            case Constants::OpCode::FToI:
            case Constants::OpCode::FToV:
            case Constants::OpCode::Dup:
            case Constants::OpCode::Drop:
            case Constants::OpCode::pGet:
            case Constants::OpCode::pSet:
            case Constants::OpCode::pPeekSet:
            case Constants::OpCode::ToStack:
            case Constants::OpCode::FromStack:
            case Constants::OpCode::GetImmP:
            case Constants::OpCode::PushString:
            case Constants::OpCode::GetHash:
            case Constants::OpCode::MemCopy:
            case Constants::OpCode::Catch:
            case Constants::OpCode::Throw:
            case Constants::OpCode::pCall:
            case Constants::OpCode::Push_Neg1:
            case Constants::OpCode::Push_0:
            case Constants::OpCode::Push_1:
            case Constants::OpCode::Push_2:
            case Constants::OpCode::Push_3:
            case Constants::OpCode::Push_4:
            case Constants::OpCode::Push_5:
            case Constants::OpCode::Push_6:
            case Constants::OpCode::Push_7:
            case Constants::OpCode::PushF_Neg1:
            case Constants::OpCode::PushF_0:
            case Constants::OpCode::PushF_1:
            case Constants::OpCode::PushF_2:
            case Constants::OpCode::PushF_3:
            case Constants::OpCode::PushF_4:
            case Constants::OpCode::PushF_5:
            case Constants::OpCode::PushF_6:
            case Constants::OpCode::PushF_7:
                return 1;
            case Constants::OpCode::PushB:
            case Constants::OpCode::GetArrayP1:
            case Constants::OpCode::GetArray1:
            case Constants::OpCode::SetArray1:
            case Constants::OpCode::GetFrameP1:
            case Constants::OpCode::GetFrame1:
            case Constants::OpCode::SetFrame1:
            case Constants::OpCode::GetStaticP1:
            case Constants::OpCode::GetStatic1:
            case Constants::OpCode::SetStatic1:
            case Constants::OpCode::Add1:
            case Constants::OpCode::Mult1:
            case Constants::OpCode::GetImmP1:
            case Constants::OpCode::GetImm1:
            case Constants::OpCode::SetImm1:
            case Constants::OpCode::StrCopy:
            case Constants::OpCode::IToS:
            case Constants::OpCode::StrAdd:
            case Constants::OpCode::StrAddI:
                return 2;
            case Constants::OpCode::Switch:
                return 2;

            case Constants::OpCode::PushB2:
            case Constants::OpCode::Return:
            case Constants::OpCode::PushS:
            case Constants::OpCode::Add2:
            case Constants::OpCode::Mult2:
            case Constants::OpCode::GetImmP2:
            case Constants::OpCode::GetImm2:
            case Constants::OpCode::SetImm2:
            case Constants::OpCode::GetArrayP2:
            case Constants::OpCode::GetArray2:
            case Constants::OpCode::SetArray2:
            case Constants::OpCode::GetFrameP2:
            case Constants::OpCode::GetFrame2:
            case Constants::OpCode::SetFrame2:
            case Constants::OpCode::GetStaticP2:
            case Constants::OpCode::GetStatic2:
            case Constants::OpCode::SetStatic2:
            case Constants::OpCode::GetGlobalP2:
            case Constants::OpCode::GetGlobal2:
            case Constants::OpCode::SetGlobal2:
            case Constants::OpCode::Jump:
            case Constants::OpCode::JumpFalse:
            case Constants::OpCode::JumpEQ:
            case Constants::OpCode::JumpNE:
            case Constants::OpCode::JumpGE:
            case Constants::OpCode::JumpGT:
            case Constants::OpCode::JumpLE:
            case Constants::OpCode::JumpLT:
                return 3;
            case Constants::OpCode::PushB3:
            case Constants::OpCode::CallNative:
            case Constants::OpCode::Call:
            case Constants::OpCode::GetGlobalP3:
            case Constants::OpCode::GetGlobal3:
            case Constants::OpCode::SetGlobal3:
            case Constants::OpCode::PushI24:
                return 4;

            case Constants::OpCode::Push:
            case Constants::OpCode::PushF:
                return 5;
            case Constants::OpCode::Function:
                return 5;
            default:
                return 0;
        }
    }
    int GetOpCodeLength(Constants::OpCode opCode, vector<char> code, int PC)
    {
        //Lengths include the opCode byte
        switch (opCode)
        {
            case Constants::OpCode::Nop:
            case Constants::OpCode::Add:
            case Constants::OpCode::Sub:
            case Constants::OpCode::Mult:
            case Constants::OpCode::Div:
            case Constants::OpCode::Mod:
            case Constants::OpCode::Not:
            case Constants::OpCode::Neg:
            case Constants::OpCode::CmpEQ:
            case Constants::OpCode::CmpNE:
            case Constants::OpCode::CmpGT:
            case Constants::OpCode::CmpGE:
            case Constants::OpCode::CmpLT:
            case Constants::OpCode::CmpLE:
            case Constants::OpCode::fAdd:
            case Constants::OpCode::fSub:
            case Constants::OpCode::fMult:
            case Constants::OpCode::fDiv:
            case Constants::OpCode::fMod:
            case Constants::OpCode::fNeg:
            case Constants::OpCode::fCmpEQ:
            case Constants::OpCode::fCmpNE:
            case Constants::OpCode::fCmpGT:
            case Constants::OpCode::fCmpGE:
            case Constants::OpCode::fCmpLT:
            case Constants::OpCode::fCmpLE:
            case Constants::OpCode::vAdd:
            case Constants::OpCode::vSub:
            case Constants::OpCode::vMult:
            case Constants::OpCode::vDiv:
            case Constants::OpCode::vNeg:
            case Constants::OpCode::And:
            case Constants::OpCode::Or:
            case Constants::OpCode::Xor:
            case Constants::OpCode::IToF:
            case Constants::OpCode::FToI:
            case Constants::OpCode::FToV:
            case Constants::OpCode::Dup:
            case Constants::OpCode::Drop:
            case Constants::OpCode::pGet:
            case Constants::OpCode::pSet:
            case Constants::OpCode::pPeekSet:
            case Constants::OpCode::ToStack:
            case Constants::OpCode::FromStack:
            case Constants::OpCode::GetImmP:
            case Constants::OpCode::PushString:
            case Constants::OpCode::GetHash:
            case Constants::OpCode::MemCopy:
            case Constants::OpCode::Catch:
            case Constants::OpCode::Throw:
            case Constants::OpCode::pCall:
            case Constants::OpCode::Push_Neg1:
            case Constants::OpCode::Push_0:
            case Constants::OpCode::Push_1:
            case Constants::OpCode::Push_2:
            case Constants::OpCode::Push_3:
            case Constants::OpCode::Push_4:
            case Constants::OpCode::Push_5:
            case Constants::OpCode::Push_6:
            case Constants::OpCode::Push_7:
            case Constants::OpCode::PushF_Neg1:
            case Constants::OpCode::PushF_0:
            case Constants::OpCode::PushF_1:
            case Constants::OpCode::PushF_2:
            case Constants::OpCode::PushF_3:
            case Constants::OpCode::PushF_4:
            case Constants::OpCode::PushF_5:
            case Constants::OpCode::PushF_6:
            case Constants::OpCode::PushF_7:
                return 1;
            case Constants::OpCode::PushB:
            case Constants::OpCode::GetArrayP1:
            case Constants::OpCode::GetArray1:
            case Constants::OpCode::SetArray1:
            case Constants::OpCode::GetFrameP1:
            case Constants::OpCode::GetFrame1:
            case Constants::OpCode::SetFrame1:
            case Constants::OpCode::GetStaticP1:
            case Constants::OpCode::GetStatic1:
            case Constants::OpCode::SetStatic1:
            case Constants::OpCode::Add1:
            case Constants::OpCode::Mult1:
            case Constants::OpCode::GetImmP1:
            case Constants::OpCode::GetImm1:
            case Constants::OpCode::SetImm1:
            case Constants::OpCode::StrCopy:
            case Constants::OpCode::IToS:
            case Constants::OpCode::StrAdd:
            case Constants::OpCode::StrAddI:
                return 2;
            case Constants::OpCode::Switch:
                return 2 + (code[PC + 1] * 6);

            case Constants::OpCode::PushB2:
            case Constants::OpCode::Return:
            case Constants::OpCode::PushS:
            case Constants::OpCode::Add2:
            case Constants::OpCode::Mult2:
            case Constants::OpCode::GetImmP2:
            case Constants::OpCode::GetImm2:
            case Constants::OpCode::SetImm2:
            case Constants::OpCode::GetArrayP2:
            case Constants::OpCode::GetArray2:
            case Constants::OpCode::SetArray2:
            case Constants::OpCode::GetFrameP2:
            case Constants::OpCode::GetFrame2:
            case Constants::OpCode::SetFrame2:
            case Constants::OpCode::GetStaticP2:
            case Constants::OpCode::GetStatic2:
            case Constants::OpCode::SetStatic2:
            case Constants::OpCode::GetGlobalP2:
            case Constants::OpCode::GetGlobal2:
            case Constants::OpCode::SetGlobal2:
            case Constants::OpCode::Jump:
            case Constants::OpCode::JumpFalse:
            case Constants::OpCode::JumpEQ:
            case Constants::OpCode::JumpNE:
            case Constants::OpCode::JumpGE:
            case Constants::OpCode::JumpGT:
            case Constants::OpCode::JumpLE:
            case Constants::OpCode::JumpLT:

                return 3;

            case Constants::OpCode::PushB3:
            case Constants::OpCode::CallNative:
            case Constants::OpCode::Call:
            case Constants::OpCode::GetGlobalP3:
            case Constants::OpCode::GetGlobal3:
            case Constants::OpCode::SetGlobal3:
            case Constants::OpCode::PushI24:
                return 4;

            case Constants::OpCode::Push:
            case Constants::OpCode::PushF:
                return 5;
            case Constants::OpCode::Function:
                return 5 + code[PC + 4];


            default:{
                cout << "Unknown OpCode: " << (int)opCode << endl << "PC: " << PC << "\r\n";
                Throw( "Unknown OpCode" );
            }
        }

    }



}
