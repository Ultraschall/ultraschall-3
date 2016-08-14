# Changelog

## Syntax of the changelog

* **Preferences:** Changes to Reaper's preferences dialog, which can be opened via `⌘`+`,` or through the `Reaper | Preferences` menu.
* **Theme:** These changes affect the design or arrangement of elements (buttons, controllers, displays, etc.) of the theme we provide.
* **Actions:** Adds new features and changes that affect the keyboard, mouse or trackpad bindings to actions or presets.
* **Soundboard:** Features of our own Soundboard for audio snippets/shorts/inserts.
* **Installer:** New features for the Mac installer which was introduced with Ultraschall 1.2.
* **Hub [Mac only]:** Our project to replace [Soundflower](https://github.com/mattingalls/Soundflower/releases/tag/2.0b2), and to provide a stable, crackle-free podcasting experience.
* **Misc:** Anything that is left.

## 2.2.2 Gropius - 2016-August-14

* Soundboard [Mac]: **Bugfix**
*Fixed a bug that prevented a recorded soundboard-track from playing.*

* Misc [Windows]: **Compatibility**
*Updates for Windows 10 Version 1607 (Build 14393, Anniversary-Update).*

* StudioLink: **Update**
*Ultraschall now includes the updated StudioLink version 16.04.1.*

## 2.2.1 Gropius - 2016-June-09

* Installer: **Bugfix**
*Fixed a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Marcus Schwarz for reporting this bug.*

* Installer: **Bugfix**
*Fixed another a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Wolfgang Schulz for reporting this bug.*

## 2.2 Gropius - 2016-June-05

* Theme: **Theme fine-tuning**
*Beautification of scroll bars, zoom icons and sliders in VST/AU effect displays*

* Actions: **Cough button and mute track**
*Complete rework of the cough button und mute button feature. Before you start your recording session, the mute button toggles cough button activation. When your recording session is complete, the mute button toggles the display ot the mute track.*

* Actions: **Track selection using the keyboard**
*You can now toggle the selection of each track by using the numerical keys on your keyboard. Use '1' to '8' to toggle the selection of the respective track. Pressing '9' selects all tracks, '0' deselects all tracks.*

* Actions: **Prepare all tracks for editing**
*The script "Prepare all tracks for editing" for completing a recording session has been improved and more parameters have been added*

* Actions: **New menu item "Customize"**
*Ultraschall 2.2 introduces the "Customize" menu item. You can use 'Shortcuts and action list' to change keyboard shortcuts and add new scripts to Ultraschall. Use 'Track: set track icon' and 'Show theme configuration window' to change the icons, colors and names of each track.*

* StudioLink: **Full integration of the StudioLink plugin**
*Ultraschall now supports the StudioLink plugin. With StudioLink you can record remote calls on up to 8 individual tracks without the need to setup the notorious 'N-1 Schalte'. Remote attendees are not required to use REAPER. They can download the StudioLink Standalone-App (see https://doku.studio-link.de/standalone/installation-standalone.html).*

* Soundboard: **Soundboard for Windows**
*The Ultraschall Soundboard now runs on Windows as a VST.*

* Soundboard: **Soundboard audio unit for Mac**
*The Ultraschall Soundboard for Mac is now an audio unit.*

* Installer: **StudioLink Plugin**
*The Ultraschall installer now includes the StudioLink plugin.*

* Preferences: **Improved Stop Function**
*The stop function has been reworked in such a way that the cursor in recording mode is set to the end of the current recording. This is to prevent the creation of further takes if the recording session continues.

* Preferences: **Automatic Record Arm for newly inserted tracks**
*Tracks are now set to 'Record Arm' after they have been inserted into the REAPER project. You are not any longer required to press the red 'Record Arm'-button.

* Misc: **Ultraschall 3 Preset for ReaEQ**
*The preset Ultraschall 3 is automatically activated if you insert the ReaEQ Equaliyer into the tracks effect chain. This results in less rumble and less boost of lower frequencies.    

* Misc: **Ultraschall Presets for audio compoitions**
*The effect presets Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate) may be used for voice colorization in audio compositions* 

* Installer: **Bugfix**
*The code signature of Uninstall.command was corrupted. Thanks to Arnd Layer for reporting this bug.*

## 2.1.1 Gropius - 2016-Feb-27

* Theme: **Further fine-tuning of the new theme**
* Windows: **Corrected color adjustments for audio tracks on Windows**

## 2.1 Gropius - 2016-Feb-19

* Theme: **Comprehensive fine-tuning of the new theme**
*The contrast of nearly all elements was increased in order to enhance usability -- also in suboptimal lighting conditions. Groups of icons are now visually encapsulated. Individual icons were redesigned in order to clarify their function. The appeal of all buttons was harmonised. Many colors were fine-tuned in order to match Ultraschall's palette. Cuts within a track item are now marked by a clearer line.*

* Theme: **Routing matrix contains display of input assignments**
*In the lower area of the routing matrix, input channels can now be assigned to tracks. Thus, really all relevant assignments happen at a single site.*

* Misc: **SWS/S&M Extension 2.8.3**
*Ultraschall now comes with the [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/).*

* Actions: **New shortcuts for more fluent editing with the keyboard**
*Start and end of a time selection can now be set with the `i` and `o` keys, just as in many video editing programs. The keys `1` and `2` now jump you to the start and end of a selection. The key assignments for jumping between chapter marks was changed, because it collided with the word-wise jumping within text sections.*

* Actions: **Start/stop/pause safe mode for the keyboard**
*In order to prevent the unintended stop of an ongoing recording, the keys `RETURN` and `SPACE` are now deactivated during a recording. A prompt will appear and can be affirmed to actually stop the recording.*

* Actions: **More robust chapter mark functions**
*All chapter mark functions were re-implemented in Lua and now take into account, whether a recording is **a)** ongoing, in which case the marker is set at the currently recorded position, or **b)** being played back, in which case it is set at the currently played position, or **c)** not applicable, in which case the marker is set to current position of the editing cursor. The MIDI connection was redesigned more robustly, so that chapter marks can be set via MIDI in any program state -- even when existing markers are being edited.*

