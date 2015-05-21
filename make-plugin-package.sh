#!/bin/sh

# Create Ultraschall REAPER Plugin package
pkgbuild --root ./Modules/Plugin/UserPlugins/Payload --scripts ./Modules/Plugin/UserPlugins/Scripts --identifier fm.ultraschall.Plugin --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPlugin.pkg

# Create Ultraschall REAPER Plugin scripts package
pkgbuild --root ./Modules/Plugin/Scripts/Payload --scripts ./Modules/Plugin/Scripts/Scripts --identifier fm.ultraschall.Plugin.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/UltraschallPluginScripts.pkg

