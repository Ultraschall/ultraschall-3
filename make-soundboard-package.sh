#!/bin/sh

# Create Ultraschall Soundboard package
pkgbuild --root ./Modules/Soundboard/VST/Payload --identifier fm.ultraschall.Soundboard --install-location /Library/Audio/Plug-ins/VST ./Build/UltraschallSoundboard-1.3beta1.pkg

# Create Ultraschall Soundboard scripts package
pkgbuild --root ./Modules/Soundboard/Extras/Payload --identifier fm.ultraschall.Soundboard.Scripts --install-location /Library ./Build/UltraschallSoundboardScripts-1.3beta1.pkg



