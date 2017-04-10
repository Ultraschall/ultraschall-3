#!/bin/sh

export ULTRASCHALL_RELEASE=Ultraschall-3.0.3-beta8
export ULTRASCHALL_RELEASE_DISK_READ_WRITE=$ULTRASCHALL_RELEASE.readwrite.dmg
export ULTRASCHALL_RELEASE_DISK_READ_ONLY=$ULTRASCHALL_RELEASE.dmg
export ULTRASCHALL_RELEASE_INTERMEDIATE=$ULTRASCHALL_RELEASE.intermediate

# Cleanup old installer image
if [ -f ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY ]; then
	rm -f ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY
fi

# Cleanup temporary intermediate directory
if [ -d ./Intermediate ]; then
	rm -rf .Intermediate
fi
mkdir ./Intermediate

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
mkdir ./Payload/Add-ons

# Build and copy release notes to payload directory
pandoc --from=markdown --to=html --standalone --self-contained --css=../REAPER/Tools/ultraschall.css --output=./Payload/README.html ../REAPER/README.md
pandoc --from=markdown --to=html --standalone --self-contained --css=../REAPER/Tools/ultraschall.css --output=./Payload/INSTALL.html ../REAPER/INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --css=../REAPER/Tools/ultraschall.css --output=./Payload/CHANGELOG.html ../REAPER/CHANGELOG.md

# Copy uninstall script to payload directory
cp ../REAPER/Scripts/Uninstall.command ./Payload/Uninstall.command

# Copy removal script to payload directory
cp ../REAPER/Scripts/Remove\ legacy\ audio\ devices.command ./Payload/Remove\ legacy\ audio\ devices.command

# Copy resources to payload 'Add-ons' directory
cp ../REAPER/Documentation/Keymap.pdf ./Payload/Add-ons/Ultraschall\ Keyboard\ Layout.pdf
cp ../REAPER/Documentation/Keymap.pptx ./Payload/Add-ons/Ultraschall\ Keyboard\ Layout.pptx
cp ../REAPER/Resources/Ultraschall\ Microbanner\ 80x15.png ./Payload/Add-ons/Ultraschall\ Microbanner\ 80x15.png
cp ../REAPER/Resources/Ultraschall\ Webbanner.png ./Payload/Add-ons/Ultraschall\ Webbanner.png

# Copy REAPER theme to payload directory
cp ../REAPER/Themes/Ultraschall_3.0_MAC.ReaperConfigZip ./Payload/Ultraschall_3.0.ReaperConfigZip

# Copy background image to payload directory
mkdir ./Payload/.background
cp ./Resources/backgroundv3.png ./Payload/.background/background.png

# Create Ultraschall REAPER Extension package
xcodebuild -project ../REAPER/Plugin/reaper_ultraschall/reaper_ultraschall.xcodeproj -configuration Release
pkgbuild --root ../REAPER/Plugin/reaper_ultraschall/Build/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin.Extension --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPluginExtension.pkg

# Create Ultraschall Soundboard package
pushd ../Soundboard
./Build/build_mac_plugin.sh
popd

# Create Ultraschall Soundboard package
# mv ../Soundboard/Files/AudioUnit/
pkgbuild --root ../Soundboard/Files/AudioUnit --identifier fm.ultraschall.Soundboard.Component --install-location /Library/Audio/Plug-Ins/Components ./Build/UltraschallSoundboard.pkg

# Create Ultraschall Soundboard extras package
pkgbuild --root ../Soundboard/Extras --identifier fm.ultraschall.Soundboard.Extras --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallSoundboardExtras.pkg

# Create ITSR StudioLink package
pkgbuild --root ./3rdParty/StudioLink/Macintosh --identifier com.itsr.StudioLink.Components --install-location /Library/Audio/Plug-Ins/Components ./Build/StudioLink.pkg

