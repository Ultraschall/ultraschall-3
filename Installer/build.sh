#!/bin/sh

export ULTRASCHALL_RELEASE=ULTRASCHALL-3.1.1-preview-1
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
pandoc --from=markdown --to=html --standalone --self-contained --css=../Tools/ultraschall.css --output=./Payload/README.html ../README.md
pandoc --from=markdown --to=html --standalone --self-contained --css=../Tools/ultraschall.css --output=./Payload/INSTALL.html ../INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --css=../Tools/ultraschall.css --output=./Payload/CHANGELOG.html ../CHANGELOG.md

# Copy uninstall script to payload directory
cp ../Scripts/Uninstall.command ./Payload/Uninstall.command

# Copy removal script to payload directory
cp ../Scripts/Remove\ legacy\ audio\ devices.command ./Payload/Remove\ legacy\ audio\ devices.command

# Copy resources to payload 'Add-ons' directory
cp ../Documentation/Keymap.pdf ./Payload/Add-ons/Ultraschall\ Keyboard\ Layout.pdf
cp ../Documentation/Keymap.pptx ./Payload/Add-ons/Ultraschall\ Keyboard\ Layout.pptx
cp ../Resources/Ultraschall\ App-Icon.png ./Payload/Add-ons/Ultraschall\ App-Icon.png
cp ../Resources/Ultraschall\ Webbanner.pdf ./Payload/Add-ons/Ultraschall\ Webbanner.pdf
cp ../Resources/Ultraschall\ Webbanner\ 400px.png ./Payload/Add-ons/Ultraschall\ Webbanner\ 400px.png
cp ../Resources/Ultraschall\ Webbanner\ 800px.png ./Payload/Add-ons/Ultraschall\ Webbanner\ 800px.png
cp ../Resources/Ultraschall\ Webbanner\ 2000px.jpg ./Payload/Add-ons/Ultraschall\ Webbanner\ 2000px.jpg

# Copy REAPER theme to payload directory
cp ../Themes/Ultraschall_3.1_MAC.ReaperConfigZip ./Payload/Ultraschall_3.1.ReaperConfigZip

# Copy background image to payload directory
mkdir ./Payload/.background
cp ./Resources/backgroundv3.png ./Payload/.background/background.png

# Create Ultraschall REAPER Extension package
# FIXME this now requires cmake
#xcodebuild -project ../Plugin/reaper_ultraschall/reaper_ultraschall.xcodeproj -configuration Release
#pkgbuild --root ../Plugin/reaper_ultraschall/Build/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin.Extension --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPluginExtension.pkg

# Create Ultraschall Soundboard package
pkgbuild --root ./3rdParty/Soundboard/Macintosh --identifier fm.ultraschall.Soundboard.Component --install-location /Library/Audio/Plug-Ins/Components ./Build/UltraschallSoundboard.pkg

# Create ITSR StudioLink package
pkgbuild --root ./3rdParty/StudioLink/Macintosh --identifier com.itsr.StudioLink.Components --install-location /Library/Audio/Plug-Ins/Components ./Build/StudioLink.pkg

# Create SWS REAPER Plugin Extension package
chmod 755 ./3rdParty/SWS/Macintosh/UserPlugins/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/UserPlugins/Payload --scripts ./3rdParty/SWS/Macintosh/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.9.6.pkg

# Create SWS REAPER Plugin Scripts package
chmod 755 ./3rdParty/SWS/Macintosh/Scripts/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/Scripts/Payload --scripts ./3rdParty/SWS/Macintosh/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.9.6.pkg

# Create Ultraschall Resources package
pkgbuild --root ../Plugin/Resources --identifier fm.ultraschall.Resources --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallResources.pkg

# Create Ultraschall Soundflower Uninstaller package
pkgbuild --scripts ../Tools/SoundflowerUninstaller/Scripts --nopayload --identifier fm.ultraschall.SoundflowerUninstaller ./Build/UltraschallSoundflowerUninstaller.pkg

# Copy Ultraschall Hub package
cp ./3rdParty/Hub/UltraschallHub-2015-11-12.pkg ./Payload/UltraschallHub.pkg

# Create preliminary unsigned installer package
productbuild --distribution ./Scripts/distribution.xml --resources ./Resources --package-path ./Build ./Payload/Ultraschall-unsigned.pkg

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

echo Creating disk layout...
echo '
   tell application "Finder"
     tell disk "ULTRASCHALL-3.1.1-preview-1.intermediate"
           open
           set current view of container window to icon view
           set toolbar visible of container window to false
           set statusbar visible of container window to false
           set the bounds of container window to {100, 100, 800, 540}
           set viewOptions to the icon view options of container window
           set arrangement of viewOptions to not arranged
           set background picture of viewOptions to file ".background:background.png"
           set position of item "ULTRASCHALL-3.1.1-alpha1.pkg" of container window to {50, 30}
           set position of item "Ultraschall_3.1.ReaperConfigZip" of container window to {200, 30}
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
echo done.

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
rm -rf ./Build
