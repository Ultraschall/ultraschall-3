# Changelog

#### Infos:
## Syntax für das Changelog

* Preferences: **Diese Änderungen**
*werden im Preferences-Dialog von Reaper vorgenommen, den man über `⌘`+`,` oder im Menü unter `Reaper | Preferences…` erreicht.*

* Theme: **Diese Änderungen betreffen das mitgelieferte Theme**
*und sind für Design und Anordnung der Elemente (Buttons, Regler, Anzeigen...) verantwortlich.*

* Actions: **Änderungen, die die Bindung von Aktionen**
*teilweise auch Presets auf Tastatur/Maus/Trackpad betreffen.*

* Soundboard: **Features unseres eigenen Soundboards**
*für Einspieler aller Art.*

* Installer: **Neuerungen, die den mit der 1.2**
*eingeführten Installer für den Mac betreffen.*

* Hub [Nur Mac]: **Unser Projekt zur Ablösung von [Soundflower](https://github.com/mattingalls/Soundflower/releases/tag/2.0b2)**
*Soundflower für ein stabiles und knacksfreies Podcastingerlebnis.*

* Misc: **Infos**
*Was sonst noch so anfällt.*

#### Last Changelog:

## 2.2.2 Gropius - 2016-August-14

* Soundboard [Mac]: **Bugfix**
*Bugfix: Aufgenommene Soundbooard-Spuren werdem jetzt abgespielt.*

* Misc [Windows]: **Kompatibilität**
*Updates für Windows 10 Version 1607 (Build 14393, Anniversary-Update).*

* StudioLink: **Update**
*Ultraschall enthält jetzt die neue StudioLink-Version 16.04.1.*

## 2.2.1 Gropius - 2016-June-09

* Installer: **Bugfix**
*Bugfix: Löschen von alten Dateien schlägt fehl. Danke an Marcus Schwarz für den Bugreport.*

* Installer: **Bugfix**
*Bugfix: Löschen von anderen alten Dateien schlägt fehl. Danke an Wolfgang Schulz für den Bugreport.*

## 2.2 Gropius - 2016-Jun-05

* Theme: **Weiteres Feintuning des neuen Themes**
*Die Scrollbalken sowie Zoom-Icons wurden vereinfacht, ebenso Schieberegler in AU/VST-Effekten.*

* Actions: **Räuspertaste und Mute-Spur**
*Komplette Neukonzeption der Räuspertasten- und Mute-Funktion. Der editierbare Mute-Envelope wird nun immer in einer Separaten Spur angezeigt und farblich besser hervorgehoben. Der Mute-Button in der Iconleiste funktioniert nun kontexabhängig: vor einer Aufnahme können ausgewählte Spuren für die Räuspertaste aktiviert werden. Während und nach der Aufnahme schaltet er die Sichtbarkeit der Mute-Spuren ein oder aus.*

* Actions: **Auswahl von Spuren über Tastatur**
*Über die Zahlentasten 1 bis 8 können die jeweiligen Spuren markiert oder unmarkiert werden. 9 markiert sämtliche Spuren, 0 hebt die Markierung sämtlicher Spuren auf.*

* Actions: **Alle Spuren für Schnitt vorbereiten**
*Die Befehlsfolge "Prepare all tracks for editing", die nach jeder Aufnahme aufgerufen werden sollte, wurde verbessert und stellt weitere Parameter für den Schnitt um.*

* Actions: **Neuer Menü-Eintrag "Customize"**
*Im Podcast-Menü sind unter dem neuen Eintrag "Customize" folgende Funktionen zusammengefasst: 'Shortcuts and action list' um Tastaturkürzel neu definieren zu können und neue Funktionen hinzuzufügen, 'Track: set track icon' um Spuren mit einem Symbol verzieren zu können, 'Show theme configuration window' um Farben des Theme anzupassen, 'Show theme element finder' um die Benamung von einzelnen Elementen der GUI zu finden sowie 'Auto color' um die Standardfarben von Spuren in Abhängigkeit ihres Namens festzulegen. Weitere Hinweise über die Anpassbarkeit von Ultraschall/Reaper zeigt dieser Vortrag: <FIXME: Link fehlt>*

* StudioLink: **Vollständige Integration des StudioLink Plugins**
*Als qualitativ in Bezug auf Stabilität, Konstanz und Klangqualität weit überlegene Alternative zu Skype unterstützt Ultraschall nun StudioLink. Ohne den Aufbau einer N-1 Schaltung über die Routingmatrix ist es damit möglich, Ferngespräche mit bis zu 8 PartnerInnen zu führen, die in jeweils separaten(!) Spuren aufgezeichnet werden. Die PartnerInnen können dabei die schlanke Standalone-Version von StudioLink nutzen und benötigen keine eigene DAW. Die Einrichtung einer StudioLink-Schaltung wird im Release-Video erläutert.*

* Soundboard: **Soundboard nun auch für Windows und als AU Version für den Mac**
*Das Ultraschall-Soundboard steht nun mit vollem Funktionsumfang auch unter Windows zur Verfügung. Bei der Mac-Version wurde von VST auf AU Technik umgestellt.*

* Installer: **StudioLink Plugin und standalone**
*Ultraschall liefert im Installer die Version des StudioLink-Plugins aus. Externe GesprächspartnerInnen können sich die [Standalone-Fassung von StudioLink](https://doku.studio-link.de/standalone/installation-standalone.html) laden.*

* Preferences: **Stop Funktion überarbeitet**
*Die Stop-Funktion bei Aufnahmen wurde so überarbeitet, dass der Aufnahme-Cursor nach Stop an das Ende der bisherigen Aufnahme gesetzt wird. Dies verhindert, dass bei einem erneuten Start der Aufnahme kein alternativer Take angelegt wird, sondern die eigentliche Aufnahme fortgesetzt wird.*

* Preferences: **Neue Spuren werden direkt für die Aufnahme aktiviert**
*Alle neu angelegten Spuren werden direkt auf "Record Arm" geschaltet und sind bereit für die Aufnahme - der zusätzliche Klick auf den roten Arm-Knopf kann damit oft entfallen.*

* Misc: **Ultraschall 3 Preset für ReaEQ**
*Standardmäßig wird bei Aktivierung des ReaEQ Equalizers das Preset Ultraschall 3 aktiviert, dass deutlich weniger Bassanhebung und damit Poltern mit sich bringt.*

* Misc: **Ultraschall Presets für gebaute Beiträge**
*Folgende Effekte werden als Ultraschall-Presets für die Verfremdung von Stimmen für gebaute Beiträge angeboten: Telephone (ReaEQ), Small Room, Large Room, Church (ReaVerbate)*

* Installer: **Bugfix**
*Fehlerhafte Code-Signatur in Uninstall.command. Vielen Dank an Arnd Layer für den Bugreport.*

## 2.1.1 Gropius - 2016-Feb-27

* Theme: **Weiteres Feintuning des neuen Themes**
* Windows: **Anpassung der Farbwerte für die Audiospuren**
*Auch unter Windows stimmen nun die Zuordnungen von Bezeichnungen und Farbwerte*


## 2.1 Gropius - 2016-Feb-19

* Theme: **Umfangreiches Feintuning des neuen Themes**
*Der Kontrast von nahezu allen Elementen wurde hoch gesetzt, um die Bedienbarkeit auch in ungünstigen Lichtsituationen zu verbessern. Gruppen von Icons werden optisch zusammengefasst. Einzelne Icons wurden neu gezeichnet um die Funktion klarer werden zu lassen. Die Anmutung aller Buttons wurde vereinheitlicht. Feintuning vieler Farbwerte, um sie der Ultraschall Farbpalette anzupassen. Die Farbpalette ist nun logisch entlang des Regenbogens angeordnet. Schnitte innerhalb eines Items sind durch abgerundete Kanten und eine feine Linie jetzt deutlicher zu erkennen.*

* Preferences: **Snap Funktionen (Magnetisches Andocken)**
*Alle Elemente wie Items, Marker und Regions unterstützen nun das magnetische Andocken, was komplexere Editings vereinfacht.*

* Theme: **Routing Matrix enthält Anzeige über Eingangszuordnungen**
*Im unteren Bereich der Routing-Matrix können nun die Zuordnungen der Input-Kanäle zu den Spuren vorgenommen werden. Somit können nun wirklch alle relevanten Zuordnungen übersichtlich an einer einzigen Stelle erfolgen.*

* Misc: **SWS/S&M Extension 2.8.3**
*Ultraschall wird nun mit der [SWS/S&M Extension 2.8.3](http://www.sws-extension.org/) ausgeliefert*

* Actions: **Neue Shortcuts für flüssiges Editing mit der Tastatur**
*Mit den Tasten `i` und `o` können Anfang und Ende einer Zeitselektion gesetzt werden - analog zu vielen Videoschnittprogrammen. Mit den Tasten `1` und `2` können Anfang und Ende der Selektion angesprungen werden. Die Tastaturzuordnungen für das Springen zwischen Kapitelmarken wurde geändert, um nicht Kollisionen beim wortweisen Springen in Textabschnitten zu provozieren.*

* Actions: **Start/Stop/Pause-Safemode für die Tastatur**
*Um das unbeabsichtigte Beenden einer laufenden Aufnahme zu verhindern, werden die Tasten `RETURN` und `SPACE` während einer Aufnahme abgefangen. Es erscheint ein Dialog, ob die Aufnahme wirklich gestoppt werden soll.*

* Actions: **Robustheit der Kapitelmarken-Funktionen**
*Sämtliche Kapitelmarkenfunktionen wurden neu in Lua implementiert und interpretieren nun, ob a) eine Aufnahme läuft oder b) eine Aufnahme abgespielt wird oder c) keine Aktion stattfindet. Im Falle von a werden die Marken an die aktuelle Aufnahmeposition gesetzt, bei b) an die aktuelle Abspielposition und bei c) an die aktuelle Position des Edit-Cursors. Die Midi-Ansteuerung wurde so robust gestaltet, dass Kapitelmarken über Midi in jedem Zustand des Programmes gesetzt werden können - selbst während bestehende Marken editiert werden.*

