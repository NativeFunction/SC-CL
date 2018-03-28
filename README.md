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

  Choose obfuscation level:  (This option is experimental use at your own risk)
    -Fs                      - Obfuscate string table - GTA V Only
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
  -n                         - Disable function names in script output, Enabled when optimisations are turned on
  -name=<string>             - File name of output script, defaults to input file name
  -no-rsc7                   - Removes the RSC7 header from the output (GTAV)
  -out-dir=<string>          - Specify the output directory of the script
  -pc-version=<uint>         - Sets the pc version for use in the native translation table
  -platform                  - Choose target platform:
    =X360                    -   Target Xbox (32 bit, big endian)
    =PS3                     -   Target PS3 (32 bit, big endian)
    =PC                      -   Target PC (64 bit, little endian)
  -pvi=<uint>                - Sets the starting index for player variables to ignore
  -pvs=<uint>                - Sets the amount of player variables to ignore
  -s                         - Limits script to one instance on runtime (GTAV | GTAIV)
  -target                    - Choose build target:
    =GTAIV                   -   Grand Theft Auto IV (sco output)
    =GTAIV_TLAD              -   Grand Theft Auto IV The Lost and Damned (sco output)
    =GTAIV_TBOGT             -   Grand Theft Auto IV The Ballad of Gay Tony (sco output)
    =GTAV                    -   Grand Theft Auto V (#sc output)
    =RDR_SCO                 -   Red Dead Redemption (sco output)
    =RDR_#SC                 -   Red Dead Redemption (#sc output)
  -vcx=<vcxproj path>        - Parses source files out of a vcxproj file to allow for seamless linking in Visual Studio

General options:

  -stats                     - Enable statistics output from program (available with Asserts)

Generic Options:

  -help                      - Display available options (-help-hidden for more)
  -help-list                 - Display list of available options (-help-list-hidden for more)
  -version                   - Display the version of this program
```
