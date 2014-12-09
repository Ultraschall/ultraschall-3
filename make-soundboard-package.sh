#!/bin/sh

# Create Ultraschall Soundboard package
pkgbuild --root ./Modules/Soundboard/Payload/VST --identifier fm.ultraschall.Soundboard --install-location /Library/Audio/Plug-ins/VST ./Build/UltraschallSoundboard-1.2.pkg

# Create Ultraschall Soundboard scripts package
pkgbuild --root ./Modules/Soundboard/Payload/Scripts --identifier fm.ultraschall.Soundboard.Scripts --install-location /Library ./Build/UltraschallSoundboardScripts-1.2.pkg