* Actions: **Benamung der Ultraschall-Actions**
*Im über die Taste `?` zu erreichenden Actions-Dialog - in dem sich auch Tastatur-Zuordnungen editieren lassen - sind nun alle Ultraschall-Funktionen einheitlich mit dem Präfix `ULTRASCHALL:` benamst und verständlicher formuliert.*

* Soundboard [Nur Mac]: **Bugfix**
*REAPER stürzt nicht mehr ab, wenn der ins Soundboard zu importierende Ordner nur eine Datei enthält. Vielen Dank an Sven Wiegand für den Bugreport.*

* Soundboard: **Bugfix**
*REAPER stürzt nicht mehr ab, wenn eine der zu importierenden Sounddateien nicht decodiert werden kann. Danke an René Kurfürst für den Bugreport.*


## 2.0 Gropius - 2015-Dec-09

* Misc: **Reaper 5 und OS X 10.11 El Capitan**
*Die Ultraschall ist nun für Reaper 5 und OSX 10.11 El Capitan optimiert. Ältere Versionen werden nicht weiter untertützt.*

* Installer [Nur Mac]: **User- statt Systemverzeichnis**
*Der neue Installer schreibt seine Einträge in das User-Verzeichnis von OSX, nicht mehr nach System.*

* Theme: **Komplettes Redesign des Theme**
*Mehr Konsistenz, weniger Unordnung. Alle Icons und Funktionsbereiche wurden überarbeitet, Farben vereinheitlicht.*

