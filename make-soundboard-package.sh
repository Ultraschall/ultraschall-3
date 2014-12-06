#!/bin/sh

# Create Ultraschall Soundboard package
pkgbuild --root ./Modules/Soundboard/Payload/VST --ownership preserve --identifier fm.ultraschall.Soundboard --install-location ~/Library/Audio/Plug-ins/VST ./Build/UltraschallSoundboard-1.2.pkg

# Create Ultraschall Soundboard scripts package
pkgbuild --root ./Modules/Soundboard/Payload/Scripts --ownership preserve --identifier fm.ultraschall.Soundboard.Scripts --install-location ~/Documents ./Build/UltraschallSoundboardScripts-1.2.pkg



