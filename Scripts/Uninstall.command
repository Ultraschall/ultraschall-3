#!/bin/sh

# Uninstall Ultraschall REAPER Extension from user domain
if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_ultraschall.dylib ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_ultraschall.dylib
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.py
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.lua
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

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.lua
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

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_delete_last_marker.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_safemode_start_pause.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_safemode_start_pause.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_safemode_start_stop.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_safemode_start_stop.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit_past.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_edit.lua
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.lua ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_marker.lua
fi

if [ -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.lua ]; then
	sudo rm -f /Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_set_namedmarker.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_mute_envelope.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_mute_envelope.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_studiolink.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_studiolink.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track1.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track1.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track2.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track2.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track3.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track3.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track4.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track4.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track5.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track5.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track6.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track6.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track7.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track7.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track8.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/ultraschall_select_track8.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/test.eel ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/test.eel
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/test.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/test.lua
fi

if [ -f ~/Library/Application\ Support/REAPER/Scripts/testing.lua ]; then
	rm -f ~/Library/Application\ Support/REAPER/Scripts/testing.lua
fi

# Uninstall SWS REAPER Extension from user domain
if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws.dylib
fi

if [ -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws_extension.dylib ]; then
	rm -f ~/Library/Application\ Support/REAPER/UserPlugins/reaper_sws_extension.dylib
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
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_ultraschall.dylib
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

if [ -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws_extension.dylib ]; then
	sudo rm -f /Library/Application\ Support/REAPER/UserPlugins/reaper_sws_extension.dylib
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

# Uninstall Ultraschall Virtual Audio Devices from user domain
if [ -d ~/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver ]; then
	sudo launchctl unload /System/Library/LaunchDaemons/com.apple.audio.coreaudiod.plist
	rm -rf ~/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver
	sudo launchctl load /System/Library/LaunchDaemons/com.apple.audio.coreaudiod.plist
fi

# Uninstall Ultraschall Virtual Audio Devices from system domain
if [ -d /Library/Audio/Plug-Ins/HAL/UltraschallHub.driver ]; then
	sudo launchctl unload /System/Library/LaunchDaemons/com.apple.audio.coreaudiod.plist
	sudo rm -rf /Library/Audio/Plug-Ins/HAL/UltraschallHub.driver
	sudo launchctl load /System/Library/LaunchDaemons/com.apple.audio.coreaudiod.plist
fi

# Uninstall color themes from user domain
if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.ReaperThemeZip ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.ReaperThemeZip
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.1.SWSColor ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.1.SWSColor
fi

if [ -d ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2 ]; then
	rm -rf ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2
fi

if [ -d ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta2_unpacked ]; then
	rm -rf ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta2_unpacked
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_2.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Black-2.ReaperThemeZip ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Black-2.ReaperThemeZip
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Classic_4.x.ReaperThemeZip ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Classic_4.x.ReaperThemeZip
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Hindenburg.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Hindenburg.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_1.0.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_1.0.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta2_unpacked.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta2_unpacked.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta3.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta3.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta4.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_beta4.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_RC1.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_RC1.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_RC4.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall_RC4.ReaperTheme
fi

if [ -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall1_1.ReaperTheme ]; then
	rm -f ~/Library/Application\ Support/REAPER/ColorThemes/Ultraschall1_1.ReaperTheme
fi

# Uninstall Ultraschall Soundboard Extras from user domain
if [ -d ~/Library/Application\ Support/Ultraschall/AudioTemplates ]; then
	rm -rf ~/Library/Application\ Support/Ultraschall/AudioTemplates
fi

if [ -d ~/Library/Application\ Support/Ultraschall/TouchOSC ]; then
	rm -rf ~/Library/Application\ Support/Ultraschall/TouchOSC
fi

if [ -f ~/Library/Application\ Support/Ultraschall/MIDI.md ]; then
	rm -f ~/Library/Application\ Support/Ultraschall/MIDI.md
fi

if [ -f ~/Library/Application\ Support/Ultraschall/OSC.md ]; then
	rm -f ~/Library/Application\ Support/Ultraschall/OSC.md
fi

# Uninstall Ultraschall Soundboard Extras from system domain
if [ -d /Library/Application\ Support/Ultraschall/AudioTemplates ]; then
	sudo rm -rf /Library/Application\ Support/Ultraschall/AudioTemplates
fi

if [ -d /Library/Application\ Support/Ultraschall/TouchOSC ]; then
	sudo rm -rf /Library/Application\ Support/Ultraschall/TouchOSC
