# Changelog

Please consult our tutorial videos (German) for detailed advide: [http://ultraschall.fm/tutorials/](http://ultraschall.fm/tutorials/)

## 3.0.2 Miedinger - 2017-March-09

* Editing: **Shortcuts for Inpoint and Outpoint**
*Use the buttons `alt` + `i` and `alt` + `o` to jump to the beginning or end of a time selection. With `shift` + `i` and `shift` + `o` sound will be played from the respective position.*

* Editing: **Improved ripple-cut**
*The new ripple-cut function (`cmd` + `x` as well as the corresponding icon) now behave more sensibly: if nothing is selected, nothing happens. If a time selection is selected, only this will be cut, regardless of items that may or may not be selected at the same time. If no time selection is selected, but exactly one item, a ripple cut (Tim's Ripple Cut) is made by means of its edges. If no time selection is selected, but several items, nothing happens.*

* Editing: **Quickly change and freeze track height**
*Use the `h` key to quickly switch between two (adjustable) track heights, which keep their height even when the window is changed in size. The switch affects all selected tracks. If no track is selected, all tracks are affected. The freezing of the height can be canceled with the zoom buttons beneath the vertical scrollbar.*

* Keymap: **Optimization of keyboard shortcuts and mapping for Windows**
*The assignment of shortcuts for Windows was adapted to the behavior on macOS. The PDF template now works the same on both systems. New shortcuts include: `shift` + `n` - Normalization of selected items as well as `alt` + `d` - Switch off all docks for distraction-free editing.*

* Theme: **FX buttons on master channel**
*The buttons for setting FX are now also visible in the master channel in any size.*

* Actions: **Advanced Prepare all tracks for editing**
*The function now includes switching on the sends of all tracks towards the master channel - a common source of mistakes for seemingly missing tracks in the final mix.*

* Mastering: **Extended episode images**
*To quickly use a standard image as episode image, you may now also use files with the name `cover.jpg`, `cover.jpeg` or `cover.png` in the project folder. Thanks to Mespotine for the idea.*

## 3.0.1 Miedinger - 2017-March-05

* Streaming **Studio Link OnAir Streaming**
*Thanks to the support by Studio Link OnAir you can now start a livestream of your show with a single click. The signal attached to the mastermix will be streamed via a public web-interface. There, you can set stream properties and share the URL.*

* Installer: **Update Check**
*Ultraschall will check upon launching whether a new version has been published. It will validate that compatible versions of plugin and theme are installed. If not it will warn you.*

* Installer: **LAME MP3 Encoder**
*The LAME MP3 Encoder in version 3.98.3 is automatically installed.*

* Theme: **Ultraschall Start-up Screen**
*A new start-up screen confirms the successful installation and provides initial hints and links to the support resources.*

* Theme: **View Adjustments**
*The view switchers in the top left now show the current mode after restarting Reaper (keyword: persistence layer). In the Edit view, the navigator window is now displayed over the whole width. Additionally, a new `Loudness` tab was added to the bottom left, which lets you measure the LUFS of tracks or individual items (see Ultraschall Dynamics).*

* Theme: **FX always visible in the mixer**
*Due to the continually growing importance of effects (StudioLink, OnAir, Soundboard, Dynamics), the FX buttons in the tracks' mixer panel are now always visible, and remain so when you shrink the windows.*

* Theme: **Waveform**
*Selected items and cuts within the waveform are highlighted more clearly now.*

* Theme: **User Interface**
*Many GUI elements receive more contrast to increase their visibility.*

* Theme: **Selection Tool**
*You can now switch the mouse pointer between two editing modes: the previous mode selects and moves individual items on the timeline, while the new mode helps you select times for faster (ripple) cutting. Times can thus be selected anywhere on the timeline, not just on the upper edge as previously. A new icon, as well as the keyboard shortcut `#`, switch between the modes.*

* Theme: **Emphasis on 'Prepare all tracks...'**
*The menu action 'Prepare all tracks for editing' needs to be used after each recording and before cutting. It is now emphasised visually. Also, the function itself has been reimplemented and expanded. A new status dialogue is displayed to provide user feedback after successful completion.*

* Theme: **Podcast Menu**
*Several `Podcast` menu entries were updated and reordered more logically.*

* Editing: **Volume Editing**
*Selected tracks can be overlayed with a new volume envelope (pre-FX!) via the menu or the shortcut `alt`+`v`. That overlay helps you realize complex fadings or volume gradients. Moreover, we've added a new pre-FX gain controller to the track area's left part. This controller adjusts the total volume of a single track; with visual feedback by the waveform. The tracks' visibility is toggled via the top icon known from the mute track.*

* Editing: **Easier Envelope Handling**
*We reworked the mode of setting and moving points in the (mure or volume) envelopes. Now you simply move existing points or click at where the next point should be set. A muted section can thus be set via two clicks. The old free-hand drawing mode can be reactivated any time by pressing `cmd`.*

* Editing: **Better `esc` Key Behaviour**
*We believe in the future and necessity of the `esc` key. That's why we enhanced the "delete any selection" function considerably. It now deselects track, item, envelope and time markers.*

* Editing: **Pre-Listening Cuts**
*The shortcut `p` allows you to pre-listen the result of a cut by time markers, without actually applying the cut. This, together with the new shortcuts `<`, `y`, `x` und `c` for moving the in- and outpoints of a time selection, enables more efficient and controlled cutting.*

* Editing: **Play Cursor at the Beginning of a Time Selection**
*Selecting time places the play cursor directly at the inpoint of the selection, to that one can use `return` or `space` to directly listen to the selection.*

* Editing: **Expanded Ripple Cut**
*The shortcut `cmd` + `x` effects a ripple cut over all tracks, even when only a single item is selected. The cutting range will then be the start- and endpoint of the item.*

* Keymap: **New Layout for Keyboard Shortcuts**
*A multitude of shortcuts was reworked and newly added in order to enable more efficient cutting via the keyboard. The new shortcuts are visualised in a [.PDF](http://url.ultraschall-podcast.de/keymap) and you can reflect customizations in the corresponding PowerPoint source file.*

* Mastering: **Ultraschall Dynamics**
*The new Dynamics Effect can optimize the podcast's loudness to -16 LUFS. This effect replaces the previously recommended AU General Dynamic Effect and can also be applied in Ultraschall's Windows version. We deliver presets with and without soft noisegate in order to reduce faint disturbances. The effect can be used and parameterized on single tracks, single items, as well as on the master channel. Please note: the effect is less suited for the repair of audio problems (humming, reverberation, etc.) against which we highly recommend using [Auphonic](https://auphonic.com/).*

* Mastering: **Effect Templates for New Tracks**
*Adding new tracks automatically adds the effects ReaEQ (Equalizer) and JS: General Dynamics, but without activating them.*

* Mastering: **New EQ Preset**
*Ultraschall 3 includes a new EQ preset, that delivers less bass boost then the preset from version 2. It is a good starting point for the headsets DT297 and HMC660.*

* Mastering: **Export Assistant**
*`Export` can be found in the bottom left icon bar and helps you generate perfect MP3 files. The ID3V2 elements metadata (like title, podcast, etc.), episode images and chapter marks will be written to the MP3 files you produce.*

* Mastering: **Noise Filter**
*We've added the ReaFix effect to the effect favorites in order to fix common sound problems like hissing or electric hum. Its use is explained in the Ultraschall Dynamics video.*

* Mastering: **Open Project Directory**
*the menu command and the icon for opening the project directory now does exactly that, instead of the subdirectory with the sound files.*

* Actions: **Colorpicker**
*The user-friendly Colorpicker (shortcut: `alt`+`c`) helps you keep the overview in complex projects; assign colors to tracks and single clips, or even gradients to multiple tracks, which can be fluid or using a sensible contrast range.*

* Actions: **Import Chaptermarks from WAV Files**
*Some devices - like Zoom H5 and H6 - allow writing chapter marks to the .WAV file during the recording. A new chapter mark action allows reading those and converts them into Ultraschall chaptermarks.*

* Actions [Windows]: **Bugfix for Umlauts**
*We fixed a bug in the handling of chaptermarks with mutated vowels. Thanks to [@jalea](https://twitter.com/jalea) and to Nico Buch for tracking down that error!*

* Soundboard: **Bugfix**
*Fixed a bug where the soundboard would not pause playback when triggered with OSC. Thanks to Bastian Boessl for reporting this bug.*

## 2.2.2 Gropius - 2016-August-14

* Soundboard [Mac]: **Bugfix**
*Fixed a bug that prevented a recorded soundboard-track from playing.*

* Misc [Windows]: **Compatibility**
*Updates for Windows 10 Version 1607 (Build 14393, Anniversary-Update).*

* StudioLink: **Update**
*Ultraschall now includes the updated StudioLink version 16.04.1.*

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
