# WINDOWS 10 PRO X64

## CHECK-OUT ULTRASCHALL

```
$ git clone --recurse-submodules https://github.com/Ultraschall/ultraschall-3.git
```

## BUILD THE SUBMODULES

### ZLIB

```
$ pushd ultraschall-3/Plugin/3rd_party/zlib

$ git checkout tags/zlib-1.2.8 -b v1.2.8
$ git submodule update --init --recursive

$ mkdir build
$ pushd build
$ cmake -G"Visual Studio 15 2017 Win64" -Thost=x64 ../
$ cmake --build . --target zlibstatic --config Debug -j
$ popd

$ popd
```

### CURL

```
$ pushd ultraschall-3/Plugin/3rd_party/curl

$ git checkout tags/libcurl-7.61.1 -b v7.61.1
$ git submodule update --init --recursive

$ mkdir build
$ pushd build
$ cmake -G"Visual Studio 15 2017 Win64" -DBUILD_CURL_EXE=OFF -DBUILD_SHARED_LIBS=OFF -DCURL_STATIC_CRT=ON -DENABLE_IPV6=ON -D CMAKE_USE_WINSSL=ON -Thost=x64 ../
$ cmake --build . --target libcurl --config Debug -j
$ popd

$ popd
```

### TAGLIB

```
$ pushd ultraschall-3/Plugin/3rd_party/taglib

$ git checkout tags/v1.11.1 -b v1.11.1
$ git submodule update --init --recursive

$ mkdir build
$ pushd build
$ cmake -G"Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS=OFF -DENABLE_STATIC_RUNTIME=ON -Thost=x64 ../
$ cmake --build . --target tag --config Debug -j
$ popd

$ popd
```

### LIBMP4V2

```
$ pushd ultraschall-3/Plugin/3rd_party/mp4v2

$ git checkout tags/Cmac2018.0.4.105409 -b Cmac2018.0.4.105409
$ git submodule update --init --recursive

$ pushd mp4v2-Win
$ msbuild mp4v2.sln /target:build /property:configuration=Debug /property:platform=x64 /property:platformtoolset=v141 /property:WinSDKVersion=10.0.17763.0 /property:WindowsTargetPlatformVersion=10.0.17763.0 /property:configurationtype=StaticLibrary
$ popd

$ popd
```

### WXWIDGETS

```
$ pushd ultraschall-3/Plugin/3rd_party/wxwidgets

$ git checkout tags/v3.1.2 -b v3.1.2
$ git submodule update --init --recursive
$ copy include/wx/msw/setup0.h include/wx/msw/setup.h

$ pushd build/msw
$ nmake /f makefile.vc BUILD=debug
$ popd

$ popd
```

## SETUP THE BUILD ENVIRONMENT

```
$ mkdir build
$ cd build
$ cmake -G"Visual Studio 15 2017 Win64" ../
```

## BUILD THE ULTRASCHALL PLUGIN FOR REAPER

```
$ cmake --build . --target reaper_ultraschall --config Debug -j
```
