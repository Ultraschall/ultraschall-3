# Ultraschall Changelog

The following features will be presented in detail in our Ultraschall tutorial videos:
[tp://ultraschall.fm/tutorials/](http://ultraschall.fm/tutorials/)

## 3.2 Miedinger - Juli 2019

### Changelog

- [UPDATE] Ultraschall now includes the SWS Plug-in V2.10.0.
  [https://github.com/Ultraschall/ultraschall-portable/issues/112](https://github.com/Ultraschall/ultraschall-portable/issues/112)

- [FIXED] Plug-in: Improve Update Check. (Thanks, [@343max](https://twitter.com/343max))
  [https://github.com/Ultraschall/ultraschall-portable/issues/26](https://github.com/Ultraschall/ultraschall-portable/issues/26)

- [FIXED] Ultraschall crashes on import of chapter markers when the selected input file contains malformed timestamp entries. (Thanks, [@moritzklenk](https://twitter.com/moritzklenk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/111](https://github.com/Ultraschall/ultraschall-portable/issues/111)

- [FIXED] The chapter marker export includes region markers.
  [https://github.com/Ultraschall/ultraschall-portable/issues/46](https://github.com/Ultraschall/ultraschall-portable/issues/46)

- [FIXED] The chapter marker export fails if a chapter marker title contains one or more non-ASCII character(s). (Thanks, Marcus von [@diezugfunker](https://twitter.com/diezugfunker))
  [https://github.com/Ultraschall/ultraschall-portable/issues/110](https://github.com/Ultraschall/ultraschall-portable/issues/110)

- [FIXED] The chapter marker export fails if the length of a chapter marker title exceeds 62 characters.
  [https://github.com/Ultraschall/ultraschall-portable/issues/109](https://github.com/Ultraschall/ultraschall-portable/issues/109)

### Known Issues

- [FEATURE] The Apple Podcast app (iOS) does not display exported chapter marker in MP3 files. (Thanks, [@twittlik](https://twitter.com/twittlik))
  [https://github.com/Ultraschall/ultraschall-portable/issues/113](https://github.com/Ultraschall/ultraschall-portable/issues/113)

- [BUG] The iTunes preview website does not play podcasts that contain exported data from Ultraschall. (Thanks, [@schanzpaulifunk](https://twitter.com/schanzpaulifunk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/114](https://github.com/Ultraschall/ultraschall-portable/issues/114)

## 3.1 Miedinger - January 2018

- REAPER: **Support for version 5.70**
  _Ultraschall 3.1 has been optimized for REAPER version 5.70. It will not run with any other versions or REAPER._ **We strongly advise you to avoid manual REAPER updates in the future**. _This will lead to the Ultraschall extension being disabled._

- Theme: **Master Channel always visible in the Mixer**
  _The Master channel in the mixer is now visible by default in all views without having to toggle the visibility using the Tab key. The Master channel is divided into two sections: the normal output signal is displayed in the center, and a RMS meter with an average of 2,000 milliseconds is located to the left and right. In combination with the new Ultraschall Dynamics2 effect this enables you to determine whether you constantly achieve the desired -16LUFS. The actual measurement is carried out in RMS instead of LUFS, however this is still accurate enough to provide a practical approximation for vocal recordings. The states are marked by color: Blue- up to -18 LUFS (mix is too quiet) Green- -18 to -14 LUFS (mix volume is properly set) Yellow- -14 to -12 LUFS (mix is too loud, this level should only be reached occasionally) Orange: -12 to 0 LUFS (mix is considerably too loud). The desired mix only occasionally leaves the green zone when there is talking._

  [Video: Master Mix and RMS Display](http://ultraschall.fm/wp-content/uploads/2018/01/Master_Mix_and_RMS.gif)

- Mastering: **Ultraschall Dynamics2 Loudness Normalization** _The Dynamics effect for loudness normalization of tracks in the 3.0 Release has received a major overhaul: three sliders now let you control the target volume (typically -16dB LUFS), noise floor (volume threshold at which a signal is considered noise) and a noise gate (steeper or slower or off). The effect has also been updated with a limiter to avoid digital clipping. You can save custom preference – even per track – as presets as well._

  [Video: Ultraschall Dynamics 2 Loudness Normalization](http://ultraschall.fm/wp-content/uploads/2018/01/dynamics2b.gif)

- Export (Mac): **Exporting and Tagging of m4a**
  _In macOS in the Render Assistant you can now generate m4a files as well. The Export Assistent will include chapter markers, meta data and episode cover just as is the case with mp3 files._

  [Video: m4a Export](http://ultraschall.fm/wp-content/uploads/2018/01/m4a_export.gif)

- Theme: **Optimized View of selected Items**
  _Selected items will no longer be highlighted by brightness, but rather by a golden frame._

  [Video: Select Items](http://ultraschall.fm/wp-content/uploads/2018/01/Select_Items.gif)

- Theme: **Alternative wave form view**
  _Use the shortcut `alt`+`shift`+`h` to change the wave form in such a way that the waves will no longer extend in both directions from the center line, but rather up from the bottom line._

  [Video: Rectify Peaks](http://ultraschall.fm/wp-content/uploads/2018/01/Rectify_Peaks.gif)

- Theme: **Wave Form Display as Spectograph**
  _By means of the Peak Display Settings you can display a spectrograph alongside the typical wave form – ideal to identify hum or buzz noise._

  [Video: Spectograph](http://ultraschall.fm/wp-content/uploads/2018/01/Spektrogramm.gif)

- Theme: **Volume Zoom of the Wave Form**
  _Using the shortcut `alt`+`h` you can vertically zoom the wave form in two steps. Doing so might make editing of very quiet passages easier for you._

  [Video: Toggle Peak Gain](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Peak_Gain.gif)

- Editing: **Zoom to Edit Cursor**
  _Using the shortcut `z` you can directly zoom in to the Edit cursor for fine editing at a suitable zoom level. Pressing `z` again will zoom back out to the previous zoom level._

  [Video: Toggle Arrange Zoom](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arrange_Zoom.gif)

- Theme: **Limiting Zoom-Out**
  _Particularly when `pinch-zooming` using the trackpad you might happen to zoom out too far, making it difficult to find your project. The maximum zoom-out is now limited to project length (project completely visible). Using `alt`+`pinch-zoom` you can use the tradition unlimited zoom feature._

  [Video: Zoom Limiter](http://ultraschall.fm/wp-content/uploads/2018/01/Zoom_Limiter.gif)

- Theme: **Zoom to Playhead**
  _Using `pinch-zoom` you still zoom in to the position of the mouse cursor. Using the keyboard zoom via the `+` and `-` keys however you zoom to the playhead position. Using the `^` key will move to the Edit, Record or playhead without zooming._

  [Video: Zoom to Playhead](http://ultraschall.fm/wp-content/uploads/2018/01/Zoom_to_Cursor.gif)

- Theme: **Ultraclock**
  _The "Recording" view shows an advanced clock - it shows the current position of the playhead as before, but also the current transport status (stop, pause, play, record, loop) in color. Furthermore the current time is shown – handy for planning start and end of a live broadcast. Use the right mouse button to open a context menu for adjusting the displayed information._

  [Video: Ultraclock](http://ultraschall.fm/wp-content/uploads/2018/01/Ultraclock.gif)

- Theme: **Optimized Tooltips**
  _All button now feature practical tool tips when hovering over them with your mouse cursor._

  [Video: Tool Tips](http://ultraschall.fm/wp-content/uploads/2018/01/tooltipps.gif)

- Theme: **Display of the Recording Format**
  _The right hand side of the menu bar now also shows the used recording format alongside the free disk space. Standard for typically gain staged recordings is FLAC (lossless compression) in 16bit at 48KHz. Feel free to adjust this to 24bit if you are in need of more headroom from the higher bit rate._

  [Video: Recording Info](http://ultraschall.fm/wp-content/uploads/2018/01/Recinfo.gif)

- Theme: **Envelope Tracks**
  _Envelope tracks now show their type names such as “Mute”, “Volume”, etc. Using `shift`+`h` you can toggle the height - similar to changing track height using `h`._

  [Video: Envelope Info](http://ultraschall.fm/wp-content/uploads/2018/01/Envelope_Info.gif)

- Theme: **Optimized RecArm Behavior**
  _When creating new track using the Podcast menu or the shortcut `cmd`+`t`, these are still enabled for recording (RecArm). When creating a track using a double click in the left track area or via the mixer or drag & drop, these will not be record enabled._

  [Video: Auto Arm new Tracks](http://ultraschall.fm/wp-content/uploads/2018/01/Auto_Arm_New_Tracks.gif)

- Theme: **Switching the RecArm Status for all Tracks**
  _Using the `shift`+`a` shortcut you can arm all tracks for recording or disarm them respectively if they have been armed before. Switching the status only works when not recording._

  [Video: Toggle RecArm all Tracks](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arm_all_Tracks.gif)

- Theme: **Toggling the Playback Speed**
  _Using the `alt`+`j` shortcut you can toggle between 1.0x and 1.5x playback speed. If this is too fast: you can simply enter a different value on the play rate slider and toggle using `alt` + `j`. This value will be preserved. A big Thanks to leonidlezner!_

  [Video: Envelope Info](http://ultraschall.fm/wp-content/uploads/2018/01/Switch_Playrate.gif)

- Editing: **Follow Mode**
  _Using `cmd`+`f`or the relevant new icon you can enable or disable the Follow mode. Enabling will cause the timeline to jump to the current position of the play or record head and scoll along to keep track of the play head. Disabling will detach the timeline from the play head so you can work on other areas within the project without having to stop playback or recording. All chapter marker features will relate to the position of the Edit cursor and no longer the play/record cursor._

  [Video: Follow Mode](http://ultraschall.fm/wp-content/uploads/2018/01/follow.gif)

- Editing: **Edit time selection on the edges**
  _You can now grab and move a time selection from both of the outer edges._

  [Video: Adjust Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Adjust_Time_Selection.gif)

- Editing: **Time selection will automatically select items**
  _When you mark a certain time selection with the Time Selection tool enabled, the actual item will automatically be selected. Marking a time selection over multiple items will select all these items respectively._

  [Video: Select Items with Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Select_Items_with_Time_Selection.gif)

- Editing: **Muting selected items along the time selection**
  _Using `cmd`+`y` you can mute the time selection across all selected items. Using `cmd`+`shift`+`y` you can unmute this time selection again._

  [Video: Mute Items with Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Mute_Items_with_Time_Selection.gif)

- Editing: **Double Click to Play**
  _Double clicking in the timeline or editing window will start playback from the clicked position._

  [Video: Double Click to Play](http://ultraschall.fm/wp-content/uploads/2018/01/Double_Click_to_Play.gif)

- Editing: **Moving Items using the Keyboard**
  _Using the `alt`+`left` or `alt`+`right` keys respectively you can move items within the timeline. Press the `n` key to open a preference window for setting the increments._

  [Video: Nudge Items](http://ultraschall.fm/wp-content/uploads/2018/01/Nudge_Items.gif)

- Chapter Markers: **Importing planned Chapter Markers from the Clipboard**
  _You can now import any text from the clipboard as a planned chapter marker (green color) into the project. Line breaks determine the individual markers._

  [Video: Import planned Markers from Clipboard](http://ultraschall.fm/wp-content/uploads/2018/01/Import_from_Clipboard.gif)

- Chapter Markers: **Placing planned Chapter Markers**
  _Using the `b` shortcut you can place the next prepared marker at the current playhead or edit cursor position (depending on the follow mode, see above)._

  [Video: Set planned Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Planned_Markers2.gif)

- Chapter Markers: **Converting all Markers to planner Chapter Markers**
  _All markers in the project can be converted to green planned chapter markers. The existing order will be unaffected._

  [Video: Set all Markers to Planning Stage](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Planned.gif)

- Chapter Markers: **Visibility of Chapter Markers during Placement**
  _When placing chapter markers at the playhead or edit cursor while being outside the visible area, the timeline will be moved to the relevant position so you can actually see where you have placed the marker._

  [Video: Show Positioning of Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Show_Positioning_of_Markers.gif)

- Chapter Markers: **Always place Chapter Markets at Play/Record Cursor position**
  _By using the `cmd` key you can always place chapter markers at the pay/record cursor position (i.e. `cmd`+`m`, `cmd`+`e`, `cmd`+`b` and `cmd`+`shift`+`m` respectively). The Follow mode (see above) will be ignored in this case and the viewport won’t change. These features are particulary suitable to be assigned to a Midi interface._

  [Video: Always set Markers to Play/Rec Position](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Play.gif)

- Chapter Markers: **Chapter Marker Management**
  _In order to be able to edit existing chapter markers during listen through, the auto play feature of chapter markers in the chapter marker list will be disabled. Playback will simply resume no matter how you edit the chapter markers. To quickly jump to a chapter marker in the timeline, simply double click to the right of the marker in the free list area. The markers will be numbered for better orientation. The numbers won’t make it into the texts._

  [Video: Edit Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Edit_markers.gif)

- Misc: **Enhanced Keyboard Shortcuts**
  _The overview of all relevant [keyboard shortcuts](http://url.ultraschall-podcast.de/keymap31) in Ultraschall has been updated and expanded._

- Easter Egg: **Should you take your time**
  _Easter comes sooner than you might think. Using the `alt`+`cmd`+`shift`+`u` shortcut you can sweeten your wait._

- Misc: **Bug Fixes and Optimization**
  _Several smaller enhancements, particularly for special cases. Too many details might even unsettle you._

## 3.0.3 Miedinger - March 2017

- REAPER: **Commitment to a specific version number**
  _For the sake of troubleshooting and in order to maintain system stability, Ultraschall will check for a specific REAPER version ( **5.70** ) on every launch. Future releases will be bound to specific newer versions of REAPER **We therefore strongly advise NOT to manually update REAPER**, since the Ultraschall extensions would be deactivated._

- Actions: **Reworked Routing Snapshots**
  _It is sometimes necessary to prepare and recall different routing situations – e.g. using Studio-Link OnAir – such as pre-show with music on the stream, the actual show with all the speakers, and after-show with music at low volume. The routing snapshot area has therefore been reimplemented completely and enhanced with its own user interface. The snapshots now also support Sends to Master and Hardware Sends._

- Keymap: **Shortcuts for Routing Snapshots**
  _`F1` to `F4` access pre-defined Routing Snapshots. `Shift` + `F1` to `F4` writes the currently configured Routing Matrix into the respective snapshot slot._

- Keymap Mac: **Aligned with system standard**
  _The following shortcut actions were aligned with macOS' system standard: Drag-and-copy of items now works with `alt` + `primary clicking-and-holding`. The current project tab is closed by `cmd` + `w`._

- Streaming: **Update for Studio Link OnAir**
  _Fixes a rare stability problem in the Windows version of Studio Link OnAir._

- Editing: **Further improvements to `esc` key behavior**
  _The "delete entire selection" function now includes also unselected envelope points. Amazing._

- Editing: **Midi actions for EQ tuner**
  _Two new Ultraschall midi actions simplify moving the in- and outpoints via a classical EQ tuner on a midi interface: The middle setting has no effect, a turn to the left or right speeds up movements in the respective direction. The further the turn, the faster the in-/outpoint moves. The scripts (`ultraschall_midi_move_start_of_time_slection.lua` und `ultraschall_midi_move_end_of_time_slection.lua`) need to be manually assigned to a midi signal._

- Installer: **Update Check**
  _Update Checks can now be en- and disabled at any time in the new start screen of Ultraschall._

- Theme: **Expanded Ultraschall start screen**
  _The new start screen now also contains the information from the old `About Ultraschall...` menu, which is hereby removed._

- Soundboard: **Bugfix**
  _The Soundboard will no longer stop playback when recalling a Routing Preset._

- Soundboard: **Presets**
  _The Soundboard now uses presets throughout. This enables saving and loading of sound sets even during a recording. Such on-the-fly changes also enable to easily use more than 24 sounds during a show. One can assign the presets to one's own project presets, so that each session starts with the correct jingles._

## 3.0.2 Miedinger - 2017-03-09

- Editing: **Shortcuts for Inpoint and Outpoint**
  _Use the buttons `alt` + `i` and `alt` + `o` to jump to the beginning or end of a time selection. With `shift` + `i` and `shift` + `o` sound will be played from the respective position._

- Editing: **Improved ripple-cut**
  _The new ripple-cut function (`cmd` + `x` as well as the corresponding icon) now behaves more sensibly: if nothing is selected, nothing happens. If a time selection is selected, only this will be cut, regardless of items that may or may not be selected at the same time. If no time selection is selected, but exactly one item, a ripple cut (Tim's Ripple Cut) is made by means of its edges. If no time selection is selected, but several items, nothing happens._

- Editing: **Quickly change and freeze track height**
  _Use the `h` key to quickly switch between two (adjustable) track heights, which keep their height even when the window is changed in size. The switch affects all selected tracks. If no track is selected, all tracks are affected. The freezing of the height can be canceled with the zoom buttons beneath the vertical scrollbar._

- Keymap: **Optimization of keyboard shortcuts and mapping for Windows**
  _The assignment of shortcuts for Windows was adapted to the behavior on macOS. The PDF template now works the same on both systems. New shortcuts include: `shift` + `n` - Normalization of selected items as well as `alt` + `d` - Switch off all docks for distraction-free editing._

- Theme: **FX buttons on master channel**
  _The buttons for setting FX are now also visible in the master channel in any size._

- Actions: **Advanced Prepare all tracks for editing**
  _The function now includes switching on the sends of all tracks towards the master channel - a common source of mistakes for seemingly missing tracks in the final mix._

- Mastering: **Extended episode images**
  _To quickly use a standard image as episode image, you may now also use files with the name `cover.jpg`, `cover.jpeg` or `cover.png` in the project folder. Thanks to Mespotine for the idea._

## 3.0.1 Miedinger - 2017-03-05

- Streaming **Studio Link OnAir Streaming**
  _Thanks to the support by Studio Link OnAir you can now start a livestream of your show with a single click. The signal attached to the mastermix will be streamed via a public web-interface. There, you can set stream properties and share the URL._

- Installer: **Update Check**
  _Ultraschall will check upon launching whether a new version has been published. It will validate that compatible versions of plugin and theme are installed. If not it will warn you._

- Installer: **LAME MP3 Encoder**
  _The LAME MP3 Encoder in version 3.98.3 is automatically installed._

- Theme: **Ultraschall Start-up Screen**
  _A new start-up screen confirms the successful installation and provides initial hints and links to the support resources._

- Theme: **View Adjustments**
  _The view switchers in the top left now show the current mode after restarting Reaper (keyword: persistence layer). In the Edit view, the navigator window is now displayed over the whole width. Additionally, a new `Loudness` tab was added to the bottom left, which lets you measure the LUFS of tracks or individual items (see Ultraschall Dynamics)._

- Theme: **FX always visible in the mixer**
  _Due to the continually growing importance of effects (StudioLink, OnAir, Soundboard, Dynamics), the FX buttons in the tracks' mixer panel are now always visible, and remain so when you shrink the windows._

- Theme: **Waveform**
  _Selected items and cuts within the waveform are highlighted more clearly now._

- Theme: **User Interface**
  _Many GUI elements receive more contrast to increase their visibility._

- Theme: **Selection Tool**
  _You can now switch the mouse pointer between two editing modes: the previous mode selects and moves individual items on the timeline, while the new mode helps you select times for faster (ripple) cutting. Times can thus be selected anywhere on the timeline, not just on the upper edge as previously. A new icon, as well as the keyboard shortcut `#`, switch between the modes._

- Theme: **Emphasis on 'Prepare all tracks...'**
  _The menu action 'Prepare all tracks for editing' needs to be used after each recording and before cutting. It is now emphasised visually. Also, the function itself has been reimplemented and expanded. A new status dialogue is displayed to provide user feedback after successful completion._

- Theme: **Podcast Menu**
  _Several `Podcast` menu entries were updated and reordered more logically._

- Editing: **Volume Editing**
  _Selected tracks can be overlayed with a new volume envelope (pre-FX!) via the menu or the shortcut `alt`+`v`. That overlay helps you realize complex fadings or volume gradients. Moreover, we've added a new pre-FX gain controller to the track area's left part. This controller adjusts the total volume of a single track; with visual feedback by the waveform. The tracks' visibility is toggled via the top icon known from the mute track._

- Editing: **Easier Envelope Handling**
  _We reworked the mode of setting and moving points in the (mure or volume) envelopes. Now you simply move existing points or click at where the next point should be set. A muted section can thus be set via two clicks. The old free-hand drawing mode can be reactivated any time by pressing `cmd`._

- Editing: **Better `esc` Key Behaviour**
  _We believe in the future and necessity of the `esc` key. That's why we enhanced the "delete any selection" function considerably. It now deselects track, item, envelope and time markers._

- Editing: **Pre-Listening Cuts**
  _The shortcut `p` allows you to pre-listen the result of a cut by time markers, without actually applying the cut. This, together with the new shortcuts `<`, `y`, `x` und `c` for moving the in- and outpoints of a time selection, enables more efficient and controlled cutting._

- Editing: **Play Cursor at the Beginning of a Time Selection**
  _Selecting time places the play cursor directly at the inpoint of the selection, to that one can use `return` or `space` to directly listen to the selection._

- Editing: **Expanded Ripple Cut**
  _The shortcut `cmd` + `x` effects a ripple cut over all tracks, even when only a single item is selected. The cutting range will then be the start- and endpoint of the item._

- Keymap: **New Layout for Keyboard Shortcuts**
  _A multitude of shortcuts was reworked and newly added in order to enable more efficient cutting via the keyboard. The new shortcuts are visualised in a [.PDF](http://url.ultraschall-podcast.de/keymap) and you can reflect customizations in the corresponding PowerPoint source file._

- Mastering: **Ultraschall Dynamics**
  _The new Dynamics Effect can optimize the podcast's loudness to -16 LUFS. This effect replaces the previously recommended AU General Dynamic Effect and can also be applied in Ultraschall's Windows version. We deliver presets with and without soft noisegate in order to reduce faint disturbances. The effect can be used and parameterized on single tracks, single items, as well as on the master channel. Please note: the effect is less suited for the repair of audio problems (humming, reverberation, etc.) against which we highly recommend using [Auphonic](https://auphonic.com/)._

- Mastering: **Effect Templates for New Tracks**
  _Adding new tracks automatically adds the effects ReaEQ (Equalizer) and JS: General Dynamics, but without activating them._

- Mastering: **New EQ Preset**
  _Ultraschall 3 includes a new EQ preset, that delivers less bass boost then the preset from version 2. It is a good starting point for the headsets DT297 and HMC660._

- Mastering: **Export Assistant**
  _`Export` can be found in the bottom left icon bar and helps you generate perfect MP3 files. The ID3V2 elements metadata (like title, podcast, etc.), episode images and chapter marks will be written to the MP3 files you produce._

- Mastering: **Noise Filter**
  _We've added the ReaFix effect to the effect favorites in order to fix common sound problems like hissing or electric hum. Its use is explained in the Ultraschall Dynamics video._

- Mastering: **Open Project Directory**
  _the menu command and the icon for opening the project directory now does exactly that, instead of the subdirectory with the sound files._

- Actions: **Colorpicker**
  _The user-friendly Colorpicker (shortcut: `alt`+`c`) helps you keep the overview in complex projects; assign colors to tracks and single clips, or even gradients to multiple tracks, which can be fluid or using a sensible contrast range._

- Actions: **Import Chaptermarks from WAV Files**
  _Some devices - like Zoom H5 and H6 - allow writing chapter marks to the .WAV file during the recording. A new chapter mark action allows reading those and converts them into Ultraschall chaptermarks._

- Actions [Windows]: **Bugfix for Umlauts**
  _We fixed a bug in the handling of chaptermarks with mutated vowels. Thanks to [@jalea](https://twitter.com/jalea) and to Nico Buch for tracking down that error!_

- Soundboard: **Bugfix**
  _Fixed a bug where the soundboard would not pause playback when triggered with OSC. Thanks to Bastian Boessl for reporting this bug._

## 2.2.2 Gropius - 2016-8-14

- Soundboard [Mac]: **Bugfix**
  _Fixed a bug that prevented a recorded soundboard-track from playing._

- Misc [Windows]: **Compatibility**
  _Updates for Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

- StudioLink: **Update**
  _Ultraschall now includes the updated StudioLink version 16.04.1._

## 2.2.1 Gropius - 2016-06-09

- Installer: **Bugfix**
  _Fixed a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Marcus Schwarz for reporting this bug._

- Installer: **Bugfix**
  _Fixed another a bug that prevented the Uninstall script to delete legacy files from the system. Thanks to Wolfgang Schulz for reporting this bug._

## 2.2 Gropius - 2016-06-05

- Theme: **Theme fine-tuning**
  _Beautification of scroll bars, zoom icons and sliders in VST/AU effect displays_

- Actions: **Cough button and mute track**
  _Complete rework of the cough button und mute button feature. Before you start your recording session, the mute button toggles cough button activation. When your recording session is complete, the mute button toggles the display ot the mute track._

- Actions: **Track selection using the keyboard**
  _You can now toggle the selection of each track by using the numerical keys on your keyboard. Use '1' to '8' to toggle the selection of the respective track. Pressing '9' selects all tracks, '0' deselects all tracks._

- Actions: **Prepare all tracks for editing**
  _The script "Prepare all tracks for editing" for completing a recording session has been improved and more parameters have been added_

- Actions: **New menu item "Customize"**
  _Ultraschall 2.2 introduces the "Customize" menu item. You can use 'Shortcuts and action list' to change keyboard shortcuts and add new scripts to Ultraschall. Use 'Track: set track icon' and 'Show theme configuration window' to change the icons, colors and names of each track._

- StudioLink: **Full integration of the StudioLink plugin**
  _Ultraschall now supports the StudioLink plugin. With StudioLink you can record remote calls on up to 8 individual tracks without the need to setup the notorious 'N-1 Schalte'. Remote attendees are not required to use REAPER. They can download the StudioLink Standalone-App. See [StudioLink](https://doku.studio-link.de/standalone/installation-standalone.html)._

- Soundboard: **Soundboard for Windows**
  _The Ultraschall Soundboard now runs on Windows as a VST._

- Soundboard: **Soundboard audio unit for Mac**
  _The Ultraschall Soundboard for Mac is now an audio unit._

- Installer: **StudioLink Plugin**
  _The Ultraschall installer now includes the StudioLink plugin._

- Preferences: **Improved Stop Function**
  \*The stop function has been reworked in such a way that the cursor in recording mode is set to the end of the current recording. This is to prevent the creation of further takes if the recording session continues.

- Preferences: **Automatic Record Arm for newly inserted tracks**
  \*Tracks are now set to 'Record Arm' after they have been inserted into the REAPER project. You are not any longer required to press the red 'Record Arm'-button.

- Misc: **Ultraschall 3 Preset for ReaEQ**
  \*The preset Ultraschall 3 is automatically activated if you insert the ReaEQ Equaliyer into the tracks effect chain. This results in less rumble and less boost of lower frequencies.

- Misc: **Ultraschall Presets for audio compoitions**
  _The effect presets Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate) may be used for voice colorization in audio compositions_

- Installer: **Bugfix**
  _The code signature of Uninstall.command was corrupted. Thanks to Arnd Layer for reporting this bug._

## 2.1.1 Gropius - 2016-02-27

- Theme: **Further fine-tuning of the new theme**
- Windows: **Corrected color adjustments for audio tracks on Windows**

## 2.1 Gropius - 2016-02-19

- Theme: **Comprehensive fine-tuning of the new theme**
  _The contrast of nearly all elements was increased in order to enhance usability -- also in suboptimal lighting conditions. Groups of icons are now visually encapsulated. Individual icons were redesigned in order to clarify their function. The appeal of all buttons was harmonised. Many colors were fine-tuned in order to match Ultraschall's palette. Cuts within a track item are now marked by a clearer line._

- Theme: **Routing matrix contains display of input assignments**
  _In the lower area of the routing matrix, input channels can now be assigned to tracks. Thus, really all relevant assignments happen at a single site._

- Misc: **SWS/S&M Extension 2.8.3**
  _Ultraschall now comes with the [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/)._

- Actions: **New shortcuts for more fluent editing with the keyboard**
  _Start and end of a time selection can now be set with the `i` and `o` keys, just as in many video editing programs. The keys `1` and `2` now jump you to the start and end of a selection. The key assignments for jumping between chapter marks was changed, because it collided with the word-wise jumping within text sections._

- Actions: **Start/stop/pause safe mode for the keyboard**
  _In order to prevent the unintended stop of an ongoing recording, the keys `RETURN` and `SPACE` are now deactivated during a recording. A prompt will appear and can be affirmed to actually stop the recording._

- Actions: **More robust chapter mark functions**
  _All chapter mark functions were reimplemented in Lua and now take into account, whether a recording is **a)** ongoing, in which case the marker is set at the currently recorded position, or **b)** being played back, in which case it is set at the currently played position, or **c)** not applicable, in which case the marker is set to current position of the editing cursor. The MIDI connection was redesigned more robustly, so that chapter marks can be set via MIDI in any program state -- even when existing markers are being edited._

- Actions: **Labelling of Ultraschall actions**
  _All Ultraschall function are now uniformly pre-fixed with `ULTRASCHALL:` and more clearly labelled in the actions dialogue for the keyboard assignments, which is accessible through the `?` key._

- Soundboard [Mac only]: **Bugfix**
  _REAPER crashes when the folder that is to be loaded into the soundboard contains only one audio file. Thanks to Sven Wiegand for reporting this bug._

- Soundboard: **Bugfix**
  _REAPER crashed when the folder that is to be loaded into the soundboard contained an audio file that can't be decoded. Thanks to René Kurfürst for reporting this bug._

## 2.0 Gropius - 2015-12-09

- Misc: **Reaper 5 and OS X 10.11 El Capitan**
  _Ultraschall is now optimized for Reaper 5 and OSX 10.11 El Capitan. Older version are not be supported any more._

- Installer [Mac only]: **User, instead of system, library**
  _The new installer writes its entries into the user library of OS X, instead of the system library._

- Theme: **Complete redesign**
  _More consistency, less clutter. All icons and functional elements have been reworked and colors were harmonized._

- Theme: **Responsive mixer**
  _Depending on the dock's height, the new mixer panel shows or hides some control elements._

- Theme: **New "Storyboard" view for audio compositions**
  _You can now tag areas in your recording -- such as individual answers in an interview -- and later search and filter, also across different projects. Any number of clip databases can be managed. Colors and comments are available, to keep the overview in complex projects. Finished sections and regions can be grouped. Text elements can be distributed freely in the cutting area, in order to manage show notes or comments._

- Actions [Mac only]: **About Screen**
  _A new menu entry_ `Podcast | About Ultraschall…` _displays the installed components and their version numbers._

- HUB [Mac only]: **New audio driver**
  _Soundflower is a thing of the past: following the new CoreAudio APIs in OSX 10.11 El Capitan, the audio engine for virtual sound devices has been revised from the ground up._

Older, untranslated changes are listed [in German only](https://github.com/Ultraschall/REAPER/blob/master/CHANGELOG-DE.md), because Ultraschall was not available in English back then.
