#!/bin/sh

# Create Ultraschall REAPER Plugin package
pkgbuild --root ./Modules/Plugin/Payload/UserPlugins --ownership preserve --identifier fm.ultraschall.Plugin --install-location ~/Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPlugin-1.2.pkg

# Create Ultraschall REAPER Plugin scripts package
pkgbuild --root ./Modules/Plugin/Payload/Scripts --ownership preserve --identifier fm.ultraschall.Plugin.Scripts --install-location ~/Library/Application\ Support/REAPER/Scripts ./Build/UltraschallPluginScripts-1.2.pkg

