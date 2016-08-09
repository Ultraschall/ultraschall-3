#!/bin/sh

export ULTRASCHALL_RELEASE=Ultraschall-2.2.2-PRE-RELEASE-2
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
cp ../REAPER/Documentation/Rams\ Edition\ Release-Poster.pdf ./Payload/Add-ons/Rams\ Edition\ Release-Poster.pdf
cp ../REAPER/Documentation/Rams\ Edition\ Release-Poster.png ./Payload/Add-ons/Rams\ Edition\ Release-Poster.png
cp ../REAPER/Resources/Ultraschall\ Colorset.SWSColor ./Payload/Add-ons/Ultraschall\ Colorset.SWSColor
cp ../REAPER/Resources/Ultraschall\ Microbanner\ 80x15.png ./Payload/Add-ons/Ultraschall\ Microbanner\ 80x15.png
cp ../REAPER/Resources/Ultraschall\ Webbanner.png ./Payload/Add-ons/Ultraschall\ Webbanner.png
cp ../REAPER/Plugin/Resources/Ultraschall\ Reaper\ Splash\ Screen.png ./Payload/Add-ons/Ultraschall\ Reaper\ Splash\ Screen.png

# Copy REAPER theme to payload directory
cp ../REAPER/Themes/Ultraschall_2.2_MAC.ReaperConfigZip ./Payload/Ultraschall_2.2.ReaperConfigZip

# Create Ultraschall REAPER Extension package
xcodebuild -project ../REAPER/Plugin/reaper_ultraschall/reaper_ultraschall.xcodeproj -configuration Release
pkgbuild --root ../REAPER/Plugin/reaper_ultraschall/Build/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin.Extension --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPluginExtension.pkg

# Create Ultraschall REAPER Plugin scripts package
mkdir -p ./Intermediate/Plugin/Scripts
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_delete_last_marker.lua ./Intermediate/Plugin/Scripts/ultraschall_delete_last_marker.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_mute_envelope.lua ./Intermediate/Plugin/Scripts/ultraschall_mute_envelope.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_safemode_start_pause.lua ./Intermediate/Plugin/Scripts/ultraschall_safemode_start_pause.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_safemode_start_stop.lua ./Intermediate/Plugin/Scripts/ultraschall_safemode_start_stop.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track1.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track1.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track2.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track2.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track3.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track3.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track4.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track4.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track5.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track5.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track6.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track6.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track7.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track7.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_track8.lua ./Intermediate/Plugin/Scripts/ultraschall_select_track8.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_set_edit.lua ./Intermediate/Plugin/Scripts/ultraschall_set_edit.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_set_edit_past.lua ./Intermediate/Plugin/Scripts/ultraschall_set_edit_past.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_set_marker.lua ./Intermediate/Plugin/Scripts/ultraschall_set_marker.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_set_namedmarker.lua ./Intermediate/Plugin/Scripts/ultraschall_set_namedmarker.lua
cp ../REAPER/Plugin/Scripts/Shared/ultraschall_select_studiolink.lua ./Intermediate/Plugin/Scripts/ultraschall_select_studiolink.lua

pkgbuild --root ./Intermediate/Plugin/Scripts --scripts ./Scripts/Scripts --identifier fm.ultraschall.Plugin.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/UltraschallPluginScripts.pkg

# Create Ultraschall Soundboard package
pushd ../Soundboard
./Build/build_mac_plugin.sh
popd

# Create Ultraschall Soundboard package
# mv ../Soundboard/Files/AudioUnit/
pkgbuild --root ../Soundboard/Files/AudioUnit --identifier fm.ultraschall.Soundboard.Component --install-location /Library/Audio/Plug-ins/Components ./Build/UltraschallSoundboard.pkg

# Create Ultraschall Soundboard extras package
pkgbuild --root ../Soundboard/Extras --identifier fm.ultraschall.Soundboard.Extras --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallSoundboardExtras.pkg

# Create Ultraschall StudioLink package
pkgbuild --root ./3rdParty/StudioLink/Macintosh --identifier com.itsr.StudioLink.Components --install-location /Library/Audio/Plug-ins/Components ./Build/StudioLink.pkg

# Create SWS REAPER Plugin Extension package
chmod 755 ./3rdParty/SWS/Macintosh/UserPlugins/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/UserPlugins/Payload --scripts ./3rdParty/SWS/Macintosh/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.8.3.pkg

# Create SWS REAPER Plugin Scripts package
chmod 755 ./3rdParty/SWS/Macintosh/Scripts/Scripts/preinstall
pkgbuild --root ./3rdParty/SWS/Macintosh/Scripts/Payload --scripts ./3rdParty/SWS/Macintosh/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.8.3.pkg

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

# Create installer image
hdiutil create -format UDRW -srcfolder ./Payload -fs HFS+ -volname $ULTRASCHALL_RELEASE ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

# Mount installer image
mkdir -p ./$ULTRASCHALL_RELEASE_INTERMEDIATE
hdiutil attach -mountpoint ./$ULTRASCHALL_RELEASE_INTERMEDIATE ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE

# Create signature on uninstall script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./$ULTRASCHALL_RELEASE_INTERMEDIATE/Uninstall.command

# Create signature on removal script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./$ULTRASCHALL_RELEASE_INTERMEDIATE/Remove\ legacy\ audio\ devices.command

# Unmount installer image
hdiutil detach ./$ULTRASCHALL_RELEASE_INTERMEDIATE  

# Convert installer image
hdiutil convert -format UDRO -o ./$ULTRASCHALL_RELEASE_DISK_READ_ONLY ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE   

# Clean-up
rm -rf ./$ULTRASCHALL_RELEASE_INTERMEDIATE
Rm -rf ./$ULTRASCHALL_RELEASE_DISK_READ_WRITE
rm -rf ./Payload
rm -rf ./Intermediate
