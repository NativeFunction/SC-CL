@echo off
cd %~dp0
:start
echo loop-convert test.c
echo Press ENTER to launch
pause > nul
cls
"../../Debug/SC-CL.exe" -platform=X360 -emit-asm -target=GTAV test.c -- -I "../../include/"
goto start
