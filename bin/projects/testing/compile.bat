@echo off
cd %~dp0
:start
echo loop-convert test.c
echo Press ENTER to launch
pause > nul
cls
"../../Debug/sc-cl.exe" -platform=X360 -emit-asm -build_type=GTAV test.c -- -I "../../include/"
goto start
