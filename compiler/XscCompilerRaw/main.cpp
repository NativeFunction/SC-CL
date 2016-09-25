#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/timer/timer.hpp>
#include "XSC.h"
#include "Utils.h"
#include <iostream>
#include <limits>

typedef string::const_iterator iter;
typedef boost::iterator_range<iter> string_view;

using namespace std;


int main(int argc, char* argv[]) {

    boost::timer::cpu_timer Time;


    if(argc > 0)
    {
            int i = 0;
            uint32_t flag = Constants::DecompileFlag::None;
            while(*argv[i] != '-')
            {
                i++;
                if(i >= argc)
                {
                    cout << "Unknown Command. Use -h For Help.\n";
                    exit(0);
                }
            }
            switch(Utils::Joaat((argv[i] + 1)))
            {
                case 2292601253://dec (decompile)
                    {
                        bool AutoOvrD = false;
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

                        Utils::DLX File = Utils::LoadData(argv[i]);
                        XSC Script;
                        Script.OpenScript(File.data, &File.length );

                        i++;
                        string output = string(argv[i]);

                        for(i; i < argc; i++)
                        {
                            if(*argv[i] != '-')
                                continue;
                            switch(Utils::Joaat((argv[i] + 1)))
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
                            }
                        }

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


                        Script.GetCode(output.c_str(), flag);

                    }
                break;
                case 2907564607://com (compile)
                    {
                        bool AutoOvrC = false, IsXbox = true, IgnoreNops = false, Rsc7 = true, CustomName = false;
                        const char* DefaultName = (const char*)"Script";
                        char* name = (char*)DefaultName;
                        uint32_t Pagebase = 3023717632, ParamCount = 0;

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

                        for(i; i < argc; i++)
                        {
                            if(*argv[i] != '-')
                                continue;
                            switch(Utils::Joaat((argv[i] + 1)))
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
                                case 214728811://-ssn(Set Script Name)
                                    i++;
                                    name = argv[i];
                                    CustomName = true;
                                break;
                                case 1142309336://-norsc7(no rsc7 header)
                                    Rsc7 = false;
                                break;
                                case 271188490://-spc(Set Param Count)
                                        {
                                        i++;
                                        char* endp;
                                        uint32_t value = strtoul(argv[i], &endp, 0);
                                        if (endp == argv[i]) {
                                            //failed
                                            cout << "Error: Could Not Parse " << argv[i] << " for Set Param Count. \nUse -h For Help.\n";
                                            exit(0);
                                        }
                                        else if (*endp != 0) {
                                            //invalid char
                                            cout << "Error: Could Not Parse " << argv[i] << " for Set Param Count. \nUse -h For Help.\n";
                                            exit(0);
                                        }
                                        else {
                                            ParamCount = value;
                                        }
                                    }
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


                        if(!CustomName)
                        {
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
                        }
                        ExitNameParse:

                        XSC xsc;
                        xsc.CompileXSC(content, Pagebase, name, IgnoreNops, ParamCount);
                        FILE* file;
                        if(IsXbox)
                            xsc.Write(file, outputc, Constants::Platform::Xbox, PikIO::Endianess::Big, Rsc7);
                        else
                            xsc.Write(file, outputc, Constants::Platform::PS3, PikIO::Endianess::Big, Rsc7);

                    }
                    break;
                case 1879302122://h (help)
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
                    << "Compile Flags:-------------------\n"
                    << "-sp = Set Platform {Xbox|PS3} Default Xbox\n"
                    << "-ssn = Set Script Name {Script Name}\n"
                    << "-spb = Set Page Base {uint32 Pagebase}\n"
                    << "-spc = Set Script Parameter Count {uint32 ParamCount}\n"
                    << "-in = Ignore Nops\n"
                    << "-norsc7 = Don't Write The Rsc7 Header\n"
                    << "-ow = Automatically Overwrite Script Output Path\n"
                    ;
                break;
                default:
                    cout << "Unknown Command. Use -h For Help.\n";
                    break;

        }
    }

    cout << Time.format();

    return 0;
}

