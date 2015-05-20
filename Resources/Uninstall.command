#!/bin/sh

# Uninstall Ultraschall REAPER Extension from user domain
if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_ultraschall.dylib ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_Ultraschall.dylib
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_einspieler.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_einspieler.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_import_shownotes.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_import_shownotes.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_notes.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_notes.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_webserver.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_webserver.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/debug.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/debug.py
fi

# Uninstall SWS REAPER Extension from user domain
if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib
fi

if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt
fi

if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws_whatsnew.txt ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws_whatsnew.txt
fi

if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/license.txt ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/license.txt
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/sws_python.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/sws_python.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/sws_python32.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/sws_python32.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/sws_python64.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/sws_python64.py
fi

# Uninstall Ultraschall REAPER Extension from system domain
if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_ultraschall.dylib ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_Ultraschall.dylib
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py
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

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.py
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

if [ -f /Library/Application\ Support/REAPER/Scripts/debug.py ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/debug.py
fi

# Uninstall SWS REAPER Extension from system domain
if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib
fi

if [ -f /Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/whatsnew.txt
fi

if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws_whatsnew.txt ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws_whatsnew.txt
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

# Uninstall Ultraschall from user domain
if [ -d ~/Library/Audio/Plug-Ins/VST/Soundboard.vst ]; then
	rm -rf ~/Library/Audio/Plug-Ins/VST/Soundboard.vst
fi

if [ -d ~/Library/Ultraschall ]; then
	rm -rf ~/Library/Ultraschall
fi

# Uninstall Ultraschall from system domain
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

if [ -f /var/db/receipts/fm.ultraschall.SoundflowerUninstaller.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.SoundflowerUninstaller.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.SoundflowerUninstaller.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.SoundflowerUninstaller.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.UltraschallHub.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.UltraschallHub.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.UltraschallHub.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.UltraschallHub.plist
fi

if [ -f /var/db/receipts/fm.ultraschall.Ultraschall.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Ultraschall.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.Ultraschall.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.Ultraschall.plist
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

