#!/bin/sh

# Create SWS REAPER Plugin package
pkgbuild --root ./Modules/SWS/UserPlugins/Payload --scripts ./Modules/SWS/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.7.0.pkg

# Create SWS REAPER Plugin Scripts package
pkgbuild --root ./Modules/SWS/Scripts/Payload --scripts ./Modules/SWS/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.7.0.pkg