* Actions: **Labelling of Ultraschall actions**
*All Ultraschall function are now uniformly pre-fixed with `ULTRASCHALL:` and more clearly labelled in the actions dialogue for the keyboard assignments, which is accessible through the `?` key.*

* Soundboard [Mac only]: **Bugfix**
*REAPER crashes when the folder that is to be loaded into the soundboard contains only one audio file. Thanks to Sven Wiegand for reporting this bug.*

* Soundboard: **Bugfix**
*REAPER crashed when the folder that is to be loaded into the soundboard contained an audio file that can't be decoded. Thanks to René Kurfürst for reporting this bug.*

## 2.0 Gropius - 2015-Dec-09

* Misc:  **Reaper 5 and OS X 10.11 El Capitan**
*Ultraschall is now optimized for Reaper 5 and OSX 10.11 El Capitan. Older version are not be supported any more.*

* Installer [Mac only]: **User, instead of system, library**
*The new installer writes its entries into the user library of OS X, instead of the system library.*

* Theme: **Complete redesign**
*More consistency, less clutter. All icons and functional elements have been reworked and colors were harmonized.*

* Theme: **Responsive mixer**
*Depending on the dock's height, the new mixer panel shows or hides some control elements.*

* Theme: **New "Storyboard" view for audio compositions**
*You can now tag areas in your recording -- such as individual answers in an interview -- and later search and filter, also across different projects. Any number of clip databases can be managed. Colors and comments are available, to keep the overview in complex projects. Finished sections and regions can be grouped. Text elements can be distributed freely in the cutting area, in order to manage show notes or comments.*

* Actions [Mac only]: **About Screen**
*A new menu entry* `Podcast | About Ultraschall…` *displays the installed components and their version numbers.*

* HUB [Mac only]: **New audio driver**
*Soundflower is a thing of the past: following the new CoreAudio APIs in OSX 10.11 El Capitan, the audio engine for virtual sound devices has been revised from the ground up.*

Older, untranslated changes are listed [in German only](https://github.com/Ultraschall/REAPER/blob/master/CHANGELOG-DE.md), because Ultraschall was not available in English back then. Please let us know if you really want to have the old changes translated.
