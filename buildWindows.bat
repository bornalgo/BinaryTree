:: Passed options:
:::: -source [SOURCE]      : source directory
:::: -build [BUILD]        : build directory excluding operating system
:::: -generator [GENERATOR]: generator for cmake
:::: -compiler [COMPILER]  : compiler for cmake
:::: -make [MAKE]          : make executable
:::: -vcvarsall            : path to vcvarsall.bat to set the environment variables for visual studio
:::: *                     : any cmake arguments
:::: -- *                  : any make arguments


@echo off
setlocal
setlocal EnableDelayedExpansion

set "PWD=%~dp0"
if "%HT%"=="" set "HT=Win64"


:readParam
set RESTVARCMAKE=
set RESTVARMAKE=
set getmake=false
if "%~1"=="" goto:endParam
set shift2=false
if "%~1"=="-source" (
    if "%~2"=="" goto:endParam
    set "SOURCE=%~2"
    set shift2=true
) else if "%~1"=="-build" (
    if "%~2"=="" goto:endParam
    set "BUILD=%~2\%HT%"
    set shift2=true
) else if "%~1"=="-generator" (
    if "%~2"=="" goto:endParam
    set "GENERATOR=%~2"
    set shift2=true
) else if "%~1"=="-compiler" (
    if "%~2"=="" goto:endParam
    set "COMPILER=%~2"
    set shift2=true
) else if "%~1"=="-make" (
    if "%~2"=="" goto:endParam
    set "MAKE=%~2"
    set shift2=true
) else if "%~1"=="-vcvarsall" (
    if "%~2"=="" goto:endParam
    set "VCVARSALL=%~2"
    set shift2=true
) else if "%~1"=="--" (
    set getmake=true
) else if %getmake%==true (
    set "RESTVARMAKE=%RESTVARMAKE% %1"
) else (
    set "RESTVARCMAKE=%RESTVARCMAKE% %1"
)
shift
if %shift2%==true shift
goto:readParam
:endParam

if "!SOURCE!"=="" set "SOURCE=."
if "!BUILD!"=="" set "BUILD=build\%HT%"
if "!GENERATOR!"=="" set "GENERATOR=Unix Makefiles"

:: Clean-up workspace
if exist "%BUILD%" rd /s /q "%BUILD%"
mkdir "%BUILD%"

if not "!VCVARSALL!"=="" (
    goto:callVCVARSALL
)
if "!GENERATOR!"=="NMake Makefiles" (
    goto:setMSVCenv
)
set MSVCCOMPILER="cl.exe"
for %%A in ("!MSVCCOMPILER!") do for %%B in ("!COMPILER!") do if "%%~xA"=="%%~xB" (
  goto:setMSVCenv
)

goto:callCMake

:setMSVCenv
if "!MAKE!"=="" set "MAKE=nmake"
if not "!VCVARSALL!"=="" (
    goto:callVCVARSALL
)
for /l %%p in (2017,2,2023) do (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\%%p\Professional\VC\Auxiliary\Build\vcvarsall.bat" (
        set "VCVARSALL=C:\Program Files (x86)\Microsoft Visual Studio\%%p\Professional\VC\Auxiliary\Build\vcvarsall.bat"
        goto:callVCVARSALL
    )
)
for /l %%p in (11,1,14) do (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio %%p.0\VC\vcvarsall.bat" (
        set "VCVARSALL=C:\Program Files (x86)\Microsoft Visual Studio %%p.0\VC\vcvarsall.bat"
        goto:callVCVARSALL
    )
)
if "!VCVARSALL!"=="" (
    echo Could not find the proper vcvarsall.bat
    exit -1
)
:callVCVARSALL
call "%VCVARSALL%" amd64

:callCMake
echo ::::::::::::::::::::: call cmake ::::::::::::::::::::
if "!COMPILER!"=="" (
    if "!RESTVARCMAKE!"=="" (
        cmake -G "%GENERATOR%" -S "%SOURCE%" -B "%BUILD%" 
    ) else (
        cmake "%RESTVARCMAKE%" -G "%GENERATOR%" -S "%SOURCE%" -B "%BUILD%" 
    )
) else (
    if "!RESTVARCMAKE!"=="" (
        cmake -DCMAKE_CXX_COMPILER="%COMPILER%" -G "%GENERATOR%" -S "%SOURCE%" -B "%BUILD%"
    ) else (
        cmake "%RESTVARCMAKE%" -DCMAKE_CXX_COMPILER="%COMPILER%" -G "%GENERATOR%" -S "%SOURCE%" -B "%BUILD%"
    )
)

echo ::::::::::::::::::::: call make :::::::::::::::::::::
cd "%BUILD%"
if "!MAKE!"=="" set "MAKE=make"
if "!RESTVARMAKE!"=="" (
    %MAKE%
) else (
    %MAKE% "%RESTVARMAKE%"
)


cd "%PWD%"

endlocal