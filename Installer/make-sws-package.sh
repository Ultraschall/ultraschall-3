#!/bin/sh

if [ ! -d ./Build ]; then
  mkdir ./Build
fi

# wget http://sws.mj-s.com/download/featured/sws-v2.7.0.0.dmg
# mv sws-v2.7.0.0.dmg ./build/sws-v2.7.0.0.dmg
hdiutil mount ./build/sws-v2.7.0.0.dmg 

if [ ! -d ./Build/Scripts/Payload ]; then
  mkdir ./Build/Scripts/Payload
fi
cp /Volumes/SWS_Extension/.sws_python.py ./Build/Scripts/Payload/sws_python.py
cp /Volumes/SWS_Extension/.sws_python32.py ./Build/Scripts/Payload/sws_python32.py
cp /Volumes/SWS_Extension/.sws_python64.py ./Build/Scripts/Payload/sws_python64.py

if [ ! -d ./Build/UserPlugins/Payload ]; then
  mkdir ./Build/UserPlugins/Payload
fi
cp /Volumes/SWS_Extension/reaper_sws.dylib ./Build/UserPlugins/Payload/reaper_sws.dylib
cp /Volumes/SWS_Extension/.whatsnew.txt ./Build/UserPlugins/Payload/reaper_sws_whatsnew.txt
cp /Volumes/SWS_Extension/license.txt ./Build/UserPlugins/Payload/license.txt


hdiutil unmount /Volumes/SWS_Extension

# Create SWS REAPER Plugin package
#pkgbuild --root ./Modules/SWS/UserPlugins/Payload --scripts ./Modules/SWS/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.6.0.pkg

# Create SWS REAPER Plugin Scripts package
#pkgbuild --root ./Modules/SWS/Scripts/Payload --scripts ./Modules/SWS/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.6.0.pkg

