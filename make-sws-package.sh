#!/bin/sh

# Create SWS REAPER Plugin package
pkgbuild --root ./Modules/SWS/Payload/UserPlugins --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.5.0.0.pkg

# Create SWS REAPER Plugin Scripts package
pkgbuild --root ./Modules/SWS/Payload/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.5.0.0.pkg