* Theme: **Responsiver Mixer**
*In Abhängigkeit der Dock-Höhe blendet der neue Mixerbereich Bediehnelemente ein und aus.*

* Theme: **Neue Ansicht: das Storyboard für gebaute Beiträge.**
*Beliebige Bereiche einer Aufnahme - etwa einzelne Antworten - können mit Schlagworten versehen werden, nach denen - auch projektübergreifend - gesucht und gefiltert werden kann. Verwaltung beliebig vieler Clip-Datenbanken. Farben und Kommentare, um in komplexen Projekten den Überblick zu behalten. Gruppierungsfunktion für fertige Abschnitte und Regionen, um sie zusammen zu halten. Text-Elemente können frei im Schnittbereich verteilt werden, etwa um Shownotes oder Kommentare zu verwalten.*

* Actions [Nur Mac]: **About Screen**
*Neue Funktion: über einen About-Screen können die derzeit installierten Komponenten mit ihren Versionsnummern angezeigt werden*

* Theme: **Translation**
*Die Menüs wurden ins Englische übersetzt.*

* HUB [Nur Mac]: **Neuer Audiotreiber**
*Soundflower gehört der Vergangenheit an: entlang der neuen CoreAudio APIs von OSX 10.11 El Capitan wurde die Audio-Engine für virtuelle Soundkomponenten von Grund auf neu geschrieben.*


## Release 1.3 - 2015-Jul-05

* WICHTIG: **Bis auf weiteres ist diese Release nur unter Reaper 4.78 lauffähig.**
*Wir arbeiten an einer Unterstützung der Reaper 5.0 Version, informiert Euch hierzu im <https://sendegate.de/c/ultraschall>.*

* Installer: **Der Installer hat ein geschmackvolleres Hintergrundbild bekommen.**
*Die aktuelle stable Version der SWS Extension (2.7) wird installiert.*

* Theme: **Überarbeitung des Podcast-Menüs**
*Viele Begrifflichkeiten wurden klarer gefasst und vereinheitlicht. Track Templates (Einspieler, Audio-Track) werden direkt im Menü angezeigt.*

* Theme: **Größe der Fenster**
*Die Default-Fenstergröße von Reaper wurde an ein 13" MBP Retina mit Standard-Auflösung optimiert.*

