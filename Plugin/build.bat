@echo off

if not exist "build" (
    mkdir build && pushd build
    cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug -Thost=x64 ../
    popd
)

pushd build
cmake --build . --target reaper_ultraschall --config Debug -j
popd
