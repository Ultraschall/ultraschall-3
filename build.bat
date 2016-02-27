@echo off

set DEFAULT_BUILD_TARGET=Rebuild
set DEFAULT_BUILD_CONFIG=Release
set DEFAULT_ZLIB_BUILD_CONFIG=ReleaseWithoutAsm
set DEFAULT_BUILD_PLATFORM=64
set DEFAULT_BUILD_PLATFORM_NAME=x64

set BUILD_TARGET=%DEFAULT_BUILD_TARGET%
set BUILD_CONFIG=%DEFAULT_BUILD_CONFIG%
set ZLIB_BUILD_CONFIG=%DEFAULT_ZLIB_BUILD_CONFIG%
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

if "%2"=="debug" set ZLIB_BUILD_CONFIG=Debug
if "%2"=="Debug" set ZLIB_BUILD_CONFIG=Debug

if "%2"=="release" set BUILD_CONFIG=Release
if "%2"=="Release" set BUILD_CONFIG=Release

if "%2"=="release" set ZLIB_BUILD_CONFIG=ReleaseWithoutAsm
if "%2"=="Release" set ZLIB_BUILD_CONFIG=ReleaseWithoutAsm

if "%3"=="x64" set BUILD_PLATFORM=64
if "%3"=="x64" set BUILD_PLATFORM_NAME=x64

if "%3"=="x86" set BUILD_PLATFORM=
if "%3"=="x86" set BUILD_PLATFORM_NAME=x86

echo "Updating Submodules..."
git submodule init > nul
git submodule update > nul

pushd Plugin\reaper_ultraschall\Submodules\zlib\contrib\vstudio\vc11
git checkout master > nul
git pull > nul
echo "%BUILD_TARGET%ing zlib library... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)"
msbuild /target:%BUILD_TARGET% /property:configuration=%ZLIB_BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /clp:ErrorsOnly;ShowTimestamp /m /nologo zlibstat.vcxproj  
popd

pushd Plugin\reaper_ultraschall\Submodules\minizip
git checkout master > nul
git pull > nul
popd
echo "Done."

:build_submodules

:build_modules
echo "%BUILD_TARGET%ing Ultraschall REAPER Plugin... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)"
pushd Plugin\reaper_ultraschall
msbuild /target:%BUILD_TARGET% /property:configuration=%BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /clp:ErrorsOnly;ShowTimestamp /m /nologo reaper_ultraschall.vcxproj
popd
echo "Done."