* Actions: **Letzte Kapitelmarke löschen**
*Neue Funktion im Podcast-Menü und als Shortcut: die erste, sich links vom Edit-Cursor (rote Linie) befindliche Kapitelmarke wird gelöscht. In 99% der Fälle ist dies die zuletzt gesetzte.*

* Actions: **Setze eine Kapitelmarke 2 Minuten in die Vergangenheit**
*Eine blaue Kapitelmarke mit der Bezeichnung "_Past" wird zwei Minuten VOR der derzeitigen Position des Edit-Markers gesetzt. Die hilft beim Markeiren einer Stelle in der Art von "eigentlich sind wir schon längst beim nächsten Thema". Durch die Farbe und den Bezeichner kann die Marke im Schnitt schnell gefunden und an die exakte Position geschoben werden.*

* Actions: **Kapitelmarken schreiben und lesen**
*Das Handling zum Export und Import der Kapitelmarken wurde überarbeitet. Kapitelmarken werden nun im Stil projektname.chapters.txt gespeichert.*

* Actions: **Textelement einfügen**
*In eine leere Spur kann nun an der Position des Cursors ein Text-Element eingefügt werden, das man mit Klick auf die Sprechblase mit beliebigem Text versehen kann der sich dann wie ein Audio-Element verhält. Diese wenn man eine Folge eher "baut", also aus vielen Sequenzen zusammensetzt bei denen etwa die klassischen Kapitelmarken zu unflexibel sind.*

* Presets: **Ein neues Einspieler-Track Preset wird mitgeliefert, bei dem bereits ein Ducking voreingestellt ist.**
*Über die Routing-Matrix werden die Kanäle ausgewählt die das Ducking aktivieren. Die genaue Bediehnung wird im Release-Screencast demonstriert.*

* Preferences: **Die Samplerate wird auf 48KHz gesetzt, die Buffer-Size auf 512. "Ignore running Change Notifications" wird gesetzt.**
*Bis zur Releasde unseres eigenen Audio-Treibers scheint dies unter OSX die am stabilsten funktionierenden Werte zu sein um Knaksen zu verhindern.*

* Soundboard: **Neuer Grid-View**
*Die Ansicht des Soundboard lässt sich umschalten zwischen der bekannten Tabellenansicht und einer Grid-Ansicht*

* Soundboard: **Ein- Ausfaden**
*Das Ein- und Ausfaden wird nun in sämtlichen Play-Modi unterstützt - etwa einfaden aus Pause etc.*

* Soundboard: **Ducking**
*Es gibt einen neuen Ducking-Schalter der sämtliche gerade laufenden Einspieler sanft auf eine zu definierende, geringere Lautstärke runterregelt über die man gut drübersprechen kann. Ein Ausschalten bewirkt wieder eine Anhebung der Einspieler. Die stärke des Ducking lässt sich in den Soundboard-Settings einstellen.*

* Soundboard: **Master-Volume**
*Die Gesamtlautstärke des Einspieler-Outputs kann über einen Schieberegler eingestellt werden*

* Soundboard: **Themes**
*Man kann verschiedene Farbsets für das Soundboard einstellen*

* Soundboard: **Live-Mode**
*Hat man alle Einstellungen im Soundboard wie Lautstärken einmal eingestellt, kann man diese nun für die Sendung in einen "Lock" Modus versetzen: egal welche Presets verwendet werden, die Soundboard Einstellungen bleiben unberührt.*

* Misc: **Bugfixes in den Plugins**
*Einige garstige Speicherlecks wurden in unseren Reaper-Plugins geschlossen. Damit sich diese jeh auswirken hätte man aber einige Tage aufnehmen müssen.*

* HUB [Nur Mac]: **Die virtuellen Sound-Devices werden umbenannt, um die Zuordnung in SKYPE intuitiver zu gestalten.**
*Stereo-Geräte werden vor Mono-Geräte gesetzt um Verschiebungen in der Routing-Matrix vorzubeugen.*



## Release 1.2 - 2015-Jan-04

* Installer: **Unter Mac OSX können weite Teile der Distribution nun über einen einfachen Installer abgewickelt werden**
*Soundflower Ultraschall-Edition, Startlogo, SWS-Extensions sowie das Ultraschall-Soundboard werden installiert. Manuell muss nur noch einmalig die Theme -Datei in Reaper gezogen werden.*

