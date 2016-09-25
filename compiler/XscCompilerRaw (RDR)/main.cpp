#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/timer/timer.hpp>
#include "RSC.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include "Crypto/aes256.h"

typedef string::const_iterator iter;
typedef boost::iterator_range<iter> string_view;

using namespace std;
using namespace Utils;
using namespace Utils::Bitwise;
using namespace Utils::Hashing;




int main(int argc, char* argv[]) {

    boost::timer::cpu_timer Time;



//    std::ifstream ScriptFile("C:\\Users\\Rocko\\Desktop\\testc.xsa");//xsa file
//    string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
//    ScriptFile.close();
//    RSC xsc;
//    xsc.Compile(content, 0xA8D74300, "testc", false);
//    xsc.GetHighLevelCode("C:\\Users\\Rocko\\Desktop\\test.c", 0);
//    return 0;
//    DLX File = IO::LoadData("C:\\Users\\Rocko\\Desktop\\playerlist.xsf");
//
//
//
//    const uint32_t CompressedHeaderStart = 12;
//    const uint32_t CompressedDataStart = CompressedHeaderStart + 8;//8 = compression header -> CompressedDataStart
//
//    uint32_t CompressedSize = SwapEndian(*((uint32_t*)((uint8_t*)File.data + CompressedHeaderStart + 4)));
//
//    cout << CompressedSize;
//    if(CompressedSize != File.length - CompressedDataStart)
//        Throw("Invalid Compression Size");
//
//    uint32_t DecompressedSize = 1048576;
//    uint8_t * DecompressedData = new uint8_t[DecompressedSize];
//
//    Compression::xCompress Compression;
//    Compression.xCompressInit();
//
//    Compression.Decompress((uint8_t*)File.data + CompressedDataStart,CompressedSize, DecompressedData, DecompressedSize);
//
//
//    FILE* file2 = fopen("stickieDecomp.xsf", "wb");
//    fwrite(DecompressedData, 1, DecompressedSize , file2);
//    fclose(file2);
//    cout << "File Written\n";
//
//
//    return 0;

//    std::ifstream ScriptFile("C:\\Users\\Rocko\\Desktop\\main.xsa");//xsa file
//    string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
//    ScriptFile.close();
//
//    RSC rsc;
//    rsc.CompileXSC(content, 0xA8D74300, "hello", false, 0);
//    cout << "Writing" << '\n';
//    rsc.XSCWrite("C:\\Users\\Rocko\\Desktop\\myedited.xsc", Constants::Platform::Xbox, PikIO::Endianess::Big, false);
//    cout << "Getting Code" << '\n';
//    rsc.GetCode("C:\\Users\\Rocko\\Desktop\\myedited.xsa", Constants::DecompileFlag::None, Constants::DecompileType::Type_None);
//
//    return 0;

    if(argc > 0)
    {
        int i = 0;
        uint32_t flag = Constants::DecompileFlag::None;

        if(argc > 1)//drag and drop support
        {
            if(*argv[1] != '-')
            {
                for(uint32_t dnd = 1; dnd < argc; dnd++)
                {
                    boost::filesystem::path path = argv[dnd];
                    if(boost::filesystem::is_regular_file(path))
                    {
                        string extension = boost::filesystem::extension(path);
                        string outp = path.parent_path().string();
                        string name = path.filename().stem().string();
                        string out = outp + '\\' + name;

                        if(extension == ".xsc" || extension == ".sco" || extension == "")
                        {
                            DLX File = IO::LoadData(argv[dnd]);
                            RSC Script;
                            if(Script.OpenScript(File.data, &File.length ))
                                Script.GetCode(out, Constants::DecompileFlag::None, Constants::DecompileType::Type_None);
                        }
                        else if (extension == ".xsa")
                        {
                            std::ifstream ScriptFile(argv[dnd]);//xsa file
                            string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
                            ScriptFile.close();
                            RSC xsc;
                            xsc.Compile(content, 0xA8D74300, (char*)name.c_str(), false);
                            xsc.XSCWrite((char*)(out + ".xsc").c_str(), Constants::Platform::Xbox, PikIO::Endianess::Big, true);
                        }
                        else if(extension == ".csa")
                        {
                            std::ifstream ScriptFile(argv[dnd]);//csa file
                            string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
                            ScriptFile.close();
                            RSC xsc;
                            xsc.Compile(content, 0xA8D74300, (char*)name.c_str(), false);
                            xsc.XSCWrite((char*)(out + ".csc").c_str(), Constants::Platform::PS3, PikIO::Endianess::Big, true);
                        }
                        else if(extension == ".sca")
                        {
                            std::ifstream ScriptFile(argv[dnd]);//csa file
                            string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
                            ScriptFile.close();
                            RSC xsc;
                            xsc.Compile(content, 0xA8D74300, (char*)name.c_str(), false, true);
                            xsc.SCOWrite((char*)(out + ".sco").c_str(), Constants::Platform::Xbox, PikIO::Endianess::Big, true);
                        }
                        else Throw("Unknown File Type");

                    }
                    else if(boost::filesystem::is_directory(path))
                    {

                        for ( boost::filesystem::recursive_directory_iterator end, dir(path); dir != end; ++dir ) {
                            if( boost::filesystem::is_regular_file(dir->path()))
                            {
                                string outp = dir->path().parent_path().string();
                                string out = outp + '\\' + dir->path().filename().stem().string();
                                string in = dir->path().string();

                                DLX File = IO::LoadData(in.c_str());
                                RSC Script;
                                if(Script.OpenScript(File.data, &File.length ))
                                    Script.GetCode(out, Constants::DecompileFlag::None, Constants::DecompileType::Type_None);

                            }
                        }

                    }
                    else
                    {
                        cout << "Path: " << argv[dnd] << " Is Invalid" << '\n';
                        Throw("Unknown File Type");
                    }
                }
                exit(0);
            }
        }

        while(*argv[i] != '-')
        {
            i++;
            if(i >= argc)
            {
                Throw("Unknown Command. Use -h For Help.\n");
            }
        }

        switch(Joaat((argv[i] + 1)))
        {
            case 2292601253://dec (decompile)
                {
                    bool AutoOvrD = false, DecompileDir = false, DecompileStr = false;
                    Constants::DecompileType DecompType = Constants::DecompileType::Type_None;

                    i++;
                    if(i + 2 > argc){
                        cout << "Error: No Path Selected.\n";
                        cout << "Reason: Not Enough Args.\n";
                        cout << "Use -h For Help.\n";
                        exit(0);
                    }
                    else if ( !boost::filesystem::exists( string(argv[i]) ) ){
                        cout << "Error: Path \"" << argv[i] << "\" Is Not A Valid Path For Script Input Path.\nUse -h For Help.\n";
                        exit(0);
                    }

                    string ScriptInputPath = string(argv[i]);
                    i++;
                    string output = string(argv[i]);

                    for(; i < argc; i++)
                    {
                        if(*argv[i] != '-')
                            continue;
                        switch(Joaat((argv[i] + 1)))
                        {
                            case 271188490://-spc -> ShowPC
                                flag |= Constants::DecompileFlag::ShowPC;
                            break;
                            case 2255151402://-sci(ShowCallInfo) -> ShowCallPosition
                                flag |= Constants::DecompileFlag::ShowCallPosition;
                            break;
                            case 112626587://-sji(ShowJumpInfo) -> ShowJumpPosition
                                flag |= Constants::DecompileFlag::ShowJumpPosition;
                            break;
                            case 267485001://-sni(ShowNativeInfo) -> ShowNativeInfo
                                flag |= Constants::DecompileFlag::ShowNativeInfo;
                            break;
                            case 2613223005://-ssi(ShowStringInfo) -> ShowStringsPC
                                flag |= Constants::DecompileFlag::ShowStringsPC;
                            break;
                            case 2427724831://-ow(Overwrite) -> AutoOverwrite
                                AutoOvrD = true;
                            break;
                            case 3283600799://-dcd(Decompile Directory)
                                DecompileDir = true;
                            break;
                            case 1162954956://-dcs(Decompile Strings)
                                DecompType = Constants::DecompileType::DecompileStrings;
                            break;
                            case 236164499://-onh(Output Native Hashes)
                                DecompType = Constants::DecompileType::OutputNativeHashes;
                            break;
                        }
                    }

                    if(DecompileDir)
                    {
                        if(!(boost::filesystem::is_directory(boost::filesystem::path(ScriptInputPath)) && boost::filesystem::is_directory(boost::filesystem::path(output))))
                            Throw("Decompile Directory Requires a Directory For The Path");
                        for ( boost::filesystem::recursive_directory_iterator end, dir(ScriptInputPath); dir != end; ++dir ) {
                            if( boost::filesystem::is_regular_file(dir->path()))
                            {
                                string outp = dir->path().parent_path().string();
                                string out = output + (outp.c_str() + ScriptInputPath.size()) + '\\' + dir->path().filename().stem().string();
                                string in = dir->path().string();

                                DLX File = IO::LoadData(in.c_str());
                                RSC Script;
                                if(Script.OpenScript(File.data, &File.length ))
                                    Script.GetCode(out, flag, DecompType);
                            }
                        }

                    }
                    else
                    {
                        if ( boost::filesystem::exists( output )){
                            if(!AutoOvrD)
                            {
                                cout << "Warning: Path \"" << output << "\" For Source Output Path Already Exists.\nDo You Want To Overwrite? Y = Yes, N = No:";
                                char in;
                                cin >> in;
                                if(tolower(in) != 'y')
                                {
                                    cout << "Operation Canceled.\n";
                                    exit(0);
                                }
                            }
                        }


                        DLX File = IO::LoadData(ScriptInputPath.c_str());
                        RSC Script;
                        if(Script.OpenScript(File.data, &File.length ))
                            Script.GetCode(output, flag, DecompType);
                    }


                }
            break;

            case 2907564607://com (compile)
                {
                    bool AutoOvrC = false, IsXbox = true, IgnoreNops = false, Rsc = true;
                    const char* DefaultName = (const char*)"Script";
                    char* name = (char*)DefaultName;
                    uint32_t Pagebase = 0xA8D74300, ParamCount = 0;

                    i++;
                    if(i + 2 > argc){
                        cout << "Error: No Path Selected. Use -h For Help.\n";
                        exit(0);
                    }
                    else if ( !boost::filesystem::exists( string(argv[i]) ) ){
                        cout << "Error: Path \"" << argv[i] << "\" Is Not A Valid Path For Source Input Path.\nUse -h For Help.\n";
                        exit(0);
                    }


                    std::ifstream ScriptFile(argv[i]);//xsa file
                    string content( (std::istreambuf_iterator<char>(ScriptFile) ),(std::istreambuf_iterator<char>()));
                    ScriptFile.close();


                    i++;
                    string output = string(argv[i]);
                    char * outputc = argv[i];

                    for(; i < argc; i++)
                    {
                        if(*argv[i] != '-')
                            continue;
                        switch(Joaat((argv[i] + 1)))
                        {
                            case 3095851008://-sp(set platform)
                                i++;
                                if(tolower(argv[i][0]) == 'x' && tolower(argv[i][1]) == 'b' && tolower(argv[i][2]) == 'o' && tolower(argv[i][3]) == 'x' && tolower(argv[i][4]) == '\0')
                                {
                                    IsXbox = true;
                                }
                                else if(tolower(argv[i][0]) == 'p' && tolower(argv[i][1]) == 's' && tolower(argv[i][2]) == '3' && tolower(argv[i][3]) == '\0')
                                {
                                    IsXbox = false;
                                }
                                else
                                {
                                    cout << "Error: Platform" << argv[i] << "\" Does Not Exist.\nUse -h For Help.\n";
                                    exit(0);
                                }
                            break;
                            case 116125582://-spb(SetPageBase)
                                {
                                    i++;
                                    char* endp;
                                    uint32_t value = strtoul(argv[i], &endp, 0);
                                    if (endp == argv[i]) {
                                        //failed
                                        cout << "Error: Could Not Parse " << argv[i] << " for Set Page Base. \nUse -h For Help.\n";
                                        exit(0);
                                    }
                                    else if (*endp != 0) {
                                        //invalid char
                                        cout << "Error: Could Not Parse " << argv[i] << " for Set Page Base. \nUse -h For Help.\n";
                                        exit(0);
                                    }
                                    else {
                                        Pagebase = value;
                                    }
                                }
                            break;
                            case 1298113611://-in(IgnoreNops)
                                IgnoreNops = true;
                            break;
                            case 3827458856://-norsc(no resource)
                                Rsc = false;
                            break;
                            case 2427724831://-ow(Overwrite) -> AutoOverwrite
                                AutoOvrC = true;
                            break;
                        }
                    }

                    if ( boost::filesystem::exists( output )){
                        if(!AutoOvrC)
                        {
                            cout << "Warning: Path \"" << output << "\" For Script Output Path Already Exists.\nDo You Want To Overwrite? Y = Yes, N = No:";
                            char in;
                            cin >> in;
                            if(tolower(in) != 'y')
                            {
                                cout << "Operation Canceled.\n";
                                exit(0);
                            }
                        }
                    }
                    else
                    {
                        if(outputc[0] == '-')
                        {
                            cout << "Error: Path \"" << output << "\" Is Not A Valid Path For Script Output Path.\nUse -h For Help.\n";
                            exit(0);
                        }
                    }

                    //parse name
                        uint32_t inc = 0,start = 0;
                        while(true)
                        {
                            switch(outputc[inc])
                            {
                                case '\0':
                                    goto ExitNameParse;
                                case '\\':
                                    start = inc + 1;
                                    break;
                                case '.':
                                    uint32_t ssize = inc - start;
                                    name = new char[ssize + 1];
                                    memcpy(name,outputc + start,ssize);
                                    name[ssize] = '\0';
                                goto ExitNameParse;
                            }
                            inc++;
                        }
                    ExitNameParse:

                    RSC xsc;
                    xsc.Compile(content, Pagebase, name, IgnoreNops);
                    if(IsXbox)
                        xsc.XSCWrite(outputc, Constants::Platform::Xbox, PikIO::Endianess::Big, Rsc);
                    else
                        xsc.XSCWrite(outputc, Constants::Platform::PS3, PikIO::Endianess::Big, Rsc);

                }
            break;

            case 1879302122://h (help)
            //{ help
                cout
                << "Operations:----------------------\n"
                << "-dec = Decompile {Script Input Path} {Source Output Path} {Optional Decompile Flags}\n"
                << "-com = Compile {Source Input Path} {Script Output Path} {Optional Compile Flags}\n"
                << "Decompile Flags:-----------------\n"
                << "-spc = Show PC Information\n"
                << "-sci = Show Call PC Information\n"
                << "-sji = Show Jump PC Information\n"
                << "-sni = Show Native Index Information\n"
                << "-ssi = Show String Index Information\n"
                << "-ow = Automatically Overwrite Source Output Path\n"
                << "-dcd = Decompile Directory (Input And Output Must Be A Path)\n"
                << "-dcs = Decompile Strings"
                << "-onh = Output Native Hashes Gathered From Scripts In The Programs Directory\n"
                << "Compile Flags:-------------------\n"
                << "-sp = Set Platform {Xbox|PS3} Default Xbox\n"
                << "-spb = Set Page Base {uint32 Pagebase}\n"
                << "-in = Ignore Nops\n"
                << "-norsc = Don't Write The Script as a Resource\n"
                << "-ow = Automatically Overwrite Script Output Path\n"
                ;
            //}
            break;

            default:
                cout << "Unknown Command. Use -h For Help.\n";
            break;

        }

    }
    else Throw("Unknown Command. Use -h For Help.\n");

    cout << Time.format();
    return 0;
}

