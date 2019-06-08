# Ultraschall Changelog

Die nachfolgenden Features werden ausführlich in unseren Ultraschall-Tutorial-Videos erklärt: [http://ultraschall.fm/tutorials/](http://ultraschall.fm/tutorials/)

## 3.2 Miedinger - Juli 2019

### Änderungsprotokoll

- [UPDATE] Ultraschall enthält jetzt die Version 2.10.0 des SWS Plug-ins.
  [https://github.com/Ultraschall/ultraschall-portable/issues/112](https://github.com/Ultraschall/ultraschall-portable/issues/112)

- [FIXED] Die Zeit, nach der ein erneuter Update-Check ausgeführt werden soll, wird falsch berechnet. (Danke, [@343max](https://twitter.com/343max))
  [https://github.com/Ultraschall/ultraschall-portable/issues/26](https://github.com/Ultraschall/ultraschall-portable/issues/26)

- [FIXED] Absturz beim Import von Kapitelmarken, wenn die ausgewählte Datei fehlerhafte Zeiteinträge enthält. (Danke, [@moritzklenk](https://twitter.com/moritzklenk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/111](https://github.com/Ultraschall/ultraschall-portable/issues/111)

- [FIXED] Beim Export von Chaptermarks werden auch Regions exportiert.
  [https://github.com/Ultraschall/ultraschall-portable/issues/46](https://github.com/Ultraschall/ultraschall-portable/issues/46)

- [FIXED] Der Export von Kapitelmarken schlägt fehl, wenn eine Kapitelmarke eine oder mehrere Nicht-ANSI-Zeichen enthält. (Danke, Marcus von [@diezugfunker](https://twitter.com/diezugfunker))
  [https://github.com/Ultraschall/ultraschall-portable/issues/110](https://github.com/Ultraschall/ultraschall-portable/issues/110)

- [FIXED] Der Export von Kapitelmarken schlägt fehl, wenn die Länge eines Kapitelmarkentitels 62 Zeichen überschreitet.
  [https://github.com/Ultraschall/ultraschall-portable/issues/109](https://github.com/Ultraschall/ultraschall-portable/issues/109)

### Bekannte Probleme

- [FEATURE] Exportierte Kapitelmarken in MP3-Dateien werden in der Apple Podcast-App (iOS) nicht angezeigt. (Danke, [@twittlik](https://twitter.com/twittlik))
  [https://github.com/Ultraschall/ultraschall-portable/issues/113](https://github.com/Ultraschall/ultraschall-portable/issues/113)

- [BUG] MP4-Dateien, die exportierte Ultraschall-Daten enthalten, werden in der iTunes-Vorschau nicht wiedergegeben. (Danke, [@schanzpaulifunk](https://twitter.com/schanzpaulifunk))
  [https://github.com/Ultraschall/ultraschall-portable/issues/114](https://github.com/Ultraschall/ultraschall-portable/issues/114)

## 3.1 Miedinger - 2018-Januar

- REAPER: **Unterstützung der Version 5.70**
  _Ultraschall 3.1 ist für die Version 5.70 von REAPER optimiert. Alle anderen Versionen sind nicht lauffähig._ **Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen**, _die Ultraschall-Erweiterungen werden dann deaktiviert._

- Theme: **Master-Kanal im Mixer immer sichtbar**
  _In allen Views ist nun auch der Master-Kanal direkt rechts im Mixer sichtbar und muss nicht mehr über einen Tab umgeschaltet werden. Der Master-Kanal ist in der Anzeige zweigeteilt: in der Mitte das normale aktuelle Signal, breiter links und rechts daneben eine RMS-Anzeige mit dem Mittel von 2000 Millisekunden. Dies ermöglicht in Kombination mit dem neuen Ultraschall Dynamics2 Effekt eine schnelle Einordnung, ob die gewünschen -16LUFS konstant erreicht oder über-/unterschritten werden. Die Messung erfolgt zwar nicht in LUFS sondern in RMS, was aber als Näherungswert in der Praxis für Sprachaufnahmen ausreicht. Farblich werden folgende Zustände unterschieden: Blau-bis -18 LUFS (Mix ist zu leise) Grün- -18 bis -14 LUFS Aufnahme ist perfekt in der Lautstärke Gelb- -14 bis -12 LUFS (Aufnahme ist zu laut, sollte nur selten erreicht werden) Orange: -12 bis 0 LUFS (Aufnahme ist deutlich zu laut). Gewünscht ist ein Mix, bei dem die Aussteuerung im Master nur selten die grüne Zone verlässt wenn gesprochen wird._

      	[Video: Master Mix and RMS Display](http://ultraschall.fm/wp-content/uploads/2018/01/Master_Mix_and_RMS.gif)

- Mastering: **Ultraschall Dynamics2 Loudness Normalization**
  _Der Dynamics-Effekt zum Vereinheitlichen der Lautstärke von Spuren der 3.0 Release wurde erheblich erweitert: über drei Schieberegler lassen sich nun Target-Lautstärke (normalerweise: -16LUFS), Noisefloor (Trennwert, ab dem ein Signal als Rauschen/Störung interpretiert wird und nicht als Stimme) sowie Noisegate (steiler oder flacher bzw. aus) je nach Anforderung einstellen. Der Effekt hat zudem einen Limiter-Effekt eingebaut der digitales Clipping abfängt. Eigene Einstellungen können - auch pro Spur - als Preset gespeichert werden._

      	[Video: Ultraschall Dynamics 2 Loudness Normalization](http://ultraschall.fm/wp-content/uploads/2018/01/dynamics2b.gif)

- Export (Mac): **Export und Tagging von m4a**
  _Es können nun auf macOS im Render-Assistenten auch m4a-Dateien generiert werden. Im Export-Assistenten werden diese genauso wie bisher MP3 mit Kapitelmarken, Metadaten und Epispodencover versehen._

      	[Video: m4a Export](http://ultraschall.fm/wp-content/uploads/2018/01/m4a_export.gif)

- Theme: **Anzeige ausgewählter Items optimiert**
  _Nur echt mit der Goldkante: ausgewählte Items werden nicht mehr durch Helligkeit hervorgehoben, sondern durch eine gut sichbare goldene Umrahmung._

      	[Video: Select Items](http://ultraschall.fm/wp-content/uploads/2018/01/Select_Items.gif)

- Theme: **Alternative Darstellung der Wellenform**
  _Mit dem Shortcut `alt`+`shift`+`h` kann die Darstellung der Wellenform so umgestellt werden, dass die Peaks nicht von der Mitte sondern der Grundlinie aus wachsen._

      	[Video: Rectify Peaks](http://ultraschall.fm/wp-content/uploads/2018/01/Rectify_Peaks.gif)

- Theme: **Darstellung der Wellenform als Spektogramm**
  _Mit Hilfe der Peak Display Settings kann man sich ergänzend zur normalen Wellenform ein Spektrogramm anzeigen lassen - hilfreich, um etwa Brummgeräusche zu identifizieren._

      	[Video: Spektogramm](http://ultraschall.fm/wp-content/uploads/2018/01/Spektrogramm.gif)

- Theme: **Lautstärke-Zoom der Wellenform**
  _Mit dem Shortcut `alt`+`h` wird die Ansicht der Wellenform vertikal in zwei Stufen gezoomt. Man kann damit auch sehr leise Passagen gut sichtbar und editierbar schalten._

      	[Video: Toggle Peak Gain](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Peak_Gain.gif)

- Editing: **Zoom zu Edit-Cursor**
  _Mit dem Shortcut `z` wird direkt zu einer für Feinschnitt passenden Zoomstufe zum Edit-Cursor hin gezoomt. Nochmaliges Drücken von `z` springt wieder in die vorherige Zoomstufe zurück._

      	[Video: Toggle Arrange Zoom](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arrange_Zoom.gif)

- Theme: **Begrenzung des Zoom-Out**
  _Insbesondere bei einem `Pinch-Zoom` auf dem Trackpad konnte es leicht passieren, dass man viel zu weit herausgezoomt hat und sein Projekt nicht wieder gefunden hat. Der maximale Zoom-Out ist nun auf die Projektlänge begrenzt (ganzes Projekt sichtbar). Über `alt`+`Pinch-Zoom` erhält man die bisherige, unlimitierte Zoomfunktion._

      	[Video: Zoom Limiter](http://ultraschall.fm/wp-content/uploads/2018/01/Zoom_Limiter.gif)

- Theme: **Zoom zu Cursor**
  _Mit dem `Pinch-Zoom` wird wie bisher immer an die Stelle gezoomt, an der sich der Mauszeiger befindet. Nutzt man hingegen die Zoomfunktion über die Tastatur `+` bzw. `-`, so wird zur Position des Cursors gezoomt. Der Shortcut `^` Springt ohne Zoom zum Edit-/Rec-/Play-Cursor._

      	[Video: Zoom to Cursor](http://ultraschall.fm/wp-content/uploads/2018/01/Zoom_to_Cursor.gif)

- Theme: **Ultraclock**
  _Im View "Recording" wird eine erweiterte Uhr angezeigt - sie zeigt wie bisher die aktuelle Position des Play-/Record-/Edit-Cursors, jedoch zusätzlich den aktuellen Transport-Status (Stop, Pause, Play, Record, Loop) in Farbe. Darüber ist die aktuelle Uhrzeit zu sehen - nützlich, um Start oder Ende einer Live-Sendung perfekt zu timen. Mit der rechten Maustaste können über ein Kontextmenü die angezeigten Informationen angepasst werden._

      	[Video: Ultraclock](http://ultraschall.fm/wp-content/uploads/2018/01/Ultraclock.gif)

- Theme: **Tooltips optimiert**
  _Alle Buttons haben jetzt aussagekräftige Tooltipps wenn man mit dem Mauszeiger länger darauf verweilt._

      	[Video: Tooltips](http://ultraschall.fm/wp-content/uploads/2018/01/tooltipps.gif)

- Theme: **Anzeige des Recording-Formates**
  _In der Menüleiste wird nun rechts nicht nur der noch freie Speicherplatz angezeigt, sondern auch das verwendete Recording-Format. Als Standard ist für normal ausgesteuerte Aufnahmen FLAC (verlustfreie Kompression), 16Bit 48KHz eingestellt. Natürlich kann dies für anspruchsvollere Aufnahmesituationen etwa auf 24Bit angehoben werden._

      	[Video: Recording Info](http://ultraschall.fm/wp-content/uploads/2018/01/Recinfo.gif)

- Theme: **Envelope-Spuren**
  _Bei Envelope Spuren werden nun deren Typnamen angezeigt - also etwa "Mute", "Volume" etc. Mit dem Shortcut `shift`+`h` kann ihre Höhe umgeschaltet werden - vergleichbar zum Umschalten der Trackhöhe mit `h`._

      	[Video: Envelope Info](http://ultraschall.fm/wp-content/uploads/2018/01/Envelope_Info.gif)

- Theme: **RecArm Verhalten optimiert**
  _Wenn neue Tracks über das Podcast-Menü oder ober den Shortcut `cmd`+`t` angelegt werden, sind sie wie bisher direkt für die Aufnahme scharf geschaltet (RecArm). Legt man Tracks über Doppelklick im linken Spurbereich oder im Mixer an, oder über drag & drop, so sind sie nicht direkt scharfgeschaltet._

      	[Video: Auto Arm new Tracks](http://ultraschall.fm/wp-content/uploads/2018/01/Auto_Arm_New_Tracks.gif)

- Theme: **Umschalten des RecArm-Status für alle Tracks**
  _Mit dem Shortcut `shift`+`a` können alle Tracks für eine Aufnahme scharfgeschaltet werden bzw. die Scharfschaltung aufgehoben werden. Das Umschalten funktioniert nur, wenn keine Aufnahme läuft._

      	[Video: Toggle Arm all tracks](http://ultraschall.fm/wp-content/uploads/2018/01/Toggle_Arm_all_Tracks.gif)

- Theme: **Umschalten der Playrate**
  _Mit dem Shortcut `alt`+`j` kann die Playrate von 1.0 zu 1.5 und zurück geschaltet werden. Wem das zu schnell ist: man kann auch einen anderen Wert am Playrate-Schieber einstellen und ebenfalls per `alt`+`j` speichern/umschalten. Der Wert bleibt erhalten. Dank an leonidlezner!_

      	[Video: Envelope Info](http://ultraschall.fm/wp-content/uploads/2018/01/Switch_Playrate.gif)

- Editing: **Folgen-Modus**
  _Mit `cmd`+`f`oder dem entsprechenden neuen Icon wird der Folgen-Modus aktiviert oder deaktiviert. Ein Aktivieren führt immer dazu, dass die Timeline zur aktuellen Position des Play- oder Record-Cursors springt und die Timeline ab dann mitscrollt. Ein deaktivieren entkoppelt die Timeline vom Abspielen oder Aufnehmen - man kann somit andere Stellen im Projekt bearbeiten, ohne dass Wiedergabe oder Aufnahme stoppt. Sämtliche Kapitelmarken-Funktionen beziehen sich ab dann auch auf die Position des Edit-Cursors, nicht wie sonst auf Play-/Record-Cursor._

      	[Video: Follow Mode](http://ultraschall.fm/wp-content/uploads/2018/01/follow.gif)

- Editing: **Zeitauswahl editieren an Kanten**
  _Eine Zeitauswahl kann nun überall an den beiden äußeren Kanten angefasst und verschoben werden._

      	[Video: Adjust Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Adjust_Time_Selection.gif)

- Editing: **Zeitauswahl selektiert direkt auch Items**
  _Wenn das Zeitauswahl-Werkzeug aktiviert ist, und man damit über ein Item zieht um eine Zeitauswahl vorzunehmen, wird nun auch direkt das entsprechende Item ausgewählt. Zieht man über mehrere Items, werden diese gemeinsam mit ausgewählt._

      	[Video: Select Items with Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Select_Items_with_Time_Selection.gif)

- Editing: **Muten ausgewählter Items entlang der Zeitauswahl**
  _Mit `cmd`+`y` werden alle ausgewählten Items gemutet, und zwar über den Zeitraum der Zeitauswahl. Mit `cmd`+`shift`+`y` wird eine Zeitauswahl wieder unmuted._

      	[Video: Mute Items with Time Selection](http://ultraschall.fm/wp-content/uploads/2018/01/Mute_Items_with_Time_Selection.gif)

- Editing: **Doppelklick für Play**
  _Ein Doppelklick in der Zeitleiste oder dem Editierfenster spielt ab der angeklickten Position ab._

      	[Video: Double-Click to Play](http://ultraschall.fm/wp-content/uploads/2018/01/Double_Click_to_Play.gif)

- Editing: **Verschieben von Items über Tastatur**
  _Mit den Tasten `alt`+`links` bzw. `alt`+`rechts` können markierte items in der Timeline verschoben werden. Über die Taste `n` erreicht man ein Einstellungsfenster, mit dem man die Laufweite festlegen kann._

      	[Video: Nudge Items](http://ultraschall.fm/wp-content/uploads/2018/01/Nudge_Items.gif)

- Kapitelmarken: **Importieren geplanter Kapitelmarken aus der Zwischenablage**
  _beliebige Texte können aus der Zwischenablage als geplante Kapitelmarken (grüne Farbe) in das Projekt eingefügt werden. Zeilenumbrüche definieren die einzelnen Marken._

      	[Video: Import planned Markers from Clipboard](http://ultraschall.fm/wp-content/uploads/2018/01/Import_from_Clipboard.gif)

- Kapitelmarken: **Setzen geplanter Kapitelmarken**
  _Mit dem Shortcut `b` wird die jeweils nächste vorbereitete Marke an die aktuelle Position des Play-/Record-Cursors bzw des Edit-Cursors (abhängig vom Folgen-Modus (siehe oben)) gesetzt._

      	[Video: Set planned Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Planned_Markers2.gif)

- Kapitelmarken: **Umwandeln aller Marker in geplante Kapitelmarken**
  _Alle im Projekt befindlichen Marker können in grüne vorbereitete Marker verwandelt werden; die bisherige Reihenfolge bleibt dabei erhalten._

      	[Video: Set all Markers to Planning Stage](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Planned.gif)

- Kapitelmarken: **Sichtbarkeit von Kapitelmarken beim Setzen**
  _Werden Kapitelmarken an Play- oder Edit-Cursor gesetzt, während diese außerhalb des sichtbaren Bereiches sind, wird die Timeline an die entsprechende Stelle verschoben so dass man sieht, wo die Marker gesetzt werden._

      	[Video: Show Positioning of Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Show_Positioning_of_Markers.gif)

- Kapitelmarken: **Kapitelmarken immer an Play-/Record-Cursor setzen**
  _Kapitelmarken können durch zusätzliche Verwendung von `cmd` immer an die Position des Play-/Record-Cursor gesetzt werden (also `cmd`+`m`, `cmd`+`e`, `cmd`+`b` sowie `cmd`+`shift`+`m`). Der Follow-Modus (siehe oben) wird dabei ignoriert und auch der Viewport ändert sich nicht. Diese Funktionen eignen sich gut, um sie etwa auf ein Midi-Interface zu legen._

      	[Video: Set Markers always to Play/Rec Position](http://ultraschall.fm/wp-content/uploads/2018/01/Set_Markers_to_Play.gif)

- Kapitelmarken: **Kapitelmarkenverwaltung**
  _Um während des Abhörens in Ruhe bestehende Kapitelmarken editieren zu können, wurde das Auto-Play Feature der Kapitelmarken in der Kapitelmarkenliste deaktiviert. Das Abspielen läuft nun einfach weiter, egal wie man die Kapitelmarken bearbeitet. Um wie bisher schnell zu einer Kapitelmarke in der Timeline zu springen, klickt man doppelt rechts neben der Marke im freien Bereich der Liste. Die Marken sind nun zur besseren Orientierung durchnummeriert, die Nummern landen nicht in den Texten._

      	[Video: Edit Markers](http://ultraschall.fm/wp-content/uploads/2018/01/Edit_markers.gif)

- Soundboard: **Sortierung unter macOS High Sierra**
  _Die Sortierung der einzelnen Sounds erfolgt nun auch unter macOS High Sierra wieder alphabetisch nach Dateinamen. Es wird nur noch der jeweils angegebene Ordner ausgelesen und in das Soundboard importiert, nicht wie bisher auch sämtliche Unterordner._

- Sonstiges: **Tastatur-Shortcuts überarbeitet**
  _Die Übersicht für alle relevanten [Tastatur-Shortcuts](http://url.ultraschall-podcast.de/keymap31) in Ultraschall wurde aktualisiert und erweitert._

- Easter Egg: **Wenns mal wieder länger dauert**
  _Ostern kommt plötzlich und unerwartet. Mit dem Shortcut `alt`+`cmd`+`shift`+`u` kann man sich die Wartezeit etwas verkürzen._

- Sonstiges: **Bugfixes und Optimierungen**
  _Diverse kleinere Optimierungen, insbesondere von Sonderfällen. Zuviele Details würden Sie nur beunruhigen._

## 3.0.3 Miedinger - 2017-April-6

- REAPER: **Festlegung auf eine exakte Versionsnummer**
  _Um die Konsistenz und Stabilität des Systems zu gewährleisten, wird bei jedem Start nun auf eine spezifische Version von REAPER geprüft (5.70). Zukünftige Releases werden dann jeweils mit neuen Versionen gekoppelt sein._ **Von einem manuellen Update von REAPER ist daher in Zukunft unbedingt abzusehen**, _die Ultraschall-Erweiterungen werden dann deaktiviert._

- Actions: **Überarbeitete Routing Snapshots**
  _Um während einer Live-Sendung - etwa mit Hilfe von Studio Link OnAir - verschiedene Routing-Situationen vorbereiten und abrufen zu können (etwa Preshow mit nur Musik auf dem Stream, Show mit allen Stimmen und Aftershow mit leisem Musikbett), wurde der Bereich der Routing-Snapshots komplett neu implementiert und mit einer eigenen Verwaltungsoberfläche versehen. Die Snapshots berücksichtigen nun auch Sends in Richtung Master sowie Hardware-Sends._

- Keymap: **Shortcuts für Routing-Snapshots**
  _Mit `F1` bis `F4` werden gesetzte Routing Snapshots abgerufen. Mit `shift` + `F1` bis `F4` wird die gerade eingestellte Routing-Matrix in den jeweiligen Snapshot-Slot geschrieben._

- Keymap Mac: **Anpassungen an Systemstandard**
  _Unter macOS wurden folgende Aktionen für Shortcuts an den Systemstandard angepasst: Drag&Copy von Items erfolgt nun über `alt` + `gedrückter Primärklick`. Der aktuelle Projekt-Tab wird mit `cmd` + `w` geschlossen._

- Streaming: **Update für Studio Link OnAir**
  _Eine neue Version von Studio Link OnAir wird ausgeliefert, die ein seltenes Stabilitätsproblem unter Windows behebt._

- Editing: **Weiter verbessertes Verhalten der `esc`-Taste**
  _Die "lösche jegliche Auswahl"-Funktion beinhaltet nun auch nicht-selektierte Envelope-Points. Erstaunlich._

- Editing: **Midi Actions für EQ-Regler**
  _Zwei neue Ultraschall-Midi Aktionen ermöglichen das leichte Verschieben des Inpoint und Outpoint über einen klassischen EQ-Regler auf einem Midi-Interface: In der Mittelstellung passiert nichts, ein Drehen nach Links oder Rechts bewirkt eine beschleunigte Bewegung in die jeweilige Richtung. Je weiter der Einschlag, desto schneller bewegt sich der In-/Outpoint. Die Skripte (`ultraschall_midi_move_start_of_time_slection.lua` und `ultraschall_midi_move_end_of_time_slection.lua`) müssen manuell einem Midi-Signal zugeordnet werden._

- Installer: **Update Check**
  _Der Update Check auf neue Versionen von Ultraschall kann nun jederzeit im neuen Startscreen ab- oder angeschaltet werden._

- Theme: **Ultraschall-Startscreen erweitert**
  _Der neue Startscreen enthält nun auch die Informationen des alten `About Ultraschall...` Menüeintrages, der somit entfällt. Die Versionsnummern aller installierten Komponenten sind nun im Startscreen unter dem `Details`-Button erreichbar._

- Soundboard: **Bugfix**
  _Das Soundboard stoppt nun nicht mehr die Wiedergabe, sobald ein Routing-Preset abgerufen wird._

- Soundboard: **Presets**
  _Das Soundboard funktioniert nun durchgängig mit Presets. Dadurch ist es möglich, beliebige Sound-Sets zu speichern und zu laden, auch während einer Aufnahme. Duch den fliegenden Wechsel von Presets während einer Aufnahme ist es nun auch leicht möglich, mehr als 24 Sounds in einer Sendung zu verwenden. Man kann die Presets den eigenen Projekt-Presets zuweisen, damit jede Sendung gleich mit den richtigen Einspielern geladen wird._

## 3.0.2 Miedinger - 2017-März-06

- Editing: **Shortcuts für In- und Outpoint**
  _Mit den Tasten `alt` + `i` sowie `alt` + `o` springt man zum Anfang bzw. Ende einer Zeitauswahl. Mit `shift` + `i` sowie `shift` + `o` wird ab der jeweiligen Position abgespielt._

- Editing: **Verbesserter Ripple-Cut**
  _Die neue Ripple-Cut Funktion (`cmd` + `x` sowie das entsprechende Icon) verhalten sich nun sinnvoller: ist nichts ausgewählt, passiert nichts. Ist eine Zeitauswahl markiert, wird nur diese geschnitten, unabhängig von eventuell zugleich ausgewählten Items. Ist keine Zeitauswahl markiert, aber genau ein Item, so wird anhand dessen Rändern ein Ripple-Cut vorgenommen (Tim's Ripple Cut). Ist keine Zeitauswahl markiert, sowie mehrere Items, passiert nichts._

- Editing: **Schneller Wechsel und Einfrieren der Trackhöhe**
  _Mit der Taste `h` schaltet man schnell zwischen zwei (einstellbaren) Trackhöhen hin und her, die dann ihre Höhe auch bei Verschieben der Fenster untereinander behalten. Das Umschalten wirkt auf alle markierten Spuren. Ist keine Spur markiert, werden alle Spuren verändert. Das Einfrieren der Höhe kann mit den Zoom-Schaltern wieder aufgehoben werden._

- Keymap: **Optimierung der Tastatur-Shortcuts und Mapping für Windows**
  _Die Belegung von Shortcuts von Windows wurde dem Verhalen auf macOS angepasst. Die PDF-Schablone funktioniert nun auf beiden Systemen gleich. Neue Shortcuts sind etwa: `shift` + `n` - Normalisierung ausgewählter Items sowie `alt` + `d` - ausschalten aller Docks für ablenkungsfreies Editieren._

- Theme: **FX Buttons im Master-Kanal**
  _Die Buttons zum Einstellen von FX sind nun auch im Master-Kanal in jeder Größe sichtbar._

- Actions: **Erweitertes Prepare all tracks for editing**
  _Die Funktion beinhaltet nun das Einschalten der Sends aller Spuren richtung Masterkanal - eine gängige Fehlerquelle für scheinbar fehlende Spuren im finalen Mix._

- Mastering: **Erweiterte Episodenbilder**
  _Im Projektordner sind für den MP3-Export nun auch Episodenbilder mit dem Namen `cover.jpg`, `cover.jpeg` sowie `cover.png` zugelassen um schnell ein Standardbild nachnutzen zu können. Danke an Mespotine für die Idee._

## 3.0.1 Miedinger - 2017-März-05

- Streaming: **Studio Link OnAir Streaming**
  _Durch die Unterstützung von Studio Link OnAir (Version 17.02.0.) kann mit einem Knopfdruck ein Live-Streaming der Sendung gestartet werden. Gestreamt wird immer das im Mastermix anliegende Signal, über ein sich öffnendes Web-Interface können Anpassungen der Streaming-Metadaten vorgenommen sowie die Streaming-URL publiziert werden._

- Installer: **Update Check**
  _Beim Starten von Ultraschall wird geprüft, ob eine neue Version vorliegt. Eine Validitäts-Check stellt sicher, dass zueinander passende Versionen von Plugin und Theme installiert sind und gibt gegebenenfalls Warnmeldungen._

- Installer: **LAME MP3 Encoder**
  _Der LAME MP3 Encoder wird in Version 3.98.3 automatisch installiert._

- Studio Link: **Update**
  _Ultraschall wird mit aktualisiertem StudioLink Plug-in in Version 16.12.0. ausgeliefert._

- Theme: **Ultraschall-Startscreen**
  _Ein neuer Startscreen informiert über die erfolgreiche Installation und gibt erste Hinweise sowie Links zu Hilfe-Ressourcen._

- Theme: **Anpassungen der Views**
  _Die Views-Umschalter oben links zeigen nun auch nach einem Reaper-Neustart den aktuellen Modus an (Stichwort: Persistenz-Schicht). Im Edit-View wird ganz oben jetzt das Navigator-Fenster über die gesamte Breite angezeigt.
  Zusätzlich gibt es unten links nun einen neuen Reiter für `Loudness`, mit dem sich die Lautstärke von Spuren oder einzelnen Items in LUFS messen lässt (siehe: Ultraschall-Dynamics)._

- Theme: **FX immer sichtbar im Mixerbereich**
  _Durch die stetig wachsende Bedeutung der Effekte (StudioLink, OnAir, Soundboard, Dynamics) sind nun die FX-Buttons im Mixerbereich der Spuren immer sichtbar, auch bei sehr verkleinertem Fenster._

- Theme: **Wellenform**
  _Ausgewählte Items werden in der Helligkeit klarer hervorgehoben. Schnitte innerhalb einer Wellenform werden deutlicher angezeigt._

- Theme: **User Interface**
  _Viele GUI-Elemente erhalten mehr Kontrast für bessere Sichtbarkeit._

- Theme: **Auswahlwerkzeug**
  _Mit einem neuen Icon-Schalter kann zwischen zwei Editier-Modi gewechselt werden: dem bisherigenen Modus, der einzelne Elemente auf der Timeline markiert und verschiebt, sowie einem neuen Auswahl-Modus ("TSB-Button"), der das Erstellen von Zeitauswahlen für schnellen Schnitt (Ripple-Cut) erheblich vereinfacht. Eine Zeitauswahl kann damit überall in der Timeline gesetzt werden, nicht mehr nur wie bisher am oberen Rand. Das Umschalten der Modi erfolgt entweder über das neue Icon oder über den Tastatur-Shortcut: `#`._

- Theme: **Hervorhebung 'Prepare all tracks for editing'**
  _Die nach jeder Aufnahme und vor dem Schnitt aufzurufende Menü-Aktion 'Prepare all tracks for editing' wird optisch hervorgehoben um die Sichtbarkeit zu erhöhen. Die Funktion selbst wurde neu implementiert und erweitert. Nach erfolgreichem Durchlauf wird ein neues Status-Fenster angezeigt._

- Theme: **Podcast-Menü**
  _Diverse Einträge im Podcast-Menü wurden aktualisiert und klarer angeordnet._

- Editing: **Volume-Editing**
  _Über das Menü oder den Shortcut `alt`+`v` kann für ausgewählte Spuren ein Lautstärke-Envelope (PRE-FX!) angezeigt werden. Mit diesem können komplexere Fadings oder Lautstärke-Verläufe realisiert werden. Ferner gibt es einen PRE-FX Gainregler links im Spurbereich, mit dem sich die Gesamtlautstärke einer Spur - mit visueller Rückmeldung durch die Wellenform - anpassen lässt. Die Sichtbarkeit der Spuren wird über das aus der Mute-Spur bekannte Icon oben umgeschaltet._

- Editing: **Einfacheres Envelope-Handling**
  _Der Modus, mit dem man in Envelopes (Mute oder Volume) Punkt setzen oder verschieben kann, ist überarbeitet worden. Man klickt nun einfach an die Stelle, an der der nächste Punkt gesetzt werden soll, bzw. verschiebt bestehende Punkte. Ein Mute-Bereich ist so mittels zweier Klicks einstellbar. Der alte Freihand-Malmodus kann jederzeit durch gedrückt halten der `cmd` Taste zurückgeholt werden._

- Editing: **Verbessertes Verhalten der `esc`-Taste**
  _Wir glauben an die Zukunft und die Notwendigkeit der `esc`-Taste. Daher haben wir die "lösche jegliche Auswahl"-Funktion erheblich erweitert - sie hebt nun Track-, Item-, Envelope- und Zeitmarkierungen auf._

- Editing: **Vorhören von Schnitten**
  _Mit dem Shortcut `p` kann man vorhören, wie sich ein Schnitt mittels Zeitmarkierung auswirken würde, ohne dass man diesen bereits durchführen muss. In Kombination mit den neuen Shortcuts zum Verschieben der In- und Outpoints einer Zeitauswahl `<`, `y`, `x` und `c` ist dadurch ein sehr effizienter und kontrollierter Schnitt möglich._

- Editing: **Play-Cursor auf Anfang von Zeitauswahlen**
  _Setzt man eine Zeitauswahl, so wird der Play-Cursor direkt auf den Inpoint dieser Auswahl gesetzt und man kann direkt mit `return` oder `space` die Auswahl anhören._

- Editing: **Erweiterter Ripple-Cut**
  _Mit dem Shortcut `cmd`+`x` wird ein Ripple-Cut über alle Spuren auch dann durchgeführt, wenn nur ein einzelnes Item ausgewählt wird. Schnittbereich ist dann Start- und Endpunkt dieses Items._

- Keymap: **Neues Layout für Tastatur-Shortcuts**
  _Eine Vielzahl an Shortcuts wurden überarbeitet und neu hinzugefügt um einen effizienteren Schnitt über die Tastatur zu ermöglichen. In einem [.PDF](http://url.ultraschall-podcast.de/keymap) sind die neuen Shortcuts ausgewiesen, eigene Anpassungen können in einer mitgelieferten PowerPoint-Datei vorgenommen werden._

- Mastering: **Ultraschall Dynamics**
  _Mit dem neuen Dynamics Effekt kann die Lautheit des Podcasts auf ca. -16 LUFS optimiert werden. Der Effekt ersetzt den bisher empfohlenen AU General Dynamic Effekt und ist auch unter Windows einsetzbar. Es werden Presets mitgeliefert mit und ohne weichem Noisegate zur Reduzierung leiser Störungen. Der Effekt kann sowohl auf Einzelspuren, einzelnen Items, als auch auf dem Master-Kanal eingesetzt und parametrisiert werden. Achtung: der Effekt ist weniger geeignet zur Reparatur von problematischem Material (Brummen, Hall etc.) - hier wird dringend nach wie vor der Einsatz von Auphonic empfohlen._

- Mastering: **Effektvorgaben bei neuen Spuren**
  _Beim Anlegen neuer Spuren werden automatisch die Effekte ReaEQ (Equalizer) und JS: General Dynamics hinzugefügt, jedoch noch nicht aktiviert._

- Mastering: **Neues EQ-Preset**
  _Ein neues Ultraschall 3 Preset für den EQ wird mitgeliefert. Es bietet weniger Bassanhebung als der Preset der 2er Version und ist ein guter Startpunkt für die Headsets [DT297](https://www.thomann.de/de/beyerdynamic_dt297pv80_mk_ii.htm?partner_id=60110) und [HMC660](https://sendegate.de/t/profi-klang-fuer-alle-das-hmc660-headset-richtig-einsetzen-fuer-unter-100/3076?u=rstockm) ist._

- Mastering: **Export Assistent**
  _Ein neuer Export-Assistent, links unten in der `Export` Iconleiste zu finden, hilft dabei, perfekte MP3-Dateien zu erzeugen. Die ID3V2 Elemente Metadaten (wie Titel, Podcast etc.), Episodenbild und Kapitelmarken werden in die produzierte MP3-Datei gespeichert._

- Mastering: **Rauschfilter verfügbar**
  _Zum Beheben gängiger Soundprobleme wie Rauschen oder Netzbrummen wurde der ReaFir-Effekt in die Effekt-Favoriten mit aufgenommen. Die Bedienung wird im [Video zu Ultraschall Dynamics](http://ultraschall.fm/tutorials/) erläutert._

- Mastering: **Bugfix: Projektordner öffnen**
  _Menübefehl und Icon für das Öffnen des Projektverzeichnisses öffnen nun wirklich das Projektverzeichnis - nicht wie bisher den Unterordner mit den Sounddateien._

- Actions: **Colorpicker**
  _Der neue nutzerfreundlicher Colorpicker (Shortcut: `alt`+`c`) hilft, Übersicht in komplexen Projekten zu erhalten: Spuren oder einzelnen Clips können Farben zugewiesen werden, mehrere Spuren über eine Auswahl auch Farbverläufe - entweder fließend, oder unter Nutzung eines sinnvollen Kontrast-Bereichs._

- Actions: **Import von Kapitelmarken aus WAV-Dateien**
  _Einige Aufnahmegeräte (z.B. Zoom H5 und H6) bieten die Möglichkeit, während der Aufnahme Kapitelmarken in die .WAV Datei zu schreiben. Mit dieser neuen Kapitelmarken-Aktion können sie ausgelesen und in Ultraschall-Kapitelmarken umgewandelt werden._

- Actions [Windows]: **Bugfix für Umlaute**
  _Es wurde ein Fehler behoben im Umgang mit Kapitelmarken, die Umlaute enthalten. Danke an @jalea and Nico Buch für das Aufspüren dieses Fehlers._

- Soundboard: **Bugfix**
  _Mit OSC kann das Abspielen von Sounds nicht angehalten werden. Danke an Bastian Boessl für den Bugreport._

## 2.2.2 Gropius - 2016-August-14

- Soundboard [Mac]: **Bugfix**
  _Bugfix: Aufgenommene Soundboard-Spuren werden jetzt abgespielt._

- Misc [Windows]: **Kompatibilität**
  _Updates für Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

- StudioLink: **Update**
  _Ultraschall enthält jetzt die neue StudioLink-Version 16.04.1._

## 2.2.2 Gropius - 2016-August-14

- Soundboard [Mac]: **Bugfix**
  _Bugfix: Aufgenommene Soundbooard-Spuren werdem jetzt abgespielt._

- Misc [Windows]: **Kompatibilität**
  _Updates für Windows 10 Version 1607 (Build 14393, Anniversary-Update)._

- StudioLink: **Update**
  _Ultraschall enthält jetzt die neue StudioLink-Version 16.04.1._

## 2.2.1 Gropius - 2016-June-09

- Installer: **Bugfix**
  _Bugfix: Löschen von alten Dateien schlägt fehl. Danke an Marcus Schwarz für den Bugreport._

- Installer: **Bugfix**
  _Bugfix: Löschen von anderen alten Dateien schlägt fehl. Danke an Wolfgang Schulz für den Bugreport._

## 2.2 Gropius - 2016-Jun-05

- Theme: **Weiteres Feintuning des neuen Themes**
  _Die Scrollbalken sowie Zoom-Icons wurden vereinfacht, ebenso Schieberegler in AU/VST-Effekten._

- Actions: **Räuspertaste und Mute-Spur**
  _Komplette Neukonzeption der Räuspertasten- und Mute-Funktion. Der editierbare Mute-Envelope wird nun immer in einer Separaten Spur angezeigt und farblich besser hervorgehoben. Der Mute-Button in der Iconleiste funktioniert nun kontexabhängig: vor einer Aufnahme können ausgewählte Spuren für die Räuspertaste aktiviert werden. Während und nach der Aufnahme schaltet er die Sichtbarkeit der Mute-Spuren ein oder aus._

- Actions: **Auswahl von Spuren über Tastatur**
  _Über die Zahlentasten 1 bis 8 können die jeweiligen Spuren markiert oder unmarkiert werden. 9 markiert sämtliche Spuren, 0 hebt die Markierung sämtlicher Spuren auf._

- Actions: **Alle Spuren für Schnitt vorbereiten**
  _Die Befehlsfolge "Prepare all tracks for editing", die nach jeder Aufnahme aufgerufen werden sollte, wurde verbessert und stellt weitere Parameter für den Schnitt um._

- Actions: **Neuer Menü-Eintrag "Customize"**
  _Im Podcast-Menü sind unter dem neuen Eintrag "Customize" folgende Funktionen zusammengefasst: 'Shortcuts and action list' um Tastaturkürzel neu definieren zu können und neue Funktionen hinzuzufügen, 'Track: set track icon' um Spuren mit einem Symbol verzieren zu können, 'Show theme configuration window' um Farben des Theme anzupassen, 'Show theme element finder' um die Benamung von einzelnen Elementen der GUI zu finden sowie 'Auto color' um die Standardfarben von Spuren in Abhängigkeit ihres Namens festzulegen. Weitere Hinweise über die Anpassbarkeit von Ultraschall/Reaper zeigt dieser Vortrag: <FIXME: Link fehlt>_

- StudioLink: **Vollständige Integration des StudioLink Plugins**
  _Als qualitativ in Bezug auf Stabilität, Konstanz und Klangqualität weit überlegene Alternative zu Skype unterstützt Ultraschall nun StudioLink. Ohne den Aufbau einer N-1 Schaltung über die Routingmatrix ist es damit möglich, Ferngespräche mit bis zu 8 PartnerInnen zu führen, die in jeweils separaten(!) Spuren aufgezeichnet werden. Die PartnerInnen können dabei die schlanke Standalone-Version von StudioLink nutzen und benötigen keine eigene DAW. Die Einrichtung einer StudioLink-Schaltung wird im Release-Video erläutert._

- Soundboard: **Soundboard nun auch für Windows und als AU Version für den Mac**
  _Das Ultraschall-Soundboard steht nun mit vollem Funktionsumfang auch unter Windows zur Verfügung. Bei der Mac-Version wurde von VST auf AU Technik umgestellt._

- Installer: **StudioLink Plugin und standalone**
  _Ultraschall liefert im Installer die Version des StudioLink-Plugins aus. Externe GesprächspartnerInnen können sich die [Standalone-Fassung von StudioLink](https://doku.Studio Link.de/standalone/installation-standalone.html) laden._

- Preferences: **Stop Funktion überarbeitet**
  _Die Stop-Funktion bei Aufnahmen wurde so überarbeitet, dass der Aufnahme-Cursor nach Stop an das Ende der bisherigen Aufnahme gesetzt wird. Dies verhindert, dass bei einem erneuten Start der Aufnahme kein alternativer Take angelegt wird, sondern die eigentliche Aufnahme fortgesetzt wird._

- Preferences: **Neue Spuren werden direkt für die Aufnahme aktiviert**
  _Alle neu angelegten Spuren werden direkt auf "Record Arm" geschaltet und sind bereit für die Aufnahme - der zusätzliche Klick auf den roten Arm-Knopf kann damit oft entfallen._

- Misc: **Ultraschall 3 Preset für ReaEQ**
  _Standardmäßig wird bei Aktivierung des ReaEQ Equalizers das Preset Ultraschall 3 aktiviert, dass deutlich weniger Bassanhebung und damit Poltern mit sich bringt._

- Misc: **Ultraschall Presets für gebaute Beiträge**
  _Folgende Effekte werden als Ultraschall-Presets für die Verfremdung von Stimmen für gebaute Beiträge angeboten: Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate)_

- Installer: **Bugfix**
  _Fehlerhafte Code-Signatur in Uninstall.command. Vielen Dank an Arnd Layer für den Bugreport._

## 2.1.1 Gropius - 2016-Feb-27

- Theme: **Weiteres Feintuning des neuen Themes**
- Windows: **Anpassung der Farbwerte für die Audiospuren**
  _Auch unter Windows stimmen nun die Zuordnungen von Bezeichnungen und Farbwerte_

## 2.1 Gropius - 2016-Feb-19

- Theme: **Umfangreiches Feintuning des neuen Themes**
  _Der Kontrast von nahezu allen Elementen wurde hoch gesetzt, um die Bedienbarkeit auch in ungünstigen Lichtsituationen zu verbessern. Gruppen von Icons werden optisch zusammengefasst. Einzelne Icons wurden neu gezeichnet um die Funktion klarer werden zu lassen. Die Anmutung aller Buttons wurde vereinheitlicht. Feintuning vieler Farbwerte, um sie der Ultraschall Farbpalette anzupassen. Die Farbpalette ist nun logisch entlang des Regenbogens angeordnet. Schnitte innerhalb eines Items sind durch abgerundete Kanten und eine feine Linie jetzt deutlicher zu erkennen._

- Preferences: **Snap Funktionen (Magnetisches Andocken)**
  _Alle Elemente wie Items, Marker und Regions unterstützen nun das magnetische Andocken, was komplexere Editings vereinfacht._

- Theme: **Routing Matrix enthält Anzeige über Eingangszuordnungen**
  _Im unteren Bereich der Routing-Matrix können nun die Zuordnungen der Input-Kanäle zu den Spuren vorgenommen werden. Somit können nun wirklch alle relevanten Zuordnungen übersichtlich an einer einzigen Stelle erfolgen._

- Misc: **SWS/S&M Extension 2.8.3**
  _Ultraschall wird nun mit der [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/) ausgeliefert_

- Actions: **Neue Shortcuts für flüssiges Editing mit der Tastatur**
  _Mit den Tasten `i` und `o` können Anfang und Ende einer Zeitselektion gesetzt werden - analog zu vielen Videoschnittprogrammen. Mit den Tasten `1` und `2` können Anfang und Ende der Selektion angesprungen werden. Die Tastaturzuordnungen für das Springen zwischen Kapitelmarken wurde geändert, um nicht Kollisionen beim wortweisen Springen in Textabschnitten zu provozieren._

- Actions: **Start/Stop/Pause-Safemode für die Tastatur**
  _Um das unbeabsichtigte Beenden einer laufenden Aufnahme zu verhindern, werden die Tasten `RETURN` und `SPACE` während einer Aufnahme abgefangen. Es erscheint ein Dialog, ob die Aufnahme wirklich gestoppt werden soll._

- Actions: **Robustheit der Kapitelmarken-Funktionen**
  _Sämtliche Kapitelmarkenfunktionen wurden neu in Lua implementiert und interpretieren nun, ob a) eine Aufnahme läuft oder b) eine Aufnahme abgespielt wird oder c) keine Aktion stattfindet. Im Falle von a werden die Marken an die aktuelle Aufnahmeposition gesetzt, bei b) an die aktuelle Abspielposition und bei c) an die aktuelle Position des Edit-Cursors. Die Midi-Ansteuerung wurde so robust gestaltet, dass Kapitelmarken über Midi in jedem Zustand des Programmes gesetzt werden können - selbst während bestehende Marken editiert werden._

- Actions: **Benamung der Ultraschall-Actions**
  _Im über die Taste `?` zu erreichenden Actions-Dialog - in dem sich auch Tastatur-Zuordnungen editieren lassen - sind nun alle Ultraschall-Funktionen einheitlich mit dem Präfix `ULTRASCHALL:` benamst und verständlicher formuliert._

- Soundboard [Nur Mac]: **Bugfix**
  _REAPER stürzt nicht mehr ab, wenn der ins Soundboard zu importierende Ordner nur eine Datei enthält. Vielen Dank an Sven Wiegand für den Bugreport._

- Soundboard: **Bugfix**
  _REAPER stürzt nicht mehr ab, wenn eine der zu importierenden Sounddateien nicht decodiert werden kann. Danke an René Kurfürst für den Bugreport._

## 2.0 Gropius - 2015-Dec-09

- Misc: **Reaper 5 und OS X 10.11 El Capitan**
  _Die Ultraschall ist nun für Reaper 5 und OSX 10.11 El Capitan optimiert. Ältere Versionen werden nicht weiter untertützt._

- Installer [Nur Mac]: **User- statt Systemverzeichnis**
  _Der neue Installer schreibt seine Einträge in das User-Verzeichnis von OSX, nicht mehr nach System._

- Theme: **Komplettes Redesign des Theme**
  _Mehr Konsistenz, weniger Unordnung. Alle Icons und Funktionsbereiche wurden überarbeitet, Farben vereinheitlicht._

- Theme: **Responsiver Mixer**
  _In Abhängigkeit der Dock-Höhe blendet der neue Mixerbereich Bediehnelemente ein und aus._

- Theme: **Neue Ansicht: das Storyboard für gebaute Beiträge.**
  _Beliebige Bereiche einer Aufnahme - etwa einzelne Antworten - können mit Schlagworten versehen werden, nach denen - auch projektübergreifend - gesucht und gefiltert werden kann. Verwaltung beliebig vieler Clip-Datenbanken. Farben und Kommentare, um in komplexen Projekten den Überblick zu behalten. Gruppierungsfunktion für fertige Abschnitte und Regionen, um sie zusammen zu halten. Text-Elemente können frei im Schnittbereich verteilt werden, etwa um Shownotes oder Kommentare zu verwalten._

- Actions [Nur Mac]: **About Screen**
  _Neue Funktion: über einen About-Screen können die derzeit installierten Komponenten mit ihren Versionsnummern angezeigt werden_

- Theme: **Translation**
  _Die Menüs wurden ins Englische übersetzt._

- HUB [Nur Mac]: **Neuer Audiotreiber**
  _Soundflower gehört der Vergangenheit an: entlang der neuen CoreAudio APIs von OSX 10.11 El Capitan wurde die Audio-Engine für virtuelle Soundkomponenten von Grund auf neu geschrieben._

## Release 1.3 - 2015-Jul-05

- WICHTIG: **Bis auf weiteres ist diese Release nur unter Reaper 4.78 lauffähig.**
  _Wir arbeiten an einer Unterstützung der Reaper 5.0 Version, informiert Euch hierzu im <https://sendegate.de/c/ultraschall>._

- Installer: **Der Installer hat ein geschmackvolleres Hintergrundbild bekommen.**
  _Die aktuelle stable Version der SWS Extension (2.7) wird installiert._

- Theme: **Überarbeitung des Podcast-Menüs**
  _Viele Begrifflichkeiten wurden klarer gefasst und vereinheitlicht. Track Templates (Einspieler, Audio-Track) werden direkt im Menü angezeigt._

- Theme: **Größe der Fenster**
  _Die Default-Fenstergröße von Reaper wurde an ein 13" MBP Retina mit Standard-Auflösung optimiert._

- Actions: **Letzte Kapitelmarke löschen**
  _Neue Funktion im Podcast-Menü und als Shortcut: die erste, sich links vom Edit-Cursor (rote Linie) befindliche Kapitelmarke wird gelöscht. In 99% der Fälle ist dies die zuletzt gesetzte._

- Actions: **Setze eine Kapitelmarke 2 Minuten in die Vergangenheit**
  _Eine blaue Kapitelmarke mit der Bezeichnung "\_Past" wird zwei Minuten VOR der derzeitigen Position des Edit-Markers gesetzt. Die hilft beim Markeiren einer Stelle in der Art von "eigentlich sind wir schon längst beim nächsten Thema". Durch die Farbe und den Bezeichner kann die Marke im Schnitt schnell gefunden und an die exakte Position geschoben werden._

- Actions: **Kapitelmarken schreiben und lesen**
  _Das Handling zum Export und Import der Kapitelmarken wurde überarbeitet. Kapitelmarken werden nun im Stil projektname.chapters.txt gespeichert._

- Actions: **Textelement einfügen**
  _In eine leere Spur kann nun an der Position des Cursors ein Text-Element eingefügt werden, das man mit Klick auf die Sprechblase mit beliebigem Text versehen kann der sich dann wie ein Audio-Element verhält. Diese wenn man eine Folge eher "baut", also aus vielen Sequenzen zusammensetzt bei denen etwa die klassischen Kapitelmarken zu unflexibel sind._

- Presets: **Ein neues Einspieler-Track Preset wird mitgeliefert, bei dem bereits ein Ducking voreingestellt ist.**
  _Über die Routing-Matrix werden die Kanäle ausgewählt die das Ducking aktivieren. Die genaue Bediehnung wird im Release-Screencast demonstriert._

- Preferences: **Die Samplerate wird auf 48KHz gesetzt, die Buffer-Size auf 512. "Ignore running Change Notifications" wird gesetzt.**
  _Bis zur Releasde unseres eigenen Audio-Treibers scheint dies unter OSX die am stabilsten funktionierenden Werte zu sein um Knaksen zu verhindern._

- Soundboard: **Neuer Grid-View**
  _Die Ansicht des Soundboard lässt sich umschalten zwischen der bekannten Tabellenansicht und einer Grid-Ansicht_

- Soundboard: **Ein- Ausfaden**
  _Das Ein- und Ausfaden wird nun in sämtlichen Play-Modi unterstützt - etwa einfaden aus Pause etc._

- Soundboard: **Ducking**
  _Es gibt einen neuen Ducking-Schalter der sämtliche gerade laufenden Einspieler sanft auf eine zu definierende, geringere Lautstärke runterregelt über die man gut drübersprechen kann. Ein Ausschalten bewirkt wieder eine Anhebung der Einspieler. Die stärke des Ducking lässt sich in den Soundboard-Settings einstellen._

- Soundboard: **Master-Volume**
  _Die Gesamtlautstärke des Einspieler-Outputs kann über einen Schieberegler eingestellt werden_

- Soundboard: **Themes**
  _Man kann verschiedene Farbsets für das Soundboard einstellen_

- Soundboard: **Live-Mode**
  _Hat man alle Einstellungen im Soundboard wie Lautstärken einmal eingestellt, kann man diese nun für die Sendung in einen "Lock" Modus versetzen: egal welche Presets verwendet werden, die Soundboard Einstellungen bleiben unberührt._

- Misc: **Bugfixes in den Plugins**
  _Einige garstige Speicherlecks wurden in unseren Reaper-Plugins geschlossen. Damit sich diese jeh auswirken hätte man aber einige Tage aufnehmen müssen._

- HUB [Nur Mac]: **Die virtuellen Sound-Devices werden umbenannt, um die Zuordnung in SKYPE intuitiver zu gestalten.**
  _Stereo-Geräte werden vor Mono-Geräte gesetzt um Verschiebungen in der Routing-Matrix vorzubeugen._

## Release 1.2 - 2015-Jan-04

- Installer: **Unter Mac OSX können weite Teile der Distribution nun über einen einfachen Installer abgewickelt werden**
  _Soundflower Ultraschall-Edition, Startlogo, SWS-Extensions sowie das Ultraschall-Soundboard werden installiert. Manuell muss nur noch einmalig die Theme -Datei in Reaper gezogen werden._

- Theme: **Neuer Eintrag im Podcast-Menü: Navigation/Springe zu Play-Cursor (#-Taste)**
  _springt zur aktuellen Position des Play-Cursors (Orange)_

- Theme: **Neuer Eintrag im Podcast-Menü: Soundboard Spur anlegen \*Legt eine Spur an, in der bereits alle Einstellungen für das Ultraschall Soundboard gesetzt sind.**
  _Im sich öffnenden Auswahlfenster muss man einmalig "Soundboard.RTrackTemplate" anwählen. Zur Funktionalität des Soundboard s.U._

- Theme: **Neues Untermenü im Podcast-Menü: Selection**
  \*bieter verschiedene nützliche Aktionen um den Schnitt mittels Selections zu beschleunigen - insbesondere Ripple-Delete zum schnellen Löschen von ganzen Passagen über alle Spuren\*\*

- Theme: **Einheitliche Symbole für Chapters(Dreieck/Strick)**
  _Neue Icons für setze Kapitelmarke, Export Chapters und Audiodatei Schreiben_

- Theme: **Mute- und Solo-Buttons**
  _In der Spuranzeige links sind nun immer die jeweiligen Mute- und Solo-Buttons sichtbar._

- Actions: **Neue Menüpunkte und Kontext-Links für den Umgang**
  _mit der Mute-Spur (Räuspertasten). Separate Mute-Spur für ausgewählten Track an/Ausschalten, Sichtbarkeit aller Mute-Spuren an/ausschalten. In der separaten Mute-Spur kann direkt mit dem Mauscursor und der linken Maustaste ein Mute-Bereich gemalt werden_

- Actions: **Verbessertes Audiodatei schreiben**
  _Der Menüpunkt "Audiodatei Schreiben" und das entsprechende Icon links unten im Edit-View setzen zunächst die Playrate des Projektes auf 1.0 um dann das Render-Menü zu starten. Ferner werden zuvor sämtliche Spuren ausgewählt, so dass man direkt einen Multifrack Export für Auphonic (Stems Export) starten kann._

- Misc: **Das Ultraschall-Soundboard feiert seinen Einstand und ist als VST-Effekt-Plugin realisiert.**
  _Für die genaue Bedienung bitte den Release-Screencast schauen. Funktionen: Verwalten von verschiedenen Sets, Play, Pause, Stop, Loop, Fade, einstellbare Fade-Zeit, regelbare Lautstärke pro Einspieler, direkte OSC-Kopplung. Zur OSC-Steuerung - etwas über ein iOS Gerät oder die Wiimotes - kommt in Kürze ein weiterer Screencast_

- Presets: **Ultraschall-Presets für Expander und EQ**
  _als Ergebnis eine kleinen Workshops mit Michael Kummeth gibt es im EQ das "Ultraschall2" Preset, das einen sehr guten Ausgangspunkt für moderate EQ-Einstellungen bietet._

- Presets: **optimiertes Datei-Handling**
  _Alle Dateien einer Podcast-Folge (Projektdatei, Aufnahmedateien, Peak-Dateien, Kapitelmarken-Datei) werden übersichtlich im Projektordner und mit sinnvollen Unterordnern abgelegt. Details sind dem Screencast zu entnehmen._

- Presets: **Sinnvolle Presets zur Dateibenamung von Aufnahmen eingestellt**
  _(Tracknummer-Trackname-Folgenname)_

- Misc: **Für die Verlinkung des Projektes auf der eigenen Podcast-Seite**
  _werden zwei unauffällige Badges mitgeliefert._

- Misc: **Für Probleme, Anregungen etc.**
  _wurde auf sendegate.de ein Support-Forum eingerichtet das den bisherigen Patter-Raum ersetzt: <https://sendegate.de/c/ultraschall>_

## Release 1.1 - 2014-Jun-09

- Theme: **Es gibt ein neues Menü "Podcast" in dem nach Workflowschritten unterteilt sämtliche Podcast-Funktionen gesammelt sind.**
  _Die Funktionen gliedern sich nach den drei Workflow-Schritten "Setup, Aufnahme und Produktion" und sind auch innerhalb der Gruppen so angeordnet, dass man sie von oben nach unten durchgehen kann. Jede neue Aufnahme durchläuft somit die Einträge (oder zumindest Teile davon) des Menüs von oben nach unten. Die Details sind dem 1.1 Release-Screencast zu entnehmen_

- Actions: **Import von mp4chaps Kapitelmarken (etwa: Shownotes Export) als Marker**

- Actions: **Export von Kapitelmarken als mp4chaps für Podlove und Auphonic**

- Actions: **Mit "E" oder dem neuen Icon werden rote Edit-Marken gesetzt**

- Theme: **im Edit-View ist ein neues Icon verfügbar, das den aktuellen Projekt-Ordner öffnet.**
  _Der Aufnahme-View wurde im unteren Teil erweitert: es sind nun drei Dockbereiche nebeneinader angesiedelt um Spurenaussteuerung, große Uhr sowie Kapitelmarken gleichzeitig im Blick haben zu können._

- Actions: **im Podcast-Menü gibt es den Eintrag "ausgewählte Spuren für Räuspertasten aktivieren".**
  _Hiermit werden für ausgewählte Spuren die Mute-Enveopes aktiviert und die Automation der Spuren auf WRITE gesetzt. Dies beschleunigt den Einsatz von Räuspertasten ganz erheblich, die Hintergründe sind in der Ultrachall-Folge zu Räuspertasten per Wiimote nachzuschauen._

- Actions: **Alle Spuren für Schnitt vorbereiten**
  _mit diesem Eintrag im Podcast-Menü werden die Recording-Buttons aller Spuren ausgeschaltet und der Mute-Automationsmode auf Trim/Read geschaltet. Sollte nach jeder Aufnahme einmal aktiviert werden._

- Theme: **mit einem Rechtsklick auf dem Spurbereich können verschiedene geschmackvoll ausgewählte Preset-Farben ausgewählt werden**
  _kreiert von niemand Geringerem als @[graphorama](https://twitter.com/graphorama)!_

- Theme: **Legt man Spuren mit den Namen "Einspieler" oder "SKYPE" an so werden diese automagisch mit geschmackvollen Farben versehen.**

- Theme: **Diverse optische Anpassungen**
  _Der Headerbereich ist etwas heller gestaltet. Die Wellenformen werden passend zur Rest-GUI invertiert dargestellt, also hell auf dunkelfarbigem Grund. Die Anzeige, welche Bereiche einer Spur ausgewählt wurden, wurde erheblich klarer gestaltet._

- Theme: **Die Icons wurden mit einer tüchtigen Portion Feenstaub überschüttet.**
  _Dies bezieht sich sowohl auf die etwas wertigere Optik, als auch auf den "State" der nun sauber gehalten wird - man hat jederzeit den Überblick, welcher View aktiv ist, welches Routing-Preset, ob Ripple-Edit aktiv ist sowie ob die Mute-Spuren sichtbar/unsichtbar geschaltet sind._

## Release 1.0 "Rams" - 2014-Feb-09

- Theme: **Ultraschall-Logo und Versionsnummer eingebaut**
  _wird in Zukunft wichtig sein um schnell sehen zu können auf welcher Version man unterwegs ist_

- Actions: **Exportformat der Kapitelmarken von .csv auf .txt umgestellt**
  _Damit man Kapitelmarken einfacher per Cut&Paste in Podlove beim Anlegen einer Episode verwenden kann wurde das Dateiformat für den Export von .csv auf .txt geändert. Die Dateien funktionieren wie bisher ebenfalls millisekundengenau in Auphonic._

- Preferences: **Views speichern nicht mehr die Fensterposition**
  _Wenn man die Views anpasst, wird nicht mehr die Hauptfenster-Position mit gespeichert / verändert. Das sollte nun deutlich weniger verwirrend sein._

## RC4 - 2014-Feb-07

- Theme: **Playrate Regler eingebaut**
  _Oben rechts befindet sich nun ein Regler, mit dem man die Abspielgeschwindigkeit des Podcast beschleunigen kann. Faktor 1,5 kann man noch ganz gut hören - diese Funktion kann im Schnitt (Edit View) nützlich sein um sich zügiger durch eine Aufnahme zu arbeiten. Mit Rechtsklick auf dem Regler kann man den Range des Faders einstellen, ferner sollte dort immer "preserve pitch" aktiviert sein (wird beides über Project Templates gespeichert, nicht global)_

- Actions: **Tastatur-Shortcuts für Navigation durch Projekt**
  _um sich flüssiger im Projekt bewegen zu können wurden zwei Tastenbelegungen geändert: alt+links/rechts springt zur vorherigen/nächsten Kapitelmarke, alt+rauf/runter zur jeweils nächsten Itemkante. Letztere Funktion entfaltet großen Charme in Kombination mit "Stile entfernen", da man so schnell die einzelnen Einspieler durchlaufen kann._

- Preferences: **Master output auch als source in der Routing Matrix**
  _Aus Gründen - die nur die Reaper Entwickler kennen - werden in den famosen neuen Presets zwar die Sends für die Tracks gespeichert, nicht jedoch die Master-Sends. Um dennoch ein 1KlickRouting (tm) umsetzen zu können wandert die Masterspur wieder als Quelle in die Routingmatrix zurück. Das Setting ist damit: Send auf den Master ist immer aktiviert, dieser schickt aber nicht immer zurück in den Mixer. Ich muss dazu mal eine Screencastfolge machen da zu abstrakt, aber es wird alles gut._

## RC3 - 2014-Feb-06

- Preferences: **Menüleiste zeigt verfügbaren Speicher an**
  _in der Menüleiste wird nun angezeigt, wieviel freier Plattenplatz noch auf dem Laufwerk vorhanden ist, auf dem aufgezeichnet wird._

- Theme: **Bereichsbeschriftungen**
  _die beiden Icon-Bereiche Views und Routing-Presets haben Beschriftungen bekommen um die Funktionen etwas klarer zu machen. Die Beschriftungen selbst sind sinnvoll mit Links zu Preset-Fenstern belegt._

- Actions: **Automagische Kapitelmarkengenerierung**
  _Im Edit-View finden sich links zwei neue Icons: diese können radikal bei der Erstellung von Kapitelmarken helfen. Wenn man eine Spur für Einspieler verwendet und diese die Kapitelübergänge markieren, so kann man diese Spur auswählen und dann das erste Icon "Stille entfernen aktivieren - es startet ein Dialog der relativ lange läuft. Ist er bei 100% kann man mit "Split" die komplette Einspielerspur so zerschneiden lassen, dass nur die einzelnen Einspieler übrig bleiben und Stille komplett entfernt wird. Nun kann man das zweite Icon aktivieren: Kapitelmarken-Foo setzt an den Beginn jeden Einspielers automatisch eine Kapitelmarke. Diese muss man nun nur noch sinnvoll benennen, ein mühsames Marken durch die Gegend schieben ist nicht mehr notwendig (aber natürlich immer noch möglich)"_

- Theme: **Icon um die Mute-Spur ein- und auszublenden**
  _Ein gängiges Konzept im Podcasting ist die Räuspertaste. Wie in der entsprechenden Ultraschall-Folge erklärt wird diese optimaler Weise über eine Mute-Automation umgesetzt. Da diese Anzeige häufig etwas im Weg ist (besonders beim Schneiden) gibt es nun ein Icon dass die Spuren für alle Tracks ein- oder ausblenden._

## RC2 - 2014-Feb-03

- Preferences: **Menüs angepasst**
  _ein paar sinnvolle Einträge sind wieder zurück gewandert_

- Preferences: **Diverse Korrekturen**
  _einige Einträge wurden korrigiert: das vertikale Verschieben von Tracks erzeugt keine Automationspuren, das Verlängern von Tracks loopt nicht den Klanginhalt, ctrl-linke Maus erzeugt einen Maus-Rechtsklick, es wird wieder nur eine Datei to Spur geschrieben_

- Theme: **Track-Farbanpassungen**
  _Ein wenig mehr Farbe im Track-Bereich_

## RC1 - 2014-Feb-02

- Theme: **Diverse Farbanpassungen**
  _Die Soundspuren haben einen leichten Verlauf erhalten der die Anmutung noch edler macht. Der Hintergrund der großen Zeitanzeige im Aufnahme-View wurde an den Resthintergrund angepasst. Das Icon zur Anzeige des Ripple-Edit Status wurde an die anderen angepasst. Einige Icons wurden für bessere Verständlichkeit ausgetauscht - etwa zum Setzen von Kapitelmarken_

- Preferences: **Menüs gelichtet**
  _Viele Einträge in den Reaper-Menüs sind für Podcastproduzierende völlig nutzlos und verwirrend. Etliche Einträge wurden daher aus den Menüs entfernt. Die Originalmenüs mit allen Einträgen bleiben dabei als letzter Eintrag in den jeweiligen Menüs erhalten._

- Actions: **Ein weiteres Bedienkonzept wird eingeführt: Snapshots zum Speichern und Abrufen von Routing/Mixerpresets**
  _Schon mit den VProdunktions-Views (F7, F8, F9 oder die drei Icons links oben) wurde versucht den klassischen Podcastingworkflow klarer zu unterstützen. Neben diesen Views, die sich auf Fensteraufbau und sichtbare Werkzeuge konzentrieren, tritt nun das Konzept der Snapshots. Diese können im Setup-View (F7 oder Mixer-Icon) rechts unten im Dock als Reiter angesteuert werden und setzen zwingend die SWS-Extension voraus (siehe Installation). Der Ablauf ist simpel: man stellt sich für die verschiedenen Stadien einer Podcastfolge die benötigten Routing-Setups in der Routing-Matrix zusammen und speicher diese in den Snapshots, die sich dann bequem über die Icons links mittig abrufen lassen. Beispiel: während der Preshow können sch bereits alle vor Ort hören, auf den Stream geht aber nur die Fahrstuhlmusik bis die Sendung beginnt. Bevor man das eigentliche Intro abspielt, schaltet man das Preset um auf Produktion (Mikrophon-Icon) und schon gehen alle Sprachkanäle ebenfalls auf den Stream. In der Poshow (Tassebier) kann leise Musik im Hintergrund laufen, im Schnitt-Preset (Schere) ist für das Abhören nur der Kanal hin zur Abhöreinheit (DAW oder lokaler Kopfhörerausgang) aktiviert. Snapshots sind unabhängig von den Views. Man kann also während einer Sendung beliebig in den Views umherschalten. Die Spanshots hingegen greifen direkt in das Routing ein und sollten nur bewusst umgeschaltet werden - sonst ist etwa der Stream tot. Zur Release gibt es eine Ultraschall-Screencast Folge wie man damit produktiv arbeitet._

- Misc: **Auphonic verarbeitet nun unser neues Kapitelmarkenformat ohne Frames.**
  _Derzeit rundet Auphonic auf ganze Sekunden ab, man hat also etwas Sicherheitsspielraum nach vorn was eher ein Vorteil ist._

## BETA 4 - 2014-Jan-28

- Theme: **Diverse Farbanpassungen**
  _noch stärker als bisher werden Farben und Formen reduziert. Mit diesem Theme dürfte Reaper die reduzierteste DAW überhaupt sein - selbst die Buttonanmutungen wurden reduziert._

- Theme: **Neue Iconleiste**
  _dynamische Iconleisten sind in Reaper nicht vorgesehen, was uns nicht davon abhalten sollte mittels Windows Presets welche zu bauen. Man kann nun links neben den Spuren die drei Views Setup, Sendung und Nachbereitung umschalten und hat sogar eine Rücmeldung in welchem View man sich gerade befindet. Dazu gibt es ein erstes Experiment mit SWS Snapshots: links neben dem Mixerbereich finden sich drei frei belegbare Snapshots, mit denen man sämtliche Mixer- und Routingeinstellungen speichern und abrufen kann - etwa um in der Preshow Musik einzuspielen während die Podcaster sich zwar unterhalten können (auch mit einem Skype-Partner) aber nicht auf den Stream gehen, dann die Sendung und anschließend eine Aftershow mit leisem Musikteppich_

## BETA 3 - aka "Der Zeitvernichter" 2014-Jan-25

- Preferences: **File/Project Settings... 50 - "Project Framerate"**
  _sorgt für sauberen Export der Kapitelmarken ohne Zeitversatz über die Projektlänge. UNBEDINGT so einstellen, selbst wenn man die Distribution ansonsten nicht nutzen möchte, Hintergrund: <http://ultraschall.wikigeeks.de/2014/01/25/howto-zeitversatz-bei-kapitelmarken-beheben>_

- Preferences: **Umstellung der Zeiteinheit auf Minuten:Sekunden**
  _an diversen Stellen. Sorgt nachhaltig dafür, dass Kapitelmarken sauber bis auf die Millisekunde nach Auphonic exportiert werden Teil 2._

- Preferences: **Audio/Rendering - 0ms "Tail length when rendering project or stems, or freezing track"**
  _Eine Aufnahme ist nach dem Rendern exakt so lang wie vorher in der Timeline angezeigt. Der bisherige Presetwert von 1.000ms fügt eine stille Sekunde am Ende hinzu und verwirrt vielleicht._

- Misc: **Footprint der Distribution auf 1/3 reduziert.**

## BETA 2 - 2014-Jan-23

- Preferences: **Audio/Recording - OFF "Always show full track control panel on armed track"**
  _ermöglicht auch Spuren die für die Aufnahme scharfgeschaltet sind in der Höhe sehr klein zu schieben. Dieser Schalter hat im Ultraschall-DR Theme generell keine Funktion, da es hier über das Theme deaktiviert wird._

- Preferences: **Project/Track-Sends Defaults - Input 1 "Record config"**
  _Sorgt dafür, dass bei jeder neu angelegten Spur das Record Monitoring sofort aktiviert ist._

- Theme: **neuer VU-Meter Balken**
  _die Pegelanzeige ist nun dreigeteilt bei Aufnahme (Grün-Gelb-Orange) und Abspielen (Blau - Gelb - Orange) für die bessere Aussteuerung im Setup-View (F7): Grün (Blau) reicht von -60db bis -18, Gelbe von -18 bis -6db (gut gepegelter Durchschnitt) und Orange von -6 db bis 0 db (Headroom für Peaks wie lautes Lachen). Wenn man mit einem Hardware-Limiter arbeitet sollte dieser so konfiguriert werden, dass die Aussteuerung knapp in den Orangenen Bereich (-3db) hineinreicht._

## BETA 1 - 2014-Jan-21

- Actions: **Actions/Show Action List... - Mousewheel "View:Scroll vertically"**
  _Schaltet das Zoomen mit Zweifinger-Trackpad rauf/runter ab und ersetzt es durch vertical-Scrolling wie überall unter OSX_
