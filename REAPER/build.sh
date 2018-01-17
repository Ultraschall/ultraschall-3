#!/bin/sh
git submodule init
git submodule update

cd Plugin/reaper_ultraschall
xcodebuild -configuration Release
cd ../..