fi

# Uninstall Ultraschall StudioLink Audio Unit from user domain
if [ -d ~/Library/Audio/Plug-Ins/Components/StudioLinkOnAir.component ]; then
	rm -rf ~/Library/Audio/Plug-Ins/Components/StudioLinkOnAir.component
fi

# Uninstall Ultraschall StudioLink Audio Unit from system domain
if [ -d /Library/Audio/Plug-Ins/Components/StudioLinkOnAir.component ]; then
	sudo rm -rf /Library/Audio/Plug-Ins/Components/StudioLinkOnAir.component
fi

# Uninstall Ultraschall StudioLink Audio Unit from user domain
if [ -d ~/Library/Audio/Plug-Ins/Components/StudioLink.component ]; then
	rm -rf ~/Library/Audio/Plug-Ins/Components/StudioLink.component
fi

# Uninstall Ultraschall StudioLink Audio Unit from system domain
if [ -d /Library/Audio/Plug-Ins/Components/StudioLink.component ]; then
	sudo rm -rf /Library/Audio/Plug-Ins/Components/StudioLink.component
fi

# Uninstall Ultraschall Soundboard Audio Unit from user domain
if [ -d ~/Library/Audio/Plug-Ins/Components/Soundboard.component ]; then
	rm -rf ~/Library/Audio/Plug-Ins/Components/Soundboard.component
fi

# Uninstall Ultraschall Soundboard Audio Unit from system domain
if [ -d /Library/Audio/Plug-Ins/Components/Soundboard.component ]; then
	sudo rm -rf /Library/Audio/Plug-Ins/Components/Soundboard.component
fi

# Uninstall Ultraschall Soundboard VST from user domain
if [ -d ~/Library/Audio/Plug-Ins/VST/Soundboard.vst ]; then
	rm -rf ~/Library/Audio/Plug-Ins/VST/Soundboard.vst
fi

# Uninstall Ultraschall Soundboard VST from system domain
if [ -d /Library/Audio/Plug-Ins/VST/Soundboard.vst ]; then
	sudo rm -rf /Library/Audio/Plug-Ins/VST/Soundboard.vst
fi

# Uninstall Ultraschall Soundboard settings from user domain
if [ -f ~/Library/Application\ Support/REAPER/presets/vst-Soundboard.ini ]; then
	rm -f ~/Library/Application\ Support/REAPER/presets/vst-Soundboard.ini
fi

# Uninstall Ultraschall Soundboard settings from system domain
if [ -f /Library/Application\ Support/REAPER/presets/vst-Soundboard.ini ]; then
	sudo rm -f /Library/Application\ Support/REAPER/presets/vst-Soundboard.ini
fi

# Uninstall Ultraschall FXChain settings from user domain
if [ -f ~/Library/Application\ Support/REAPER/FXChains/Wikigeeks.RfxChain ]; then
	rm -f ~/Library/Application\ Support/REAPER/FXChains/Wikigeeks.RfxChain
fi

# Uninstall Ultraschall FXChain settings from system domain
if [ -f /Library/Application\ Support/REAPER/FXChains/Wikigeeks.RfxChain ]; then
	sudo rm -f /Library/Application\ Support/REAPER/FXChains/Wikigeeks.RfxChain
fi

# Uninstall Ultraschall track templates from user domain
if [ -f ~/Library/Application\ Support/REAPER/TrackTemplates/Soundboard\ Spur\ anlegen.RTRackTemplate ]; then
	rm -f ~/Library/Application\ Support/REAPER/TrackTemplates/Soundboard\ Spur\ anlegen.RTRackTemplate
fi

if [ -f ~/Library/Application\ Support/REAPER/TrackTemplates/Soundboard.RTRackTemplate ]; then
	rm -f ~/Library/Application\ Support/REAPER/TrackTemplates/Soundboard.RTRackTemplate
fi

if [ -f ~/Library/Application\ Support/REAPER/TrackTemplates/Insert\ Ultraschall-Soundboard\ track.RTrackTemplate ]; then
	rm -f ~/Library/Application\ Support/REAPER/TrackTemplates/Insert\ Ultraschall-Soundboard\ track.RTrackTemplate
fi

if [ -f ~/Library/Application\ Support/REAPER/TrackTemplates/Ultraschall\ Colors.SWSColor ]; then
	rm -f ~/Library/Application\ Support/REAPER/TrackTemplates/Ultraschall\ Colors.SWSColor
fi