* Theme: **Neuer Eintrag im Podcast-Menü: Navigation/Springe zu Play-Cursor (#-Taste)**
*springt zur aktuellen Position des Play-Cursors (Orange)*

* Theme: **Neuer Eintrag im Podcast-Menü: Soundboard Spur anlegen *Legt eine Spur an, in der bereits alle Einstellungen für das Ultraschall Soundboard gesetzt sind.**
*Im sich öffnenden Auswahlfenster muss man einmalig "Soundboard.RTrackTemplate" anwählen. Zur Funktionalität des Soundboard s.U.*

* Theme: **Neues Untermenü im Podcast-Menü: Selection**
*bieter verschiedene nützliche Aktionen um den Schnitt mittels Selections zu beschleunigen - insbesondere Ripple-Delete zum schnellen Löschen von ganzen Passagen über alle Spuren**

* Theme: **Einheitliche Symbole für Chapters(Dreieck/Strick)**
*Neue Icons für setze Kapitelmarke, Export Chapters und Audiodatei Schreiben*

* Theme: **Mute- und Solo-Buttons**
*In der Spuranzeige links sind nun immer die jeweiligen Mute- und Solo-Buttons sichtbar.*

* Actions: **Neue Menüpunkte und Kontext-Links für den Umgang**
*mit der Mute-Spur (Räuspertasten). Separate Mute-Spur für ausgewählten Track an/Ausschalten, Sichtbarkeit aller Mute-Spuren an/ausschalten. In der separaten Mute-Spur kann direkt mit dem Mauscursor und der linken Maustaste ein Mute-Bereich gemalt werden*

* Actions: **Verbessertes Audiodatei schreiben**
*Der Menüpunkt "Audiodatei Schreiben" und das entsprechende Icon links unten im Edit-View setzen zunächst die Playrate des Projektes auf 1.0 um dann das Render-Menü zu starten. Ferner werden zuvor sämtliche Spuren ausgewählt, so dass man direkt einen Multifrack Export für Auphonic (Stems Export) starten kann.*

* Misc: **Das Ultraschall-Soundboard feiert seinen Einstand und ist als VST-Effekt-Plugin realisiert.**
*Für die genaue Bedienung bitte den Release-Screencast schauen. Funktionen: Verwalten von verschiedenen Sets, Play, Pause, Stop, Loop, Fade, einstellbare Fade-Zeit, regelbare Lautstärke pro Einspieler, direkte OSC-Kopplung. Zur OSC-Steuerung - etwas über ein iOS Gerät oder die Wiimotes - kommt in Kürze ein weiterer Screencast*

* Presets: **Ultraschall-Presets für Expander und EQ**
*als Ergebnis eine kleinen Workshops mit Michael Kummeth gibt es im EQ das "Ultraschall2" Preset, das einen sehr guten Ausgangspunkt für moderate EQ-Einstellungen bietet.*

* Presets: **optimiertes Datei-Handling**
*Alle Dateien einer Podcast-Folge (Projektdatei, Aufnahmedateien, Peak-Dateien, Kapitelmarken-Datei) werden übersichtlich im Projektordner und mit sinnvollen Unterordnern abgelegt. Details sind dem Screencast zu entnehmen.*

* Presets: **Sinnvolle Presets zur Dateibenamung von Aufnahmen eingestellt**
*(Tracknummer-Trackname-Folgenname)*

* Misc: **Für die Verlinkung des Projektes auf der eigenen Podcast-Seite**
*werden zwei unauffällige Badges mitgeliefert.*

* Misc: **Für Probleme, Anregungen etc.**
*wurde auf sendegate.de ein Support-Forum eingerichtet das den bisherigen Patter-Raum ersetzt:  <https://sendegate.de/c/ultraschall>*


## Release 1.1 - 2014-Jun-09

* Theme: **Es gibt ein neues Menü "Podcast" in dem nach Workflowschritten unterteilt sämtliche Podcast-Funktionen gesammelt sind.**
*Die Funktionen gliedern sich nach den drei Workflow-Schritten "Setup, Aufnahme und Produktion" und sind auch innerhalb der Gruppen so angeordnet, dass man sie von oben nach unten durchgehen kann. Jede neue Aufnahme durchläuft somit die Einträge (oder zumindest Teile davon) des Menüs von oben nach unten. Die Details sind dem 1.1 Release-Screencast zu entnehmen*

* Actions: **Import von mp4chaps Kapitelmarken (etwa: Shownotes Export) als Marker**

* Actions: **Export von Kapitelmarken als mp4chaps für Podlove und Auphonic**

* Actions: **Mit "E" oder dem neuen Icon werden rote Edit-Marken gesetzt**

* Theme: **im Edit-View ist ein neues Icon verfügbar, das den aktuellen Projekt-Ordner öffnet.**
*Der Aufnahme-View wurde im unteren Teil erweitert: es sind nun drei Dockbereiche nebeneinader angesiedelt um Spurenaussteuerung, große Uhr sowie Kapitelmarken gleichzeitig im Blick haben zu können.*

* Actions: **im Podcast-Menü gibt es den Eintrag "ausgewählte Spuren für Räuspertasten aktivieren".**
*Hiermit werden für ausgewählte Spuren die Mute-Enveopes aktiviert und die Automation der Spuren auf WRITE gesetzt. Dies beschleunigt den Einsatz von Räuspertasten ganz erheblich, die Hintergründe sind in der Ultrachall-Folge zu Räuspertasten per Wiimote nachzuschauen.*

* Actions: **Alle Spuren für Schnitt vorbereiten**
*mit diesem Eintrag im Podcast-Menü werden die Recording-Buttons aller Spuren ausgeschaltet und der Mute-Automationsmode auf Trim/Read geschaltet. Sollte nach jeder Aufnahme einmal aktiviert werden.*

* Theme: **mit einem Rechtsklick auf dem Spurbereich können verschiedene geschmackvoll ausgewählte Preset-Farben ausgewählt werden**
*kreiert von niemand Geringerem als @[graphorama](https://twitter.com/graphorama)!*

* Theme: **Legt man Spuren mit den Namen "Einspieler" oder "SKYPE" an so werden diese automagisch mit geschmackvollen Farben versehen.**

* Theme: **Diverse optische Anpassungen**
*Der Headerbereich ist etwas heller gestaltet. Die Wellenformen werden passend zur Rest-GUI invertiert dargestellt, also hell auf dunkelfarbigem Grund. Die Anzeige, welche Bereiche einer Spur ausgewählt wurden, wurde erheblich klarer gestaltet.*

* Theme: **Die Icons wurden mit einer tüchtigen Portion Feenstaub überschüttet.**
*Dies bezieht sich sowohl auf die etwas wertigere Optik, als auch auf den "State" der nun sauber gehalten wird - man hat jederzeit den Überblick, welcher View aktiv ist, welches Routing-Preset, ob Ripple-Edit aktiv ist sowie ob die Mute-Spuren sichtbar/unsichtbar geschaltet sind.*


## Release 1.0 "Rams" - 2014-Feb-09

* Theme: **Ultraschall-Logo und Versionsnummer eingebaut**
*wird in Zukunft wichtig sein um schnell sehen zu können auf welcher Version man unterwegs ist*

* Actions: **Exportformat der Kapitelmarken von .csv auf .txt umgestellt**
*Damit man Kapitelmarken einfacher per Cut&Paste in Podlove beim Anlegen einer Episode verwenden kann wurde das Dateiformat für den Export von .csv auf .txt geändert. Die Dateien funktionieren wie bisher ebenfalls millisekundengenau in Auphonic.*

* Preferences: **Views speichern nicht mehr die Fensterposition**
*Wenn man die Views anpasst, wird nicht mehr die Hauptfenster-Position mit gespeichert / verändert. Das sollte nun deutlich weniger verwirrend sein.*


## RC4 - 2014-Feb-07

* Theme: **Playrate Regler eingebaut**
*Oben rechts befindet sich nun ein Regler, mit dem man die Abspielgeschwindigkeit des Podcast beschleunigen kann. Faktor 1,5 kann man noch ganz gut hören - diese Funktion kann im Schnitt (Edit View) nützlich sein um sich zügiger durch eine Aufnahme zu arbeiten. Mit Rechtsklick auf dem Regler kann man den Range des Faders einstellen, ferner sollte dort immer "preserve pitch" aktiviert sein (wird beides über Project Templates gespeichert, nicht global)*

* Actions: **Tastatur-Shortcuts für Navigation durch Projekt**
*um sich flüssiger im Projekt bewegen zu können wurden zwei Tastenbelegungen geändert: alt+links/rechts springt zur vorherigen/nächsten Kapitelmarke, alt+rauf/runter zur jeweils nächsten Itemkante. Letztere Funktion entfaltet großen Charme in Kombination mit "Stile entfernen", da man so schnell die einzelnen Einspieler durchlaufen kann.*

* Preferences: **Master output auch als source in der Routing Matrix**
*Aus Gründen - die nur die Reaper Entwickler kennen - werden in den famosen neuen Presets zwar die Sends für die Tracks gespeichert, nicht jedoch die Master-Sends. Um dennoch ein 1KlickRouting (tm) umsetzen zu können wandert die Masterspur wieder als Quelle in die Routingmatrix zurück. Das Setting ist damit: Send auf den Master ist immer aktiviert, dieser schickt aber nicht immer zurück in den Mixer. Ich muss dazu mal eine Screencastfolge machen da zu abstrakt, aber es wird alles gut.*


## RC3 - 2014-Feb-06

* Preferences: **Menüleiste zeigt verfügbaren Speicher an**
*in der Menüleiste wird nun angezeigt, wieviel freier Plattenplatz noch auf dem Laufwerk vorhanden ist, auf dem aufgezeichnet wird.*

* Theme: **Bereichsbeschriftungen**
*die beiden Icon-Bereiche Views und Routing-Presets haben Beschriftungen bekommen um die Funktionen etwas klarer zu machen. Die Beschriftungen selbst sind sinnvoll mit Links zu Preset-Fenstern belegt.*

* Actions:  **Automagische Kapitelmarkengenerierung**
*Im Edit-View finden sich links zwei neue Icons: diese können radikal bei der Erstellung von Kapitelmarken helfen. Wenn man eine Spur für Einspieler verwendet und diese die Kapitelübergänge markieren, so kann man diese Spur auswählen und dann das erste Icon "Stille entfernen aktivieren - es startet ein Dialog der relativ lange läuft. Ist er bei 100% kann man mit "Split" die komplette Einspielerspur so zerschneiden lassen, dass nur die einzelnen Einspieler übrig bleiben und Stille komplett entfernt wird. Nun kann man das zweite Icon aktivieren: Kapitelmarken-Foo setzt an den Beginn jeden Einspielers automatisch eine Kapitelmarke. Diese muss man nun nur noch sinnvoll benennen, ein mühsames Marken durch die Gegend schieben ist nicht mehr notwendig (aber natürlich immer noch möglich)"*

* Theme: **Icon um die Mute-Spur ein- und auszublenden**
*Ein gängiges Konzept im Podcasting ist die Räuspertaste. Wie in der entsprechenden Ultraschall-Folge erklärt wird diese optimaler Weise über eine Mute-Automation umgesetzt. Da diese Anzeige häufig etwas im Weg ist (besonders beim Schneiden) gibt es nun ein Icon dass die Spuren für alle Tracks ein- oder ausblenden.*


## RC2 - 2014-Feb-03

* Preferences: **Menüs angepasst**
*ein paar sinnvolle Einträge sind wieder zurück gewandert*

* Preferences: **Diverse Korrekturen**
*einige Einträge wurden korrigiert: das vertikale Verschieben von Tracks erzeugt keine Automationspuren, das Verlängern von Tracks loopt nicht den Klanginhalt, ctrl-linke Maus erzeugt einen Maus-Rechtsklick, es wird wieder nur eine Datei to Spur geschrieben*

* Theme: **Track-Farbanpassungen**
*Ein wenig mehr Farbe im Track-Bereich*


## RC1 - 2014-Feb-02

* Theme: **Diverse Farbanpassungen**
*Die Soundspuren haben einen leichten Verlauf erhalten der die Anmutung noch edler macht. Der Hintergrund der großen Zeitanzeige im Aufnahme-View wurde an den Resthintergrund angepasst. Das Icon zur Anzeige des Ripple-Edit Status wurde an die anderen angepasst. Einige Icons wurden für bessere Verständlichkeit ausgetauscht - etwa zum Setzen von Kapitelmarken*

* Preferences: **Menüs gelichtet**
*Viele Einträge in den Reaper-Menüs sind für Podcastproduzierende völlig nutzlos und verwirrend. Etliche Einträge wurden daher aus den Menüs entfernt. Die Originalmenüs mit allen Einträgen bleiben dabei als letzter Eintrag in den jeweiligen Menüs erhalten.*

* Actions: **Ein weiteres Bedienkonzept wird eingeführt: Snapshots zum Speichern und Abrufen von Routing/Mixerpresets**
*Schon mit den VProdunktions-Views (F7, F8, F9 oder die drei Icons links oben) wurde versucht den klassischen Podcastingworkflow klarer zu unterstützen. Neben diesen Views, die sich auf Fensteraufbau und sichtbare Werkzeuge konzentrieren, tritt nun das Konzept der Snapshots. Diese können im Setup-View (F7 oder Mixer-Icon) rechts unten im Dock als Reiter angesteuert werden und setzen zwingend die SWS-Extension voraus (siehe Installation). Der Ablauf ist simpel: man stellt sich für die verschiedenen Stadien einer Podcastfolge die benötigten Routing-Setups in der Routing-Matrix zusammen und speicher diese in den Snapshots, die sich dann bequem über die Icons links mittig abrufen lassen. Beispiel: während der Preshow können sch bereits alle vor Ort hören, auf den Stream geht aber nur die Fahrstuhlmusik bis die Sendung beginnt. Bevor man das eigentliche Intro abspielt, schaltet man das Preset um auf Produktion (Mikrophon-Icon) und schon gehen alle Sprachkanäle ebenfalls auf den Stream. In der Poshow (Tassebier) kann leise Musik im Hintergrund laufen, im Schnitt-Preset (Schere) ist für das Abhören nur der Kanal hin zur Abhöreinheit (DAW oder lokaler Kopfhörerausgang) aktiviert. Snapshots sind unabhängig von den Views. Man kann also während einer Sendung beliebig in den Views umherschalten. Die Spanshots hingegen greifen direkt in das Routing ein und sollten nur bewusst umgeschaltet werden - sonst ist etwa der Stream tot. Zur Release gibt es eine Ultraschall-Screencast Folge wie man damit produktiv arbeitet.*

* Misc: **Auphonic verarbeitet nun unser neues Kapitelmarkenformat ohne Frames.**
*Derzeit rundet Auphonic auf ganze Sekunden ab, man hat also etwas Sicherheitsspielraum nach vorn was eher ein Vorteil ist.*


## BETA 4 - 2014-Jan-28

* Theme: **Diverse Farbanpassungen**
*noch stärker als bisher werden Farben und Formen reduziert. Mit diesem Theme dürfte Reaper die reduzierteste DAW überhaupt sein - selbst die Buttonanmutungen wurden reduziert.*

* Theme: **Neue Iconleiste**
*dynamische Iconleisten sind in Reaper nicht vorgesehen, was uns nicht davon abhalten sollte mittels Windows Presets welche zu bauen. Man kann nun links neben den Spuren die drei Views Setup, Sendung und Nachbereitung umschalten und hat sogar eine Rücmeldung in welchem View man sich gerade befindet. Dazu gibt es ein erstes Experiment mit SWS Snapshots: links neben dem Mixerbereich finden sich drei frei belegbare Snapshots, mit denen man sämtliche Mixer- und Routingeinstellungen speichern und abrufen kann - etwa um in der Preshow Musik einzuspielen während die Podcaster sich zwar unterhalten können (auch mit einem Skype-Partner) aber nicht auf den Stream gehen, dann die Sendung und anschließend eine Aftershow mit leisem Musikteppich*

## BETA 3 - aka "Der Zeitvernichter" 2014-Jan-25

* Preferences: **File/Project Settings... 50 - "Project Framerate"**
*sorgt für sauberen Export der Kapitelmarken ohne Zeitversatz über die Projektlänge. UNBEDINGT so einstellen, selbst wenn man die Distribution ansonsten nicht nutzen möchte, Hintergrund: <http://ultraschall.wikigeeks.de/2014/01/25/howto-zeitversatz-bei-kapitelmarken-beheben>*

* Preferences: **Umstellung der Zeiteinheit auf Minuten:Sekunden**
*an diversen Stellen. Sorgt nachhaltig dafür, dass Kapitelmarken sauber bis auf die Millisekunde nach Auphonic exportiert werden Teil 2.*

* Preferences: **Audio/Rendering - 0ms "Tail length when rendering project or stems, or freezing track"**
*Eine Aufnahme ist nach dem Rendern exakt so lang wie vorher in der Timeline angezeigt. Der bisherige Presetwert von 1.000ms fügt eine stille Sekunde am Ende hinzu und verwirrt vielleicht.*

* Misc: **Footprint der Distribution auf 1/3 reduziert.**


## BETA 2 - 2014-Jan-23

* Preferences: **Audio/Recording - OFF "Always show full track control panel on armed track"**
*ermöglicht auch Spuren die für die Aufnahme scharfgeschaltet sind in der Höhe sehr klein zu schieben. Dieser Schalter hat im Ultraschall-DR Theme generell keine Funktion, da es hier über das Theme deaktiviert wird.*

* Preferences: **Project/Track-Sends Defaults - Input 1 "Record config"**
*Sorgt dafür, dass bei jeder neu angelegten Spur das Record Monitoring sofort aktiviert ist.*

* Theme: **neuer VU-Meter Balken**
*die Pegelanzeige ist nun dreigeteilt bei Aufnahme (Grün-Gelb-Orange) und Abspielen (Blau - Gelb - Orange) für die bessere Aussteuerung im Setup-View (F7): Grün (Blau) reicht von -60db bis -18, Gelbe von -18 bis -6db (gut gepegelter Durchschnitt) und Orange von -6 db bis 0 db (Headroom für Peaks wie lautes Lachen). Wenn man mit einem Hardware-Limiter arbeitet sollte dieser so konfiguriert werden, dass die Aussteuerung knapp in den Orangenen Bereich (-3db) hineinreicht.*


## BETA 1 - 2014-Jan-21

* Actions: **Actions/Show Action List... - Mousewheel "View:Scroll vertically"**
*Schaltet das Zoomen mit Zweifinger-Trackpad rauf/runter ab und ersetzt es durch vertical-Scrolling wie überall unter OSX*
