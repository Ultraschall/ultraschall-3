#!/bin/sh
git submodule init
git submodule update

cd Plugin/reaper_ultraschall/Submodules/minizip
git checkout 2.2
git pull
cd ../../../../

cd Plugin/reaper_ultraschall
xcodebuild -configuration Release
cd ../..


