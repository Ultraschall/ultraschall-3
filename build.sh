#!/bin/sh

export ULTRASCHALL_RELEASE=Ultraschall-2.1_prerelase_4
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
cp ../REAPER/Themes/Ultraschall_2.1.ReaperConfigZip ./Payload/Ultraschall_2.1.ReaperConfigZip

# Create Ultraschall REAPER Extension package
xcodebuild -project ../REAPER/Plugin/reaper_ultraschall/reaper_ultraschall.xcodeproj -configuration Release
pkgbuild --root ../REAPER/Plugin/reaper_ultraschall/Build/Release --scripts ./Scripts/Plugin --identifier fm.ultraschall.Plugin.Extension --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/UltraschallPluginExtension.pkg

# Create Ultraschall REAPER Plugin scripts package
pkgbuild --root ../REAPER/Plugin/Scripts --scripts ./Scripts/Scripts --identifier fm.ultraschall.Plugin.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/UltraschallPluginScripts.pkg

# Create Ultraschall Soundboard package
pushd ../Soundboard
./Build/build_mac_plugin.sh
popd

pkgbuild --root ../Soundboard/Files/VST --identifier fm.ultraschall.Soundboard.VST --install-location /Library/Audio/Plug-ins/VST ./Build/UltraschallSoundboardVST.pkg

# Create Ultraschall Soundboard extras package
pkgbuild --root ../Soundboard/Extras --identifier fm.ultraschall.Soundboard.Extras --install-location /Library/Application\ Support/Ultraschall ./Build/UltraschallSoundboardExtras.pkg

# Create SWS REAPER Plugin Extension package
pkgbuild --root ./3rdParty/SWS/UserPlugins/Payload --scripts ./3rdParty/SWS/UserPlugins/Scripts --identifier com.mj-s.sws --install-location /Library/Application\ Support/REAPER/UserPlugins ./Build/SWS_Extension-2.8.3.pkg

# Create SWS REAPER Plugin Scripts package
pkgbuild --root ./3rdParty/SWS/Scripts/Payload --scripts ./3rdParty/SWS/Scripts/Scripts --identifier com.mj-s.sws.Scripts --install-location /Library/Application\ Support/REAPER/Scripts ./Build/SWS_ExtensionScripts-2.8.3.pkg

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

# Create signature on uninstall script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./Payload/Uninstall.command

# Create signature on removal script
codesign --sign "Developer ID Application: Heiko Panjas (8J2G689FCZ)" ./Payload/Remove\ legacy\ audio\ devices.command


# Create installer image
hdiutil create -srcfolder ./Payload -fs HFS+ -volname $ULTRASCHALL_RELEASE ./$ULTRASCHALL_RELEASE_DISK1
rm -rf ./Payload
