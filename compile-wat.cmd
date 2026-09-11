@echo off
set LOGFILE=compile-wat.log
echo Build started > %LOGFILE%

set WATCOM=c:\watcom
if exist c:\watcom2\binp\wcc386.exe set WATCOM=c:\watcom2
if not exist %WATCOM%\binp\wcc386.exe goto nowatcom

if "%OS2TK%" == "" set OS2TK=c:\os2tk45
if not exist %OS2TK%\h\os2.h goto notk

set PATH=%WATCOM%\binp;%WATCOM%\bin;%PATH%
set INCLUDE=%WATCOM%\h;%WATCOM%\h\os2
set WATCOM=%WATCOM%

echo Cleaning... >> %LOGFILE%
wmake -f makefile.wat clean 2>&1 | tee -a %LOGFILE%

echo Building... >> %LOGFILE%
wmake -f makefile.wat all 2>&1 | tee -a %LOGFILE%

if exist bin\checkers.exe goto buildok
echo. >> %LOGFILE%
echo BUILD FAILED >> %LOGFILE%
echo BUILD FAILED
goto end

:buildok
echo. >> %LOGFILE%
echo BUILD OK >> %LOGFILE%
echo BUILD OK
goto end

:nowatcom
echo ERROR: Open Watcom not found at c:\watcom or c:\watcom2 >> %LOGFILE%
echo ERROR: Open Watcom not found
goto end

:notk
echo ERROR: OS/2 Toolkit not found at %OS2TK% >> %LOGFILE%
echo ERROR: OS/2 Toolkit not found at %OS2TK%

:end
