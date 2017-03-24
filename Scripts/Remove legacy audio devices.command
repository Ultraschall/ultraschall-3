#!/bin/sh

# remove legacy UltraschallHub 1.x driver
if [ -d /Library/Extensions/UltraschallHub.kext ]
then
	sudo kextunload /Library/Extensions/UltraschallHub.kext
	sudo kextunload /Library/Extensions/UltraschallHub.kext
	sudo rm -rf /Library/Extensions/UltraschallHub.kext
fi

if [ -d /System/Library/Extensions/UltraschallHub.kext ]
then
	sudo kextunload /System/Library/Extensions/UltraschallHub.kext
	sudo kextunload /System/Library/Extensions/UltraschallHub.kext
	sudo rm -rf /System/Library/Extensions/UltraschallHub.kext
fi

# remove early UltraschallHub driver
if [ -d /Library/Extensions/Ultraschall.kext ]
then
	sudo kextunload /Library/Extensions/Ultraschall.kext
	sudo kextunload /Library/Extensions/Ultraschall.kext
	sudo rm -rf /Library/Extensions/Ultraschall.kext
fi
if [ -d /System/Library/Extensions/Ultraschall.kext ]
then
	sudo kextunload /System/Library/Extensions/Ultraschall.kext
	sudo kextunload /System/Library/Extensions/Ultraschall.kext
	sudo rm -rf /System/Library/Extensions/Ultraschall.kext
fi

#remove Soundflower (incl. Ultraschall Edition and experimental builds)
if [ -d /Library/Extensions/Soundflower.kext ]
then
	sudo kextunload /Library/Extensions/Soundflower.kext
	sudo kextunload /Library/Extensions/Soundflower.kext
	sudo rm -rf /Library/Extensions/Soundflower.kext
fi
if [ -d /System/Library/Extensions/Soundflower.kext ]
then
	sudo kextunload /System/Library/Extensions/Soundflower.kext
	sudo kextunload /System/Library/Extensions/Soundflower.kext
	sudo rm -rf /System/Library/Extensions/Soundflower.kext
fi

echo "Uninstall finished. You might close this window."
echo "Deinstallation abgeschlossen. Dieses Fenster kann geschlossen werden."
