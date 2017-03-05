@echo off

set DEFAULT_BUILD_TARGET=Rebuild
set DEFAULT_BUILD_CONFIG=Release
set DEFAULT_BUILD_PLATFORM=64
set DEFAULT_BUILD_PLATFORM_NAME=x64

set BUILD_TARGET=%DEFAULT_BUILD_TARGET%
set BUILD_CONFIG=%DEFAULT_BUILD_CONFIG%
set BUILD_PLATFORM=%DEFAULT_BUILD_PLATFORM%
set BUILD_PLATFORM_NAME=%DEFAULT_BUILD_PLATFORM_NAME%

if "%1"=="clean" set BUILD_TARGET=Clean
if "%1"=="Clean" set BUILD_TARGET=Clean

if "%1"=="build" set BUILD_TARGET=Build
if "%1"=="Build" set BUILD_TARGET=Build

if "%1"=="rebuild" set BUILD_TARGET=Rebuild
if "%1"=="Rebuild" set BUILD_TARGET=Rebuild

if "%2"=="debug" set BUILD_CONFIG=Debug
if "%2"=="Debug" set BUILD_CONFIG=Debug

if "%2"=="release" set BUILD_CONFIG=Release
if "%2"=="Release" set BUILD_CONFIG=Release

if "%3"=="x64" set BUILD_PLATFORM=64
if "%3"=="x64" set BUILD_PLATFORM_NAME=x64

if "%3"=="x86" set BUILD_PLATFORM=
if "%3"=="x86" set BUILD_PLATFORM_NAME=x86

echo %BUILD_TARGET%ing Ultraschall REAPER Plugin... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)
pushd Plugin\reaper_ultraschall
msbuild /nologo /maxcpucount /target:%BUILD_TARGET% /property:configuration=%BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /property:platformtoolset=v140 /clp:ErrorsOnly;ShowTimestamp reaper_ultraschall.vcxproj
popd
echo Done.