# Uninstall Ultraschall track templates from system domain
if [ -f /Library/Application\ Support/REAPER/TrackTemplates/Soundboard\ Spur\ anlegen.RTRackTemplate ]; then
	sudo rm -f /Library/Application\ Support/REAPER/TrackTemplates/Soundboard\ Spur\ anlegen.RTRackTemplate
fi

if [ -f /Library/Application\ Support/REAPER/TrackTemplates/Soundboard.RTRackTemplate ]; then
	sudo rm -f /Library/Application\ Support/REAPER/TrackTemplates/Soundboard.RTRackTemplate
fi

if [ -f /Library/Application\ Support/REAPER/TrackTemplates/Insert\ Ultraschall-Soundboard\ track.RTrackTemplate ]; then
	sudo rm -f /Library/Application\ Support/REAPER/TrackTemplates/Insert\ Ultraschall-Soundboard\ track.RTrackTemplate
fi

# Uninstall StudioLink track templates from user domain
if [ -f ~/Library/Application\ Support/REAPER/TrackTemplates/Insert\ StudioLink\ track.RTrackTemplate ]; then
	rm -f ~/Library/Application\ Support/REAPER/TrackTemplates/Insert\ StudioLink\ track.RTrackTemplate
fi

# Uninstall StudioLink track templates from system domain
if [ -f /Library/Application\ Support/REAPER/TrackTemplates/Insert\ StudioLink\ track.RTrackTemplate ]; then
	sudo rm -f /Library/Application\ Support/REAPER/TrackTemplates/Insert\ StudioLink\ track.RTrackTemplate
fi

# Uninstall Ultraschall project templates from user domain
if [ -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP ]; then
	rm -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP
fi

if [ -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP-bak ]; then
	rm -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP-bak
fi

if [ -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP ]; then
	rm -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP
fi

if [ -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP-bak ]; then
	rm -f ~/Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP-bak
fi

# Uninstall Ultraschall project templates from system domain
if [ -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP ]; then
	sudo rm -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP
fi

if [ -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP-bak ]; then
	sudo rm -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall.RPP-bak
fi

if [ -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP ]; then
	sudo rm -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP
fi

if [ -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP-bak ]; then
	sudo rm -f /Library/Application\ Support/REAPER/ProjectTemplates/Ultraschall\ Ducking.RPP-bak
fi

# Uninstall StudioLink project templates from user domain
if [ -f ~/Library/Application\ Support/REAPER/ProjectTemplates/StudioLink.RPP ]; then
	rm -f ~/Library/Application\ Support/REAPER/ProjectTemplates/StudioLink.RPP
fi

# Uninstall StudioLink project templates from system domain
if [ -f /Library/Application\ Support/REAPER/ProjectTemplates/StudioLink.RPP ]; then
	sudo rm -f /Library/Application\ Support/REAPER/ProjectTemplates/StudioLink.RPP
fi

# Uninstall Ultraschall Add-ons from user domain
if [ -f ~/Library/Application\ Support/Ultraschall/Ultraschall\ Reaper\ Splash\ Screen.png ]; then
	rm -f ~/Library/Application\ Support/Ultraschall/Ultraschall\ Reaper\ Splash\ Screen.png
fi

# Uninstall Ultraschall Add-ons from system domain
if [ -f /Library/Application\ Support/Ultraschall/Ultraschall\ Reaper\ Splash\ Screen.png ]; then
	sudo rm -f /Library/Application\ Support/Ultraschall/Ultraschall\ Reaper\ Splash\ Screen.png
fi

# Uninstall left-overs from user domain
if [ -d ~/Library/Ultraschall ]; then
	rm -rf ~/Library/Ultraschall
fi

# Uninstall left-overs from system domain
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
if [ -f /var/db/receipts/com.itsr.StudioLink.bom ]; then
	sudo rm -f /var/db/receipts/com.itsr.StudioLink.bom
fi

if [ -f /var/db/receipts/com.itsr.StudioLink.plist ]; then
	sudo rm -f /var/db/receipts/com.itsr.StudioLink.plist
fi

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

if [ -f /var/db/receipts/fm.ultraschall.UltraschallHubDriver.bom ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.UltraschallHubDriver.bom
fi

if [ -f /var/db/receipts/fm.ultraschall.UltraschallHubDriver.plist ]; then
	sudo rm -f /var/db/receipts/fm.ultraschall.UltraschallHubDriver.plist
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

echo "Uninstall finished. You might close this window."
echo "Deinstallation abgeschlossen. Dieses Fenster kann geschlossen werden."
