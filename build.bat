:Inspired from https://stackoverflow.com/a/51350746

@echo off
chcp 65001 > NUL

 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 : Copyright (C) 2019 Charly Lamothe                                           :
 :                                                                             :
 : This file is part of LibUnknownEchoUtilsModule.                              :
 :                                                                             :
 :   Licensed under the Apache License, Version 2.0 (the "License");           :
 :   you may not use this file except in compliance with the License.          :
 :   You may obtain a copy of the License at                                   :
 :                                                                             :
 :   http://www.apache.org/licenses/LICENSE-2.0                                :
 :                                                                             :
 :   Unless required by applicable law or agreed to in writing, software       :
 :   distributed under the License is distributed on an "AS IS" BASIS,         :
 :   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  :
 :   See the License for the specific language governing permissions and       :
 :   limitations under the License.                                            :
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

setlocal enabledelayedexpansion

goto :init

:header
    echo.
    echo. %__BAT_NAME% %__VERSION%
    echo. %__COPYRIGHT% %__YEAR%
    echo.
    echo. This is a builder script for Windows, providing
    echo. command-line arguments and flags to build
    echo. personalized target, by selecting the build type,
    echo. the install_path or the target plateform.
    goto :eof

:init
    set default_build_type=release
    set default_install_path="C:\\LibUnknownEchoUtilsModule"
    set default_plateform=x64

    set "__NAME=%~n0"
    set "__VERSION=1.0"
    set "__YEAR=2019"
    set "__COPYRIGHT=Charly Lamothe"
    set "__BAT_NAME=%~nx0"

:parse
    set "map=%*"

    call :gettoken --help help
    if "%help%"=="~1" goto :show_usage

    call :gettoken --version version
    if "%version%"=="~1" goto :show_version

    call :header

    call :gettoken --build_type build_type
    call :gettoken --install_path install_path
    call :gettoken --plateform plateform

    if "%build_type%"=="--build_type=" set build_type=%default_build_type%
    if "%build_type%"=="" set build_type=%default_build_type%
    if "%install_path%"=="--install_path=" set install_path=%default_install_path%
    if "%install_path%"=="" set install_path=%default_install_path%
    if "%plateform%"=="--plateform=" set plateform=%default_plateform%
    if "%plateform%"=="" set plateform=%default_plateform%

    echo:
    echo [~] Build type is %build_type%
    echo [~] Installation path is %install_path%
    echo [~] Target plateform is %plateform%

    echo [~] Building ...
    cmake -Bbuild/%build_type% -H. -DCMAKE_BUILD_TYPE=%build_type% ^
    -DCMAKE_INSTALL_PREFIX=%install_path% ^
    -DCMAKE_GENERATOR_PLATFORM=%plateform%
    cd %cd%/build/%build_type%
    cmake --build . --config %build_type%
    cd %~dp0%

    goto :end

:gettoken
    call set "tmpvar=%%map:*%1=%%"
    if "%tmpvar%"=="%map%" (set "%~2=") else (
        for /f "tokens=1 delims= " %%a in ("%tmpvar%") do set tmpvar=%%a
        set "%~2=!tmpvar:~1!"
    )
    goto :eof

:show_usage
    echo usage: %__BAT_NAME% [--help]
    echo.                 [--build_type [BUILD_TYPE]]
    echo.                 [--install_path [INSTALL_PATH]]
    echo.                 [--plateform [PLATEFORM]]
    echo. 
    echo. optional arguments:
    echo.   --help           Shows this help
    echo.   --version        Shows the version
    echo.   --build_type [BUILD_TYPE]
    echo.                    Select the build type: release or Debug (default: %default_build_type%)
    echo.   --install_path [INSTALL_PATH]
    echo.                    Select the installation path (default: %default_install_path%)
    echo.   --plateform [PLATEFORM]
    echo.                    Select the target plateform: x64 or x86 (default: %default_plateform%)
    goto :end

:show_version
    echo %__VERSION%
    goto :end

:cleanup
    set "__NAME="
    set "__VERSION="
    set "__YEAR="
    set "__COPYRIGHT="
    set "__BAT_NAME="

    set "default_build_type="
    set "default_install_path="
    set "default_plateform="
    
    goto :eof

:end
    call :cleanup
    exit /b
