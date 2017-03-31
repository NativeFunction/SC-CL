@echo off
cd %~dp0
:start
echo loop-convert test.c
echo Press ENTER to launch
pause > nul
cls
"../../Debug/loop-convert.exe" -platform=XBOX -build_type=RDR_XSC test.c -- -I "../../include/"
goto start
