@echo off

set DEFAULT_BUILD_TARGET=Rebuild
set DEFAULT_BUILD_CONFIG=Release
set DEFAULT_BUILD_PLATFORM=64
set DEFAULT_BUILD_PLATFORM_NAME=x64

set DEFAULT_ZLIB_BUILD_CONFIG=ReleaseWithoutAsm
set DEFAULT_CURL_BUILD_CONFIG="LIB Release - DLL Windows SSPI"

set BUILD_TARGET=%DEFAULT_BUILD_TARGET%
set BUILD_CONFIG=%DEFAULT_BUILD_CONFIG%
set BUILD_PLATFORM=%DEFAULT_BUILD_PLATFORM%
set BUILD_PLATFORM_NAME=%DEFAULT_BUILD_PLATFORM_NAME%

set ZLIB_BUILD_CONFIG=%DEFAULT_ZLIB_BUILD_CONFIG%
set CURL_BUILD_CONFIG=%DEFAULT_CURL_BUILD_CONFIG%

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

if "%2"=="debug" set CURL_BUILD_CONFIG="LIB Debug - DLL Windows SSPI"
if "%2"=="Debug" set CURL_BUILD_CONFIG="LIB Debug - DLL Windows SSPI"

if "%2"=="release" set BUILD_CONFIG=Release
if "%2"=="Release" set BUILD_CONFIG=Release

if "%2"=="release" set ZLIB_BUILD_CONFIG=ReleaseWithoutAsm
if "%2"=="Release" set ZLIB_BUILD_CONFIG=ReleaseWithoutAsm

if "%2"=="release" set CURL_BUILD_CONFIG="LIB Release - DLL Windows SSPI"
if "%2"=="Release" set CURL_BUILD_CONFIG="LIB Release - DLL Windows SSPI"

if "%3"=="x64" set BUILD_PLATFORM=64
if "%3"=="x64" set BUILD_PLATFORM_NAME=x64

if "%3"=="x86" set BUILD_PLATFORM=
if "%3"=="x86" set BUILD_PLATFORM_NAME=x86

echo Updating Submodules...
git submodule init > nul
git submodule update > nul
echo Done.

echo %BUILD_TARGET%ing zlib library... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)
pushd Plugin\reaper_ultraschall\Submodules\zlib\contrib\vstudio\vc11
git checkout --quiet master > nul
git pull > nul
msbuild /nologo /maxcpucount /target:%BUILD_TARGET% /property:configuration=%ZLIB_BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /property:platformtoolset=v140 /clp:ErrorsOnly;ShowTimestamp zlibstat.vcxproj  
popd

echo %BUILD_TARGET%ing curl library... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)
pushd Plugin\reaper_ultraschall\Submodules\curl
git checkout --quiet master > nul
git pull > nul
pushd projects
call generate.bat vc14 > nul
pushd Windows\VC14\lib
msbuild /nologo /maxcpucount /target:%BUILD_TARGET% /property:configuration=%CURL_BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /clp:ErrorsOnly;ShowTimestamp libcurl.vcxproj   
popd
call generate -clean > nul
popd
popd
echo Done.

echo %BUILD_TARGET%ing Ultraschall REAPER Plugin... (%BUILD_CONFIG%, %BUILD_PLATFORM_NAME%)
pushd Plugin\reaper_ultraschall
msbuild /nologo /maxcpucount /target:%BUILD_TARGET% /property:configuration=%BUILD_CONFIG% /property:platform=%BUILD_PLATFORM_NAME% /clp:ErrorsOnly;ShowTimestamp reaper_ultraschall.vcxproj
popd
echo Done.

