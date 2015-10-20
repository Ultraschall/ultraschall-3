#!/bin/sh

export ULTRASCHALL_RELEASE=Ultraschall-2.0-alpha2
export ULTRASCHALL_RELEASE_DISK1=$ULTRASCHALL_RELEASE.dmg

# Cleanup old installer image
if [ -f ./$ULTRASCHALL_RELEASE_DISK1 ]; then
	rm -f ./$ULTRASCHALL_RELEASE_DISK1
fi

# Cleanup temporary build directory
if [ -d ./Build ]; then
	rm -rf ./Build
fi
mkdir ./Build

# Cleanup temporary payload directory
if [ -d ./Payload ]; then
	rm -rf ./Payload
fi
mkdir ./Payload
mkdir ./Payload/Resources

# Copy release notes to payload directory
cp ../REAPER/Documentation/Rams\ Edition\ Release-Poster.pdf ./Payload/Resources/Rams\ Edition\ Release-Poster.pdf
cp ../REAPER/Documentation/Rams\ Edition\ Release-Poster.png ./Payload/Resources/Rams\ Edition\ Release-Poster.png
cp ../REAPER/Documentation/Ultraschall\ Install\ and\ Release\ Notes.html ./Payload/Ultraschall\ Install\ and\ Release\ Notes.html

# Copy uninstall script to payload directory
cp ../REAPER/Scripts/Uninstall.command ./Payload/Uninstall.command

# Copy resources to payload directory
cp ../REAPER/Resources/Ultraschall\ Colorset.SWSColor ./Payload/Resources/Ultraschall\ Colorset.SWSColor
cp ../REAPER/Resources/Ultraschall\ Microbanner\ 80x15.png ./Payload/Resources/Ultraschall\ Microbanner\ 80x15.png
cp ../REAPER/Resources/Ultraschall\ Webbanner.png ./Payload/Resources/Ultraschall\ Webbanner.png

# Copy REAPER theme to payload directory
cp ../REAPER/Themes/Ultraschall_2.0.ReaperConfigZip ./Payload/Ultraschall_2.0.ReaperConfigZip

# Create Ultraschall REAPER Plugin package
xcodebuild -project ../REAPER/Plugin/reaper_ultraschall/reaper_ultraschall.xcodeproj -configuration Release
pkgbuild --root ../REAPER/Plugin/reaper_ultraschall/Build/Products/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPlugin.pkg

# Create Ultraschall REAPER Plugin scripts package
pkgbuild --root ../REAPER/Plugin/Scripts --scripts ./Scripts/Scripts --identifier fm.ultraschall.Plugin.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/UltraschallPluginScripts.pkg

# Create Ultraschall Soundboard package
pkgbuild --root ./3rdParty/Soundboard/VST/Payload --identifier fm.ultraschall.Soundboard --install-location /Library/Audio/Plug-ins/VST ./Build/UltraschallSoundboard.pkg

# Create Ultraschall Soundboard scripts package
pkgbuild --root ./3rdParty/Soundboard/Extras/Payload --identifier fm.ultraschall.Soundboard.Scripts --install-location /Library ./Build/UltraschallSoundboardScripts.pkg

# Create SWS REAPER Plugin package
pkgbuild --root ./3rdParty/SWS/UserPlugins/Payload --scripts ./3rdParty/SWS/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.8.1.pkg

# Create SWS REAPER Plugin Scripts package
pkgbuild --root ./3rdParty/SWS/Scripts/Payload --scripts ./3rdParty/SWS/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.8.1.pkg

# Create Ultraschall Resources package
pkgbuild --root ../REAPER/Plugin/Resources --identifier fm.ultraschall.Resources --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallResources.pkg

# Create Ultraschall Soundflower Uninstaller package
pkgbuild --root ../REAPER/Tools/SoundflowerUninstaller/Payload --scripts ../REAPER/Tools/SoundflowerUninstaller/Scripts --nopayload --identifier fm.ultraschall.SoundflowerUninstaller ./Build/UltraschallSoundflowerUninstaller.pkg

# Create preliminary unsigned installer package 
productbuild --distribution ./Scripts/distribution.xml --resources ./Resources --package-path ./Build ./Payload/Ultraschall-unsigned.pkg
rm -rf ./Build

# Create final signed installer package
productsign --sign "Developer ID Installer: Heiko Panjas (8J2G689FCZ)" ./Payload/Ultraschall-unsigned.pkg ./Payload/Ultraschall-2.0.pkg
rm -f ./Payload/Ultraschall-unsigned.pkg

# Create installer image
hdiutil create -srcfolder ./Payload -fs HFS+ -volname $ULTRASCHALL_RELEASE ./$ULTRASCHALL_RELEASE_DISK1
rm -rf ./Payload



