@echo off
cd %~dp0
:start
echo loop-convert test.c
echo Press ENTER to launch
pause > nul
cls
"../../Debug/loop-convert.exe" -platform=XBOX -build_type=GTAV test.c inc.c -- -I "../../include/"
goto start
