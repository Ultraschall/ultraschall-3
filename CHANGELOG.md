# Changelog

## Syntax of the changelog

* **Preferences:** Changes to Reaper's preferences dialog, which can be opened via `⌘`+`,` or through the `Reaper | Preferences` menu.
* **Theme:** These changes affect the design or arrangement of elements (buttons, controllers, displays, etc.) of the theme we provide.
* **Actions:** Adds new features and changes that affect the keyboard, mouse or trackpad bindings to actions or presets.
* **Soundboard:** Features of our own Soundboard for audio snippets/shorts/inserts.
* **Installer:** New features for the Mac installer which was introduced with Ultraschall 1.2.
* **Hub [Mac only]:** Our project to replace [Soundflower](https://github.com/mattingalls/Soundflower/releases/tag/2.0b2), and to provide a stable, crackle-free podcasting experience.
* **Misc:** Anything that is left.

## 2.2 Gropius - 2016-Mai-xx

* Theme: **Weiteres Feintuning des neuen Themes**
*Die Scrollbalken sowie Zoom-Icons wurden vereinfacht, ebenso Schieberegler in AU/VST-Effekten.*

* Actions: **Räuspertaste und Mute-Spur**
*Komplette Neukonzeption der Räuspertasten- und Mute-Funktion. Der editierbare Mute-Envelope wird nun immer in einer Separaten Spur angezeigt und farblich besser hervorgehoben. Der Mute-Button in der Iconleiste funktioniert nun kontexabhängig: vor einer Aufnahme können ausgewählte Spuren für die Räuspertaste aktiviert werden. Während und nach der Aufnahme schaltet er die Sichtbarkeit der Mute-Spuren ein oder aus.*

* Actions: **Auswahl von Spuren über Tastatur**
*Über die Zahlentasten 1 bis 8 können die jeweiligen Spuren markiert oder unmarkiert werden. 9 markiert sämtliche Spuren, 0 hebt die Markeirung sämtlicher Spuren auf.*

* Actions: **Alle Spuren für Schnitt vorbereiten**
*Die Befelsfolge "Prepare all tracks for editing", die nach jeder Aufnahme aufgerufen werden sollte, wurde verbessert und stellt weitere Parameter für den Schnitt um.*

* Actions: **Neuer Menü-Eintrag "Customise"**
*Im Podcast-Menü sind unter dem neuen Eintrag "Customise" folgende Funktionen zusammengefasst: 'Shortcuts and action list' um Tastaturkürzel neu definieren zu können und neue Funktionen hinzuzufügen, 'Track: set track icon' um Spuren mit einem Symbol verzieren zu können, 'Show theme configuration window' um Farben des Theme anzupassen, 'Show theme element finder' um die Benamung von einzelnen Elementen der GUI zu finden sowie 'Auto color' um die Standardfarben von Spuren in Abhängigkeit ihres Namens festzulegen. Weitere Hinweise über die Anpassbarkeit von Ultraschall/Reaper zeigt dieser Vortrag:*

* StudioLink: **Vollständige Integration des StudioLink Plugins**
*Als qualitativ in Bezug auf Stabilität, Konstanz und Klangqualität weit überlegene Alternative zu Skype unterstützt Ultraschall nun StudioLink. Ohne den Aufbau einer N-1 Schaltung über die Routingmatrix ist es damit möglich, Ferngespräche mit bis zu 8 PartnerInnen zu führen, die in jeweils separaten (!) Spuren aufgezeichnet werden. Die PartnerInnen können dabei die schlanke Standalone-Version von StudioLink nutzen und benötigen keine eigene DAW. Die Einrichtung einer StudioLink-Schaltung wird im Release-Video erläutert.*

* Soundboard: **Soundboard nun auch für Windows und als AU Version für den Mac**
*Das Ultraschall-Spundboard steht nun mit vollem Funktionsumfang auch unter Windows zur Vefügung. Bei der Mac-Version wurde von VST auf AU Technik umgestellt.*

* Installer: **StudioLink Plugin und standalone**
*Ultraschall liefert im Installer die Version des StudioLink-Plugins aus. Externe GesprächspartnerInnen können sich die [Standalone-Fassung von StudioLink](https://doku.studio-link.de/standalone/installation-standalone.html) laden.*

* Preferences: **Stop Funktion überarbeitet**
*Die Stop Funktion bei Aufnahmen wurde so überarbeitet, dass der Aufnahme-Cursor nach Stop an das Ende der bisherigen Aufnahme gesetzt wird. Dies verhindert, dass bei einem erneuten Start der Aufnahme kein alternativer Take angelegt wird, sondern die eigentliche Aufnahme fortgesetzt wird.*

* Preferences: **Neue Spuren werden direkt für die Aufnahme aktiviert**
*Alle neu angelegten Spuren werden direkt auf "Record Arm" geschaltet und sind bereit für die Aufnahme - der zusätzliche Klick auf den roten Arm-Knopf kann damit oft entfallen.*

* Misc: **Ultraschall 3 Preset für ReaEQ**
*Standardmäßig wird bei Aktivierung des ReaEQ Equalizers das Preset Ultraschall 3 aktiviert, dass deutlich weniger Bassanhebung und damit Poltern mit sich bring.*

* Misc: **Ultraschall Presets für gebaute Beiträge**
*Folgende Effekte werden als Ultraschall-Presets für die Verfremdung von Stimmen für gebaute Beiträge angeboten: Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate)*

* Installer: **Bugfix**
*The code signature of Uninstall.command was corrupted on image creation. Thanks to Arnd Layer for reporting this bug.*

## 2.1.1 Gropius - 2016-Feb-27

* Theme: **More fine-tuning of the new theme**
* Windows: **Anpassung der Farbwerte für die Audiospuren**
*Auch unter Windows stimmen nun die Zuordnungen von Bezeichnungen und Farbwerte*

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
