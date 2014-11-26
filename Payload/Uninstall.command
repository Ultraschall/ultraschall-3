#!/bin/sh
rm -f /Users/Heiko/Library/Application Support/REAPER/UserPlugins/reaper_Ultraschall.dylib
rm -f /Users/Heiko/Library/Application Support/REAPER/Scripts/ultraschall_.*

rm -f /Users/Heiko/Library/Application Support/REAPER/UserPlugins/reaper_sws.*
rm -f /Users/Heiko/Library/Application Support/REAPER/Scripts/sws_.*

sudo rm -rf /Users/Heiko/Library/Audio/Plug-Ins/VST/Soundboard.vst

sudo kextunload /Library/Extensions/UltraschallHub.kext
sudo kextunload /Library/Extensions/UltraschallHub.kext
sudo rm -rf /Library/Extensions/UltraschallHub.kext

sudo rm -f /var/db/receipts/com.mj-s.sws.*
sudo rm -f /var/db/receipts/fm.ultraschall.*


