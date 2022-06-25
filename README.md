# SC-CL
SC-CL is a Clang Compiler targeted towards Rockstar's scripting format.

Supported Targets
---------------------------------
* Grand Theft Auto 4
    * SCO format
* Red Dead Redemption
    * SCO format
    * XSC format
    * CSC format
* Grand Theft Auto 5
    * XSC format
    * CSC format
    * YSC format
* Red Dead Redemption 2
    * XSC format
    * CSC format
    * YSC format

How To Build
---------------------------------
1. Download [LLVM 14.0.5 source](https://github.com/llvm/llvm-project/releases/tag/llvmorg-14.0.5)
2. Extract LLVM
3. Download [Clang SC-CL edited source](https://github.com/NativeFunction/Clang-SC-CL-Edited)
4. Replace llvm_src/clang contents with Clang-SC-CL-Edited contents
5. Make directory llvm_src/clang-tools-extra/SC-CL
6. Open llvm_src/clang-tools-extra/CMakeLists.txt
7. Add ```add_subdirectory(SC-CL)``` to bottom
8. Download [SC-CL source](https://github.com/NativeFunction/SC-CL)
9. Move SC-CL contents into llvm_src/clang-tools-extra/SC-CL
10. Run CMake configure with source dir as llvm_src/llvm and bin dir as llvm_src/build
11. Set LLVM option ```LLVM_ENABLE_PROJECTS=clang;clang-tools-extra```
12. Run CMake generate
13. Open llvm_src/build/LLVM.sln or equivalent
14. Go to Clang executables in solution explorer
15. Right click on SC-CL and click build
  
Usage
---------------------------------

```console
USAGE: SC-CL.exe [options] <source0> [... <sourceN>]

OPTIONS:

Clang Options:

  -extra-arg=<string>        - Additional argument to append to the compiler command line
  -extra-arg-before=<string> - Additional argument to prepend to the compiler command line
  -p=<string>                - Build path

Compiler Options:

  Choose obfuscation level: (This option is experimental use at your own risk)
    -Fs                      - Obfuscate string table - GTA V and RDR2 Only
    -F1                      - Enable low obfuscations
    -F2                      - Enable default obfuscations
    -F3                      - Enable high obfuscations
    -F4                      - Enable very high obfuscations
    -F5                      - Enable max obfuscations
  Choose optimization level:
    -g                       - No optimizations, enable debugging
    -O1                      - Enable trivial optimizations
    -O2                      - Enable default optimizations
    -O3                      - Enable expensive optimizations
  -emit-asm                  - Emits the pre compiled ASM representation of the script
  -emit-asm-only             - Only emits the pre compiled ASM representation of the script
  -hvi=<uint>                - Sets the starting index for host variables to ignore
  -hvs=<uint>                - Sets the amount of host variables to ignore
  -ivscr                     - Choose GTAIV sco output config:
    =CompressEncrypt         -   Sco output with compression and encryption (Default)
    =None                    -   Sco output with no compression or encryption
    =Encrypt                 -   Sco output with encryption
  -n                         - Disable function names in script output, Enabled when optimisations are turned on
  -name=<string>             - File name of output script, defaults to input file name
  -no-rsc7                   - Removes the RSC7 header from the output (GTAV)
  -out-dir=<string>          - Specify the output directory of the script
  -platform                  - Choose target platform:
    =XBOX                    -   Target Xbox
    =PSX                     -   Target Playstation
    =PC                      -   Target PC
  -pvi=<uint>                - Sets the starting index for player variables to ignore
  -pvs=<uint>                - Sets the amount of player variables to ignore
  -s                         - Limits script to one instance on runtime (RDR2 | GTAV | GTAIV)
  -target                    - Choose build target:
    =GTAIV                   -   Grand Theft Auto IV (sco output)
    =GTAIV_TLAD              -   Grand Theft Auto IV The Lost and Damned (sco output)
    =GTAIV_TBOGT             -   Grand Theft Auto IV The Ballad of Gay Tony (sco output)
    =GTAV                    -   Grand Theft Auto V (#sc output)
    =RDR_SCO                 -   Red Dead Redemption (sco output)
    =RDR_#SC                 -   Red Dead Redemption (#sc output)
    =RDR2                    -   Red Dead Redemption 2 (#sc output)
  -vcx=<vcxproj path>        - Parses source files out of a vcxproj file to allow for seamless linking in Visual Studio

Generic Options:

  -help                      - Display available options (-help-hidden for more)
  -help-list                 - Display list of available options (-help-list-hidden for more)
  -version                   - Display the version of this program
```
