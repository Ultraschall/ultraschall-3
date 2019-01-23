@echo off

if not exist "_build" (
    mkdir _build && pushd _build
    cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug -Thost=x64 ../
    popd
)

pushd _build
cmake --build . --target reaper_ultraschall --config Debug -j
popd