# Create LAME package
pkgbuild --root ./3rdParty/LAME/Macintosh --identifier net.sf.lame.Encoder --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/LAME.pkg

# Create SWS REAPER Plugin Extension package
chmod 755 ./3rdParty/SWS/Macintosh/UserPlugins/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/UserPlugins/Payload --scripts ./3rdParty/SWS/Macintosh/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.8.8.pkg

# Create SWS REAPER Plugin Scripts package
chmod 755 ./3rdParty/SWS/Macintosh/Scripts/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/Scripts/Payload --scripts ./3rdParty/SWS/Macintosh/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.8.8.pkg

# Create Ultraschall Resources package
pkgbuild --root ../REAPER/Plugin/Resources --identifier fm.ultraschall.Resources --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallResources.pkg

# Create Ultraschall Soundflower Uninstaller package
pkgbuild --scripts ../REAPER/Tools/SoundflowerUninstaller/Scripts --nopayload --identifier fm.ultraschall.SoundflowerUninstaller ./Build/UltraschallSoundflowerUninstaller.pkg

# Copy Ultraschall Hub package
cp ./3rdParty/Hub/UltraschallHub-2015-11-12.pkg ./Payload/UltraschallHub.pkg

# Create preliminary unsigned installer package
productbuild --distribution ./Scripts/distribution.xml --resources ./Resources --package-path ./Build ./Payload/Ultraschall-unsigned.pkg
rm -rf ./Build

# Create final signed installer package
productsign --sign "Developer ID Installer: Heiko Panjas (8J2G689FCZ)" ./Payload/Ultraschall-unsigned.pkg ./Payload/$ULTRASCHALL_RELEASE.pkg
rm -f ./Payload/Ultraschall-unsigned.pkg

# Create installer disk image
hdiutil create -format UDRW -srcfolder ./Payload -fs HFS+ -volname $ULTRASCHALL_RELEASE ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

# Mount installer disk image
mkdir -p ./$ULTRASCHALL_RELEASE_INTERMEDIATE
hdiutil attach -mountpoint ./$ULTRASCHALL_RELEASE_INTERMEDIATE ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

# Create signature on uninstall script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./$ULTRASCHALL_RELEASE_INTERMEDIATE/Uninstall.command

# Create signature on removal script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./$ULTRASCHALL_RELEASE_INTERMEDIATE/Remove\ legacy\ audio\ devices.command

echo '
   tell application "Finder"
     tell disk "'$ULTRASCHALL_RELEASE_INTERMEDIATE'"
           open
           set current view of container window to icon view
           set toolbar visible of container window to false
           set statusbar visible of container window to false
           set the bounds of container window to {100, 100, 800, 540}
           set viewOptions to the icon view options of container window
           set arrangement of viewOptions to not arranged
           set background picture of viewOptions to file ".background:background.png"
           set position of item "Ultraschall-3.0.3-beta8.pkg" of container window to {50, 30}
           set position of item "Ultraschall_3.0.ReaperConfigZip" of container window to {200, 30}
           set position of item "README.html" of container window to {50, 135}
           set position of item "INSTALL.html" of container window to {200, 135}
           set position of item "CHANGELOG.html" of container window to {350, 135}
           set position of item "UltraschallHub.pkg" of container window to {50, 220}
           set position of item "Add-ons" of container window to {200, 220}
           set position of item "Uninstall.command" of container window to {50, 320}
           set position of item "Remove legacy audio devices.command" of container window to {200, 320}
           close
           open
           update without registering applications
           delay 2
     end tell
   end tell
' | osascript

sync

# Unmount installer disk image
hdiutil detach ./$ULTRASCHALL_RELEASE_INTERMEDIATE

# Convert installer disk image
hdiutil convert -format UDRO -o ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

# Clean-up
rm -rf ./$ULTRASCHALL_RELEASE_INTERMEDIATE
rm -rf ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE
rm -rf ./Payload
rm -rf ./Intermediate
