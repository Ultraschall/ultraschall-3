# Ultraschall Changelog

Please consult our tutorial videos (German) for detailed advice: [http://ultraschall.fm/tutorials/](http://ultraschall.fm/tutorials/)

## 3.0.3 Miedinger - 2017-März-

* REAPER: **Commitment to a specific version number**
  _For the sake of troubleshooting and in order to maintain system stability, Ultraschall will check for a specific REAPER version ( **5.70** ) on every launch. Future releases will be bound to specific newer versions of REAPER **We therefore strongly advise NOT to manually update REAPER**, since the Ultraschall extensions would be deactivated._

* Actions: **Reworked Routing Snapshots**
  _It is sometimes necessary to prepare and recall different routing situations – e.g. using Studio-Link OnAir – such as pre-show with music on the stream, the actual show with all the speakers, and after-show with music at low volume. The routing snapshot area has therefore been reimplemented completely and enhanced with its own user interface. The snapshots now also support Sends to Master and Hardware Sends._

* Keymap: **Shortcuts for Routing Snapshots**
  _`F1` to `F4` access pre-defined Routing Snapshots. `Shift` + `F1` to `F4` writes the currently configured Routing Matrix into the respective snapshot slot._

* Keymap Mac: **Aligned with system standard**
  _The following shortcut actions were aligned with macOS' system standard: Drag-and-copy of items now works with `alt` + `primary clicking-and-holding`. The current project tab is closed by `cmd` + `w`._

* Streaming: **Update for Studio Link OnAir**
  _Fixes a rare stability problem in the Windows version of Studio Link OnAir._

* Editing: **Further improvements to `esc` key behavior**
  _The "delete entire selection" function now includes also unselected envelope points. Amazing._

* Editing: **Midi actions for EQ tuner**
  _Two new Ultraschall midi actions simplify moving the in- and outpoints via a classical EQ tuner on a midi interface: The middle setting has no effect, a turn to the left or right speeds up movements in the respective direction. The further the turn, the faster the in-/outpoint moves. The scripts (`ultraschall_midi_move_start_of_time_slection.lua` und `ultraschall_midi_move_end_of_time_slection.lua`) need to be manually assigned to a midi signal._

* Installer: **Update Check**
  _Update Checks can now be en- and disabled at any time in the new start screen of Ultraschall._

* Theme: **Expanded Ultraschall start screen**
  _The new start screen now also contains the information from the old `About Ultraschall...` menu, which is hereby removed._

* Soundboard: **Bugfix**
  _The Soundboard will no longer stop playback when recalling a Routing Preset._

* Soundboard: **Presets**
  _The Soundboard now uses presets throughout. This enables saving and loading of sound sets even during a recording. Such on-the-fly changes also enable to easily use more than 24 sounds during a show. One can assign the presets to one's own project presets, so that each session starts with the correct jingles._

## 3.0.2 Miedinger - 2017-March-09

* Editing: **Shortcuts for Inpoint and Outpoint**
  _Use the buttons `alt` + `i` and `alt` + `o` to jump to the beginning or end of a time selection. With `shift` + `i` and `shift` + `o` sound will be played from the respective position._

* Editing: **Improved ripple-cut**
  _The new ripple-cut function (`cmd` + `x` as well as the corresponding icon) now behaves more sensibly: if nothing is selected, nothing happens. If a time selection is selected, only this will be cut, regardless of items that may or may not be selected at the same time. If no time selection is selected, but exactly one item, a ripple cut (Tim's Ripple Cut) is made by means of its edges. If no time selection is selected, but several items, nothing happens._

* Editing: **Quickly change and freeze track height**
  _Use the `h` key to quickly switch between two (adjustable) track heights, which keep their height even when the window is changed in size. The switch affects all selected tracks. If no track is selected, all tracks are affected. The freezing of the height can be canceled with the zoom buttons beneath the vertical scrollbar._

* Keymap: **Optimization of keyboard shortcuts and mapping for Windows**
  _The assignment of shortcuts for Windows was adapted to the behavior on macOS. The PDF template now works the same on both systems. New shortcuts include: `shift` + `n` - Normalization of selected items as well as `alt` + `d` - Switch off all docks for distraction-free editing._

* Theme: **FX buttons on master channel**
  _The buttons for setting FX are now also visible in the master channel in any size._

* Actions: **Advanced Prepare all tracks for editing**
  _The function now includes switching on the sends of all tracks towards the master channel - a common source of mistakes for seemingly missing tracks in the final mix._

* Mastering: **Extended episode images**
  _To quickly use a standard image as episode image, you may now also use files with the name `cover.jpg`, `cover.jpeg` or `cover.png` in the project folder. Thanks to Mespotine for the idea._

## 3.0.1 Miedinger - 2017-March-05

* Streaming **Studio Link OnAir Streaming**
  _Thanks to the support by Studio Link OnAir you can now start a livestream of your show with a single click. The signal attached to the mastermix will be streamed via a public web-interface. There, you can set stream properties and share the URL._

* Installer: **Update Check**
  _Ultraschall will check upon launching whether a new version has been published. It will validate that compatible versions of plugin and theme are installed. If not it will warn you._

* Installer: **LAME MP3 Encoder**
  _The LAME MP3 Encoder in version 3.98.3 is automatically installed._

* Theme: **Ultraschall Start-up Screen**
  _A new start-up screen confirms the successful installation and provides initial hints and links to the support resources._

* Theme: **View Adjustments**
  _The view switchers in the top left now show the current mode after restarting Reaper (keyword: persistence layer). In the Edit view, the navigator window is now displayed over the whole width. Additionally, a new `Loudness` tab was added to the bottom left, which lets you measure the LUFS of tracks or individual items (see Ultraschall Dynamics)._

* Theme: **FX always visible in the mixer**
  _Due to the continually growing importance of effects (StudioLink, OnAir, Soundboard, Dynamics), the FX buttons in the tracks' mixer panel are now always visible, and remain so when you shrink the windows._

* Theme: **Waveform**
  _Selected items and cuts within the waveform are highlighted more clearly now._

* Theme: **User Interface**
  _Many GUI elements receive more contrast to increase their visibility._

* Theme: **Selection Tool**
  _You can now switch the mouse pointer between two editing modes: the previous mode selects and moves individual items on the timeline, while the new mode helps you select times for faster (ripple) cutting. Times can thus be selected anywhere on the timeline, not just on the upper edge as previously. A new icon, as well as the keyboard shortcut `#`, switch between the modes._

* Theme: **Emphasis on 'Prepare all tracks...'**
  _The menu action 'Prepare all tracks for editing' needs to be used after each recording and before cutting. It is now emphasised visually. Also, the function itself has been reimplemented and expanded. A new status dialogue is displayed to provide user feedback after successful completion._

* Theme: **Podcast Menu**
  _Several `Podcast` menu entries were updated and reordered more logically._

* Editing: **Volume Editing**
  _Selected tracks can be overlayed with a new volume envelope (pre-FX!) via the menu or the shortcut `alt`+`v`. That overlay helps you realize complex fadings or volume gradients. Moreover, we've added a new pre-FX gain controller to the track area's left part. This controller adjusts the total volume of a single track; with visual feedback by the waveform. The tracks' visibility is toggled via the top icon known from the mute track._

* Editing: **Easier Envelope Handling**
  _We reworked the mode of setting and moving points in the (mure or volume) envelopes. Now you simply move existing points or click at where the next point should be set. A muted section can thus be set via two clicks. The old free-hand drawing mode can be reactivated any time by pressing `cmd`._

* Editing: **Better `esc` Key Behaviour**
  _We believe in the future and necessity of the `esc` key. That's why we enhanced the "delete any selection" function considerably. It now deselects track, item, envelope and time markers._

* Editing: **Pre-Listening Cuts**
  _The shortcut `p` allows you to pre-listen the result of a cut by time markers, without actually applying the cut. This, together with the new shortcuts `<`, `y`, `x` und `c` for moving the in- and outpoints of a time selection, enables more efficient and controlled cutting._

* Editing: **Play Cursor at the Beginning of a Time Selection**
  _Selecting time places the play cursor directly at the inpoint of the selection, to that one can use `return` or `space` to directly listen to the selection._

* Editing: **Expanded Ripple Cut**
  _The shortcut `cmd` + `x` effects a ripple cut over all tracks, even when only a single item is selected. The cutting range will then be the start- and endpoint of the item._

* Keymap: **New Layout for Keyboard Shortcuts**
  _A multitude of shortcuts was reworked and newly added in order to enable more efficient cutting via the keyboard. The new shortcuts are visualised in a [.PDF](http://url.ultraschall-podcast.de/keymap) and you can reflect customizations in the corresponding PowerPoint source file._

* Mastering: **Ultraschall Dynamics**
  _The new Dynamics Effect can optimize the podcast's loudness to -16 LUFS. This effect replaces the previously recommended AU General Dynamic Effect and can also be applied in Ultraschall's Windows version. We deliver presets with and without soft noisegate in order to reduce faint disturbances. The effect can be used and parameterized on single tracks, single items, as well as on the master channel. Please note: the effect is less suited for the repair of audio problems (humming, reverberation, etc.) against which we highly recommend using [Auphonic](https://auphonic.com/)._

* Mastering: **Effect Templates for New Tracks**
  _Adding new tracks automatically adds the effects ReaEQ (Equalizer) and JS: General Dynamics, but without activating them._

* Mastering: **New EQ Preset**
  _Ultraschall 3 includes a new EQ preset, that delivers less bass boost then the preset from version 2. It is a good starting point for the headsets DT297 and HMC660._

* Mastering: **Export Assistant**
  _`Export` can be found in the bottom left icon bar and helps you generate perfect MP3 files. The ID3V2 elements metadata (like title, podcast, etc.), episode images and chapter marks will be written to the MP3 files you produce._

* Mastering: **Noise Filter**
  _We've added the ReaFix effect to the effect favorites in order to fix common sound problems like hissing or electric hum. Its use is explained in the Ultraschall Dynamics video._

* Mastering: **Open Project Directory**
  _the menu command and the icon for opening the project directory now does exactly that, instead of the subdirectory with the sound files._

* Actions: **Colorpicker**
  _The user-friendly Colorpicker (shortcut: `alt`+`c`) helps you keep the overview in complex projects; assign colors to tracks and single clips, or even gradients to multiple tracks, which can be fluid or using a sensible contrast range._

* Actions: **Import Chaptermarks from WAV Files**
  _Some devices - like Zoom H5 and H6 - allow writing chapter marks to the .WAV file during the recording. A new chapter mark action allows reading those and converts them into Ultraschall chaptermarks._

* Actions [Windows]: **Bugfix for Umlauts**
  _We fixed a bug in the handling of chaptermarks with mutated vowels. Thanks to [@jalea](https://twitter.com/jalea) and to Nico Buch for tracking down that error!_

* Soundboard: **Bugfix**
  _Fixed a bug where the soundboard would not pause playback when triggered with OSC. Thanks to Bastian Boessl for reporting this bug._

## 2.2.2 Gropius - 2016-August-14

* Soundboard [Mac]: **Bugfix**
  _Fixed a bug that prevented a recorded soundboard-track from playing._

* Misc [Windows]: **Compatibility**
  _Updates for Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

* StudioLink: **Update**
  _Ultraschall now includes the updated StudioLink version 16.04.1._

## 2.2.2 Gropius - 2016-August-14

* Soundboard [Mac]: **Bugfix**
  _Fixed a bug that prevented a recorded soundboard-track from playing._

* Misc [Windows]: **Compatibility**
  _Updates for Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

* StudioLink: **Update**
  _Ultraschall now includes the updated StudioLink version 16.04.1._

## 2.2.1 Gropius - 2016-June-09

* Installer: **Bugfix**
  _Fixed a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Marcus Schwarz for reporting this bug._

* Installer: **Bugfix**
  _Fixed another a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Wolfgang Schulz for reporting this bug._

## 2.2 Gropius - 2016-June-05

* Theme: **Theme fine-tuning**
  _Beautification of scroll bars, zoom icons and sliders in VST/AU effect displays_

* Actions: **Cough button and mute track**
  _Complete rework of the cough button und mute button feature. Before you start your recording session, the mute button toggles cough button activation. When your recording session is complete, the mute button toggles the display ot the mute track._

* Actions: **Track selection using the keyboard**
  _You can now toggle the selection of each track by using the numerical keys on your keyboard. Use '1' to '8' to toggle the selection of the respective track. Pressing '9' selects all tracks, '0' deselects all tracks._

* Actions: **Prepare all tracks for editing**
  _The script "Prepare all tracks for editing" for completing a recording session has been improved and more parameters have been added_

* Actions: **New menu item "Customize"**
  _Ultraschall 2.2 introduces the "Customize" menu item. You can use 'Shortcuts and action list' to change keyboard shortcuts and add new scripts to Ultraschall. Use 'Track: set track icon' and 'Show theme configuration window' to change the icons, colors and names of each track._

* StudioLink: **Full integration of the StudioLink plugin**
  _Ultraschall now supports the StudioLink plugin. With StudioLink you can record remote calls on up to 8 individual tracks without the need to setup the notorious 'N-1 Schalte'. Remote attendees are not required to use REAPER. They can download the StudioLink Standalone-App (see https://doku.studio-link.de/standalone/installation-standalone.html)._

* Soundboard: **Soundboard for Windows**
  _The Ultraschall Soundboard now runs on Windows as a VST._

* Soundboard: **Soundboard audio unit for Mac**
  _The Ultraschall Soundboard for Mac is now an audio unit._

* Installer: **StudioLink Plugin**
  _The Ultraschall installer now includes the StudioLink plugin._

* Preferences: **Improved Stop Function**
  \*The stop function has been reworked in such a way that the cursor in recording mode is set to the end of the current recording. This is to prevent the creation of further takes if the recording session continues.

* Preferences: **Automatic Record Arm for newly inserted tracks**
  \*Tracks are now set to 'Record Arm' after they have been inserted into the REAPER project. You are not any longer required to press the red 'Record Arm'-button.

* Misc: **Ultraschall 3 Preset for ReaEQ**
  \*The preset Ultraschall 3 is automatically activated if you insert the ReaEQ Equaliyer into the tracks effect chain. This results in less rumble and less boost of lower frequencies.

* Misc: **Ultraschall Presets for audio compoitions**
  _The effect presets Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate) may be used for voice colorization in audio compositions_

* Installer: **Bugfix**
  _The code signature of Uninstall.command was corrupted. Thanks to Arnd Layer for reporting this bug._

## 2.1.1 Gropius - 2016-Feb-27

* Theme: **Further fine-tuning of the new theme**
* Windows: **Corrected color adjustments for audio tracks on Windows**

## 2.1 Gropius - 2016-Feb-19

* Theme: **Comprehensive fine-tuning of the new theme**
  _The contrast of nearly all elements was increased in order to enhance usability -- also in suboptimal lighting conditions. Groups of icons are now visually encapsulated. Individual icons were redesigned in order to clarify their function. The appeal of all buttons was harmonised. Many colors were fine-tuned in order to match Ultraschall's palette. Cuts within a track item are now marked by a clearer line._

* Theme: **Routing matrix contains display of input assignments**
  _In the lower area of the routing matrix, input channels can now be assigned to tracks. Thus, really all relevant assignments happen at a single site._

* Misc: **SWS/S&M Extension 2.8.3**
  _Ultraschall now comes with the [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/)._

* Actions: **New shortcuts for more fluent editing with the keyboard**
  _Start and end of a time selection can now be set with the `i` and `o` keys, just as in many video editing programs. The keys `1` and `2` now jump you to the start and end of a selection. The key assignments for jumping between chapter marks was changed, because it collided with the word-wise jumping within text sections._

* Actions: **Start/stop/pause safe mode for the keyboard**
  _In order to prevent the unintended stop of an ongoing recording, the keys `RETURN` and `SPACE` are now deactivated during a recording. A prompt will appear and can be affirmed to actually stop the recording._

* Actions: **More robust chapter mark functions**
  _All chapter mark functions were reimplemented in Lua and now take into account, whether a recording is **a)** ongoing, in which case the marker is set at the currently recorded position, or **b)** being played back, in which case it is set at the currently played position, or **c)** not applicable, in which case the marker is set to current position of the editing cursor. The MIDI connection was redesigned more robustly, so that chapter marks can be set via MIDI in any program state -- even when existing markers are being edited._

* Actions: **Labelling of Ultraschall actions**
  _All Ultraschall function are now uniformly pre-fixed with `ULTRASCHALL:` and more clearly labelled in the actions dialogue for the keyboard assignments, which is accessible through the `?` key._

* Soundboard [Mac only]: **Bugfix**
  _REAPER crashes when the folder that is to be loaded into the soundboard contains only one audio file. Thanks to Sven Wiegand for reporting this bug._

* Soundboard: **Bugfix**
  _REAPER crashed when the folder that is to be loaded into the soundboard contained an audio file that can't be decoded. Thanks to René Kurfürst for reporting this bug._

## 2.0 Gropius - 2015-Dec-09

* Misc: **Reaper 5 and OS X 10.11 El Capitan**
  _Ultraschall is now optimized for Reaper 5 and OSX 10.11 El Capitan. Older version are not be supported any more._

* Installer [Mac only]: **User, instead of system, library**
  _The new installer writes its entries into the user library of OS X, instead of the system library._

* Theme: **Complete redesign**
  _More consistency, less clutter. All icons and functional elements have been reworked and colors were harmonized._

* Theme: **Responsive mixer**
  _Depending on the dock's height, the new mixer panel shows or hides some control elements._

* Theme: **New "Storyboard" view for audio compositions**
  _You can now tag areas in your recording -- such as individual answers in an interview -- and later search and filter, also across different projects. Any number of clip databases can be managed. Colors and comments are available, to keep the overview in complex projects. Finished sections and regions can be grouped. Text elements can be distributed freely in the cutting area, in order to manage show notes or comments._

* Actions [Mac only]: **About Screen**
  _A new menu entry_ `Podcast | About Ultraschall…` _displays the installed components and their version numbers._

* HUB [Mac only]: **New audio driver**
  _Soundflower is a thing of the past: following the new CoreAudio APIs in OSX 10.11 El Capitan, the audio engine for virtual sound devices has been revised from the ground up._

Older, untranslated changes are listed [in German only](https://github.com/Ultraschall/REAPER/blob/master/CHANGELOG-DE.md), because Ultraschall was not available in English back then. Please let us know if you really want to have the old changes translated.
