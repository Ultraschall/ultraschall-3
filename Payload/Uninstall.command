#!/bin/sh

# Uninstall Ultraschall REAPER Extension
if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_Ultraschall.dylib ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_Ultraschall.dylib
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_einspieler.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_einspieler.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_import_shownotes.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_import_shownotes.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_notes.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_notes.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_webserver.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_webserver.py
fi

# Uninstall SWS REAPER Extension
if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib
fi

if [ -f /Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt
fi

if [ -f /Library/Application\ Support/REAPER/UserPlugins/license.txt ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/license.txt
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/sws_python.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/sws_python.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/sws_python32.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/sws_python32.py
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/sws_python64.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/sws_python64.py
fi

# Uninstall Ultraschall
if [ -d /Library/Audio/Plug-Ins/VST/Soundboard.vst ]; then
	sudo rm -rf /Library/Audio/Plug-Ins/VST/Soundboard.vst
fi

if [ -d /Library/Ultraschall ]; then
	sudo rm -rf /Library/Ultraschall
fi

# Uninstall Ultraschall Driver
if [ -d /Library/Extensions/UltraschallHub.kext ]; then
	sudo kextunload /Library/Extensions/UltraschallHub.kext
	sudo kextunload /Library/Extensions/UltraschallHub.kext
	sudo rm -rf /Library/Extensions/UltraschallHub.kext
fi

# Remove installer receipts
if [ -f /var/db/receipts/fm.ultraschall.Soundboard.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Soundboard.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Soundboard.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Soundboard.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.Soundboard.Scripts.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Soundboard.Scripts.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Soundboard.Scripts.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Soundboard.Scripts.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.Plugin.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Plugin.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Plugin.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Plugin.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.Plugin.Scripts.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Plugin.Scripts.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Plugin.Scripts.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Plugin.Scripts.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.pkg.UltraschallDriver.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.pkg.UltraschallDriver.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.pkg.UltraschallDriver.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.pkg.UltraschallDriver.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.Resources.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Resources.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Resources.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Resources.plist
fi

if [ -f /var/db/receipts/com.mj-s.sws.bom ]; then
	sudo rm -f /var/db/receipts/com.mj-s.sws.bom
fi

if [ -f /var/db/receipts/com.mj-s.sws.plist ]; then
	sudo rm -f /var/db/receipts/com.mj-s.sws.plist
fi

if [ -f /var/db/receipts/com.mj-s.sws.Scripts.bom ]; then
	sudo rm -f /var/db/receipts/com.mj-s.sws.Scripts.bom
fi

if [ -f /var/db/receipts/com.mj-s.sws.Scripts.plist ]; then
	sudo rm -f /var/db/receipts/com.mj-s.sws.Scripts.plist
fi

