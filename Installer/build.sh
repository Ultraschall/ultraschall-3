#!/bin/sh

export ULTRASCHALL_RELEASE=ULTRASCHALL-3.2-build495
export ULTRASCHALL_RELEASE_DISK_READ_WRITE=$ULTRASCHALL_RELEASE.readwrite.dmg
export ULTRASCHALL_RELEASE_DISK_READ_ONLY=$ULTRASCHALL_RELEASE.dmg
export ULTRASCHALL_RELEASE_INTERMEDIATE=$ULTRASCHALL_RELEASE.intermediate

# Cleanup old installer image
if [ -f ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY ]; then
  rm -f ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY
fi

# Cleanup temporary _intermediate directory
if [ -d ./_intermediate ]; then
  rm -rf ._intermediate
fi
mkdir ./_intermediate

# Cleanup temporary _build directory
# if [ -d ./_build ]; then
#   rm -rf ./_build
# fi
mkdir -p ./_build

# Cleanup temporary _payload directory
if [ -d ./_payload ]; then
  rm -rf ./_payload
fi
mkdir -p ./_payload
mkdir -p ./_payload/Add-ons

# Build and copy release notes to _payload directory
pandoc --from=markdown --to=html --standalone --self-contained --quiet --css=../Tools/ultraschall.css --output=./_payload/README.html ../Docs/Release/README.md
pandoc --from=markdown --to=html --standalone --self-contained --quiet --css=../Tools/ultraschall.css --output=./_payload/INSTALL.html ../Docs/Release/INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --quiet --css=../Tools/ultraschall.css --output=./_payload/CHANGELOG.html ../Docs/Release/CHANGELOG.md

# Copy uninstall script to _payload directory
cp ../Scripts/Uninstall.command ./_payload/Uninstall.command

# Copy removal script to _payload directory
cp ../Scripts/Remove\ legacy\ audio\ devices.command ./_payload/Remove\ legacy\ audio\ devices.command

# Copy resources to _payload 'Add-ons' directory
cp ../Docs/Release/Keymap.pdf ./_payload/Add-ons/Ultraschall\ Keyboard\ Layout.pdf
cp ../Docs/Release/Keymap.pptx ./_payload/Add-ons/Ultraschall\ Keyboard\ Layout.pptx
cp ../Resources/Ultraschall\ App-Icon.png ./_payload/Add-ons/Ultraschall\ App-Icon.png
cp ../Resources/Ultraschall\ Webbanner.pdf ./_payload/Add-ons/Ultraschall\ Webbanner.pdf
cp ../Resources/Ultraschall\ Webbanner\ 400px.png ./_payload/Add-ons/Ultraschall\ Webbanner\ 400px.png
cp ../Resources/Ultraschall\ Webbanner\ 800px.png ./_payload/Add-ons/Ultraschall\ Webbanner\ 800px.png
cp ../Resources/Ultraschall\ Webbanner\ 2000px.jpg ./_payload/Add-ons/Ultraschall\ Webbanner\ 2000px.jpg

# Copy REAPER theme to _payload directory
cp ../Themes/Ultraschall_3.1_MAC.ReaperConfigZip ./_payload/Ultraschall_3.1.ReaperConfigZip

# Copy background image to _payload directory
mkdir ./_payload/.background
cp ./Resources/backgroundv3.png ./_payload/.background/background.png

# Create Ultraschall REAPER Extension package
cd ./_build
cmake -G "Xcode" -DCMAKE_BUILD_TYPE=Release ../../Plugin
cmake --build . --target reaper_ultraschall --config Release
cd ..
pkgbuild --root ./_build/src/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin.Extension --install-location /Library/Application\ Support/REAPER/UserPlugins ./_build/UltraschallPlugin.pkg

# Download current Ultraschall API files
git clone https://github.com/Ultraschall/ultraschall-portable.git ./_build/ultraschall-portable
mkdir -p ./_build/api_root/ultraschall_api
cp -r ./_build/ultraschall-portable/UserPlugins/ultraschall_api ./_build/api_root
rm -rf ./_build/ultraschall-portable

# Create Ultraschall API package
pkgbuild --root ./_build/api_root --identifier fm.ultraschall.api --install-location /Library/Application\ Support/REAPER/UserPlugins ./_build/UltraschallAPI.pkg

# Create Ultraschall Soundboard package
pkgbuild --root ./3rdParty/Soundboard/Macintosh --identifier fm.ultraschall.Soundboard.Component --install-location /Library/Audio/Plug-Ins/Components ./_build/UltraschallSoundboard.pkg

# Create ITSR StudioLink package
pkgbuild --root ./3rdParty/StudioLink/Macintosh --identifier com.itsr.StudioLink.Components --install-location /Library/Audio/Plug-Ins/Components ./_build/StudioLink.pkg

# Create SWS REAPER Plugin Extension package
chmod 755 ./3rdParty/SWS/Macintosh/UserPlugins/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/UserPlugins/Payload --scripts ./3rdParty/SWS/Macintosh/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./_build/SWS_Extension-2.10.0.pkg

# Create SWS REAPER Plugin Scripts package
chmod 755 ./3rdParty/SWS/Macintosh/Scripts/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/Scripts/Payload --scripts ./3rdParty/SWS/Macintosh/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./_build/SWS_ExtensionScripts-2.10.0.pkg

# Create Ultraschall Resources package
pkgbuild --root ../Resources --identifier fm.ultraschall.Resources --install-location /Library/Application\ Support/Ultraschall ./_build/UltraschallResources.pkg

# Create Ultraschall Soundflower Uninstaller package
pkgbuild --scripts ../Tools/SoundflowerUninstaller/Scripts --nopayload --identifier fm.ultraschall.SoundflowerUninstaller ./_build/UltraschallSoundflowerUninstaller.pkg

# Copy Ultraschall Hub package
cp ./3rdParty/Hub/UltraschallHub-2015-11-12.pkg ./_payload/UltraschallHub.pkg

# Create preliminary unsigned installer package
productbuild --distribution ./Scripts/distribution.xml --resources ./Resources --package-path ./_build ./_payload/Ultraschall-unsigned.pkg

# Create final signed installer package
productsign --sign "Developer ID Installer: Heiko Panjas (8J2G689FCZ)" ./_payload/Ultraschall-unsigned.pkg ./_payload/$ULTRASCHALL_RELEASE.pkg
rm -f ./_payload/Ultraschall-unsigned.pkg

# Create installer disk image
hdiutil create -format UDRW -srcfolder ./_payload -fs HFS+ -volname $ULTRASCHALL_RELEASE ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

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
     tell disk "ULTRASCHALL-3.2-build495.intermediate"
           open
           set current view of container window to icon view
           set toolbar visible of container window to false
           set statusbar visible of container window to false
           set the bounds of container window to {100, 100, 800, 540}
           set viewOptions to the icon view options of container window
           set arrangement of viewOptions to not arranged
           set background picture of viewOptions to file ".background:background.png"
           set position of item "ULTRASCHALL-3.2-build495.pkg" of container window to {50, 30}
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
rm -rf ./_payload
rm -rf ./_intermediate
# rm -rf ./_build
