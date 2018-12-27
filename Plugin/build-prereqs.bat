@echo off
pushd _ext

rem --------------------------------------------------------------------------
git clone https://github.com/winlibs/zlib.git zlib
pushd zlib
git checkout tags/zlib-1.2.8 -b v1.2.8
git submodule update --init --recursive
mkdir build && pushd build
cmake -G"Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=OFF -Thost=x64 ..\
cmake --build . --target zlibstatic --config Debug -j
popd
popd
rem --------------------------------------------------------------------------

rem --------------------------------------------------------------------------
git clone https://github.com/winlibs/cURL.git curl
pushd curl
git checkout tags/libcurl-7.61.1 -b v7.61.1
git submodule update --init --recursive
mkdir build && pushd build
cmake -G"Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=OFF -DBUILD_CURL_EXE=OFF -DENABLE_IPV6=ON -DCMAKE_USE_WINSSL=ON -Thost=x64 ..\
cmake --build . --target libcurl --config Debug -j
popd
popd
rem --------------------------------------------------------------------------

rem --------------------------------------------------------------------------
git clone https://github.com/taglib/taglib.git taglib
pushd taglib
git checkout tags/v1.11.1 -b v1.11.1
git submodule update --init --recursive
mkdir build && pushd build
cmake -G"Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=OFF -Thost=x64 ..\
cmake --build . --target tag --config Debug -j
popd
popd
rem --------------------------------------------------------------------------

rem --------------------------------------------------------------------------
git clone https://github.com/TechSmith/mp4v2.git mp4v2
pushd mp4v2
git checkout tags/Cmac2018.0.4.105409 -b Cmac2018.0.4.105409
git submodule update --init --recursive
pushd mp4v2-Win
msbuild mp4v2.sln /target:build /property:configuration=Debug /property:platform=x64 /property:platformtoolset=v141 /property:WinSDKVersion=10.0.17763.0 /property:WindowsTargetPlatformVersion=10.0.17763.0 /property:configurationtype=StaticLibrary /property:preprocessordefinitions=_CRT_SECURE_NO_WARNINGS
popd
popd
rem --------------------------------------------------------------------------

rem --------------------------------------------------------------------------
git clone https://github.com/wxWidgets/wxWidgets.git wxwidgets
pushd wxwidgets
git checkout tags/v3.1.2 -b v3.1.2
git submodule update --init --recursive
copy include\wx\msw\setup0.h include\wx\msw\setup.h
pushd build\msw
nmake /f makefile.vc BUILD=debug
popd
popd
rem --------------------------------------------------------------------------

popd
