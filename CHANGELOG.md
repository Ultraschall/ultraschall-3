# Changelog

## Syntax of the changelog


* **Preferences:** Changes to Reaper's preferences dialog, which can be opened via `⌘`+`,` or through the `Reaper | Preferences` menu.  
* **Theme:** These changes affect the design or arrangement of elements (buttons, controllers, displays, etc.) of the theme we provide.  
* **Actions:** Adds new features and changes that affect the keyboard, mouse or trackpad bindings to actions or presets.  
* **Soundboard [Mac only - yet]:** Features of our own Soundboard for audio snippets/shorts/inserts.  
* **Installer [Mac only]:** New features for the Mac installer which was introduced with Ultraschall 1.2.  
* **Hub [Mac only]:** Our project to replace [Soundflower](https://github.com/mattingalls/Soundflower/releases/tag/2.0b2), and to provide a stable, crackle-free podcasting experience.  
* **Misc:** Anything that is left.

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
