Ultraschall DR Reaper Theme
=================================

Mit Podlove und Auphonic wurden uns Produzierenden von Podcasts mächtige Werkzeuge an die Hand gegeben. Was jedoch fehlte, war eine für Podcasts optimierte Umgebung für Aufnahme und Produktion der eigentlichen Podcasts.

Die verschiedenen DAWs (Digital Audio Workstations) haben verschiedene Vor- und Nachteile, seien sie finanzieller Natur oder in Bezug auf Features. Reaper besetzt hier nach Meinung vieler einen Sweet Spot: für schlanke 44 € erhält man das Schweizer Offiziersmesser unter den DAWs, entwickelt von Audio-Nerds (das alte Winamp-Team). Das Problem: Ästhetisch ist Reaper - in der Windowswelt verankert - eine mittlere Zumutung. Zudem sind dutzende Presets gut für Musikproduktionen eingestellt, out-of-the-box jedoch nahezu **absurd falsch** für uns Podcaster - etwa die Orientierung an Takten statt an Zeiteinheiten.

Diese Distribution von Presets, Layouts und Theme versucht Reaper soweit wie nur irgend möglich für Podcasting zu optimieren. Hierbei werden drei Ebenen angegangen:

* **Design.** Es wird eine schlichte, minimalistische Anmutung angestrebt. Ornamente die von der Funktion ablenken sind unerwünscht. Überflüssige sowie redundante Icons und Menüeinträge werden rigoros entfernt.
* **Orientierung am Workflow** Podcaster produzieren komplett anders als Musiker. Bei uns gibt es zumeist die drei Phasen Vorbereitung, (Live-)Sendung und Nachbereitung. An diesen Phasen orientiert sich der Programmaufbau, man kann beliebig zwischen den Views hin- und herschalten.
* **Podcast-Features im Schnellzugriff** Für uns nützliche Funktionen werden prominent platziert: das Setzen und Benennen von Kapitelmarken, deren Export zu Auphonic oder Podlove, Routing-Presets für Preshow und Sendung, Ripple-Edit damit die Spuren immer synchron bleiben u.v.A.m

Der Einsatz dieser Distribution erfolgt auf **eigene Gefahr, eigene Einstellungen werden in der Regel ungefragt überschrieben** - es lohnt also, diese vorher zu sichern über Preferences/General/Export Configuration...

Meine Änderungen sind so angelegt, dass sie **vermutlich** einen Versionssprung von Reaper ohne Einschränkungen überleben. Wissen werden wir das erst, wenn es ein paar gegeben hat, aber ich bin zuversichtlich. Meine Änderungen greifen auf sehr vielen verschiedenen Ebenen: Dateisystem (Grafiken), Walter-Themingdatei, Projektsettings, Reaper-Settings, Toolbar-Settings. All diese Änderungen sind **quelloffen** (CC0) und können beliebig angepasst werden - man sollte jedoch eine recht klare Vorstellung haben was man tut. Eine Screencast-Folge, die nur auf das Modding eingeht, ist in Planung.

Alle Angaben beziehen sich auf die Englische Standardfassung von Reaper auf dem MAC (Mavericks). Die Chancen stehen gut, dass die meisten Features auch mit der Windows-Version funktionieren.

### Download:



### Installation:
---------------------------------------
1. Reaper laden und installieren - eine **Vollversion ist für 30 Tage kostenlos** testbar: <http://www.reaper.fm> danach werden 44 € fällig. Es wird zwingend Reaper 4.62 oder neuer vorausgesetzt
2. **MAC**: Die **SWS-Extension** aus dieser Distribution (sws-v2.4.0.9 Mac.dmg) installieren. **PC**: hier kann die : <http://sws.mj-s.com> - etwas nach unten scrollen zum Bereich "DOWNLOAD LAST BETA/PRE-RELEASE"
3. **MAC**: Die Ultraschall-Edition von Soundflower laden und installieren <http://marius-eisenbraun.de/soundflower-ultraschall-edition/> Für den **PC** existiert nach aktuellem Forschungsstand keine Alternative, siehe <http://ultraschall.wikigeeks.de/2014/06/08/gastbeitrag-podcasting-und-ultraschall-unter-windows-ein-erfahrungsbericht/>
4. Die Reaper-Ultraschall Konfiguration laden: Reaper starten. Die Datei Ultraschall_1_1_final.ReaperConfigZip in das Reaper Hauptfenster ziehen. Sollte dies auf dem **PC** nicht funktionieren: im Repaer-Menü unter Reaper/Preferences.../General mit "import configuration..." die Datei laden. Die einzelnen Images und Configurationsdateien werden automagisch von Reaper an die richtigen Stellen geschrieben. **WARNUNG:**
Wenn man vorher bereits mit eigenen Einstellungen gearbeitet hat empfiehlt es sich, ebendiese **ZUVOR** an gleicher Stelle zu exportieren - es werden von dieser Distribution erhebliche Bereiche ungefragt überschrieben.
5. Im Menü unter Podcast/Projekt-Vorlagen/ "Ultraschall" aufrufen. Direkt im selben Menü "Aktuelles Projekt als Vorlage speichern..." anwählen und unter dem eigenen Sendungsnamen speichern. Darüber kann man später auch einzelne Setups verwalten (Solopodcast, Podcast mit Skype-Partnern etc.)"
6. Teil unseres Ultraschall-.zip Archivs ist eine erste eigene Extension: **reaper_Ultraschall.dylib** - diese Datei muss in das /Users/username/Library/Application Support/REAPER/UserPlugins Verzeichnis gelegt werden. Der einfachste Weg dieses Verzeichnis zu finden (der Ordner Library ist auf dem MAC standardmäßig unsichtbar) führt über Reaper: einfach Reaper starten und im Menü unter "Options" den Eintrag "Show REAPER ressource path" anwählen. Dann kann direkt der Ordner UserPlugins geöffnet werden.
7. Damit das neue Ultraschall-Farbset funktioniert, muss anschließend die Preset-Palette des MAC/PC überschrieben werden. **WARNUNG**: wenn bereits mit liebgewonnenen Farb-Presets arbeitet sollte man diesen Import überspringen und sich die Farbwerte lieber manuell einstellen. Der Import funktioniert so: Im Menüpunkt "Extensions" den Punkt Auto Color/Icon aufrufen. Hier kann auch die automagische Zuordnung von Farben und Spurnamen erweitert/angepasst werden. Mit einem Rechtsklick in diesem Fenster "Show Color Management Window" aufrufen. Dort den Punkt "Load color set from file..." auswählen und die in dieser Distribution mitgelieferte Datei "Ultraschall Colorset.SWSColor" laden. Nun stehen alle 11 Ultraschall-Farben zur Verfügung.
8. Zur Handhabung der doch zahlreichen neuen Funktionen wird der 1.1 Release Screencast empfohlen.


### Community:
---------------------------------------

wie unter <http://ultraschall.wikigeeks.de/2014/01/21/gesucht-betatester-fuer-ultraschall-dr-edition-von-reaper/> beschrieben versuche ich die Weiterentwicklung von Reaper mit Unterstützung der PodcasterInnen-Community voranzutreiben. Hierzu gibt es diese ANlaufstationen:

* Die Projektseite - wo ich unter anderem in einem Video erkläre was eigentlich Sinn und Zweck des ganzen Projektes ist: <http://ultraschall.wikigeeks.de>

* Chat auf Patter (App.net) - auch Fragen zu Bedienung und Bugreporting: <http://patter-app.net/room.html?channel=41961>

* Unser Board auf Trello für die Weiterentwicklung: <https://trello.com/b/c1ulqLBu/ultraschall-dr-reaper>

* Unser Dokuwiki, in dem wir Stück für Stück eine Dokumentation zusammentragen sowie einzelne Einsatz-Szenarien vorstellen: <http://wiki.ultraschall-podcast.de>

Alle drei ist lesend frei geschaltet, wenn du beitragen möchtest: melde dich bei mir (rstockm) auf Twitter oder ADN


### Bedienung:
---------------------------------------

Diese Distribution krempelt viele Bereiche von Reaper um - man muss umlernen. Ein erster Anlaufpunkt mit kompakter Erklärung der drei Workflow-Views und der Icons findet sich in diesem Release-Poster.

Begleitend sei mein Screencast empfohlen in dem ich auf Details eingehe. Fragen gern an mich oder noch besser im Patter-Raum <http://patter-app.net/room.html?channel=41961>.

### Syntax für das Changelog
---------------------------------------

**Preferences**
Diese Änderungen werden im Preferences-Dialog von Reaper vorgenommen , den man über ⌘, oder im Menü unter Reaper/Preferences... erreicht.

**Theme**
Diese Änderungen betreffen das mitgelieferte Theme und sind für Design und Anordnung der Elemente (Buttons, Regler, Anzeigen...) verantwortlich.

**Actions**
Änderungen, die die Bindung von Aktionen, teilweise auch Presets auf Tastatur/Maus/Trackpad betreffen.

**Misc**
Was sonst noch so anfällt

---
Changelog
---------------------------------------

### Release 1.1 - 9.6.2014

* **Theme** Es gibt ein neues Menü "Podcast" in dem nach Workflowschritten unterteilt sämtliche Podcast-Funktionen gesammelt sind. *Die Funktionen gliedern sich nach den drei Workflow-Schritten "Setup, Aufnahme und Produktion" und sind auch innerhalb der Gruppen so angeordnet, dass man sie von oben nach unten durchgehen kann. Jede neue Aufnahme durchläuft somit die Einträge (oder zumindest Teile davon) des Menüs von oben nach unten. Die Details sind dem 1.1 Release-Screencast zu entnehmen*

* **Actions** Import von mp4chaps Kapitelmarken (etwa: Shownotes Export) als Marker

* **Actions** Export von Kapitelmarken als mp4chaps für Podlove und Auphonic

* **Actions** Mit "E" oder dem neuen Icon werden rote Edit-Marken gesetzt

* **Theme** im Edit-View ist ein neues Icon verfügbar, das den aktuellen Projekt-Ordner öffnet. Der Aufnahme-View wurde im unteren Teil erweitert: es sind nun drei Dockbereiche nebeneinader angesiedelt um Spurenaussteuerung, große Uhr sowie Kapitelmarken gleichzeitig im Blick haben zu können.

* **Actions** im Podcast-Menü gibt es den Eintrag "ausgewählte Spuren für Räuspertasten aktivieren". *Hiermit werden für ausgewählte Spuren die Mute-Enveopes aktiviert und die Automation der Spuren auf WRITE gesetzt. Dies beschleunigt den Einsatz von Räuspertasten ganz erheblich, die Hintergründe sind in der Ultrachall-Folge zu Räuspertasten per Wiimote nachzuschauen.*

* **Actions** Alle Spuren für Schnitt vorbereiten *mit diesem Eintrag im Podcast-Menü werden die Recording-Buttons aller Spuren ausgeschaltet und der Mute-Automationsmode auf Trim/Read geschaltet. Sollte nach jeder Aufnahme einmal aktiviert werden.*

* **Theme** mit einem Rechtsklick auf dem Spurbereich können verschiedene geschmackvoll ausgewählte Preset-Farben ausgewählt werden - kreiert von niemand Geringerem als @graphorama!

* **Theme** Legt man Spuren mit den Namen "Einspieler" oder "SKYPE" an so werden diese automagisch mit geschmackvollen Farben versehen.

* **Theme** - Diverse optische Anpassungen *Der Headerbereich ist etwas heller gestaltet. Die Wellenformen werden passend zur Rest-GUI invertiert dargestellt, also hell auf dunkelfarbigem Grund. Die Anzeige, welche Bereiche einer Spur ausgewählt wurden, wurde erheblich klarer gestaltet. .*

* **Theme** Die Icons wurden mit einer tüchtigen Portion Feenstaub überschüttet. *Dies bezieht sich sowohl auf die etwas wertigere Optik, als auch auf den "State" der nun auber gehalten wird - man hat jederzeit den Überblick, welcher View aktiv ist, welches Routing-Preset, ob Ripple-Edit aktiv ist sowie ob die Mute-Spuren sichtbar/unsichtbar geschaltet sind.*

### Release 1.0 "Rams" - 9.2.2014


* **Theme** - Ultraschall-Logo und Versionsnummer eingebaut *wird in Zukunft wichtig sein um schnell sehen zu können auf welcher Version man unterwegs ist*

* **Actions** Exportformat der Kapitelmarken von .csv auf .txt umgestellt *Damit man Kapitelmarken einfacher per Cut&Paste in Podlove beim Anlegen einer Episode verwenden kann wurde das Dateiformat für den Export von .csv auf .txt geändert. Die Dateien funktionieren wie bisher ebenfalls millisekundengenau in Auphonic.*

* **Preferences** Views speichern nicht mehr die Fensterposition *Wenn man die Views anpasst, wird nicht mehr die Hauptfenster-Position mit gespeichert / verändert. Das sollte nun deutlich weniger verwirrend sein.*

### RC4 - 7.2.2014


* **Theme** - Playrate Regler eingebaut *Oben rechts befindet sich nun ein Regler, mit dem man die Abspielgeschwindigkeit des Podcast beschleunigen kann. Faktor 1,5 kann man noch ganz gut hören - diese Funktion kann im Schnitt (Edit View) nützlich sein um sich zügiger durch eine Aufnahme zu arbeiten. Mit Rechtsklick auf dem Regler kann man den Range des Faders einstellen, ferner sollte dort immer "preserve pitch" aktiviert sein (wird beides über Project Templates gespeichert, nicht global)*

* **Actions** Tastatur-Shortcuts für Navigation durch Projekt *um sich flüssiger im Projekt bewegen zu können wurden zwei Tastenbelegungen geändert: alt+links/rechts springt zur vorherigen/nächsten Kapitelmarke, alt+rauf/runter zur jeweils nächsten Itemkante. Letztere Funktion entfaltet großen Charme in Kombination mit "Stile entfernen", da man so schnell die einzelnen Einspieler durchlaufen kann.*

* **Preferences** Master output auch als source in der Routing Matrix *Aus Gründen - die nur die Reaper Entwickler kennen - werden in den famosen neuen Presets zwar die Sends für die Tracks gespeichert, nicht jedoch die Master-Sends. Um dennoch ein 1KlickRouting (tm) umsetzen zu können wandert die Masterspur wieder als Quelle in die Routingmatrix zurück. Das Setting ist damit: Send auf den Master ist immer aktiviert, dieser schickt aber nicht immer zurück in den Mixer. Ich muss dazu mal eine Screencastfolge machen da zu abstrakt, aber es wird alles gut.*


### RC3 - 6.2.2014


* **Preferences** - Menüleiste zeigt verfügbaren Speicher an *in der Menüleiste wird nun angezeigt, wieviel freier Plattenplatz noch auf dem Laufwerk vorhanden ist, auf dem aufgezeichnet wird.*

* **Theme** - Bereichsbeschriftungen *die beiden Icon-Bereiche Views und Routing-Presets haben Beschriftungen bekommen um die Funktionen etwas klarer zu machen. Die Beschriftungen selbst sind sinnvoll mit Links zu Preset-Fenstern belegt.*

* **Actions** - Automagische Kapitelmarkengenerierung *Im Edit-View finden sich links zwei neue Icons: diese können radikal bei der Erstellung von Kapitelmarken helfen. Wenn man eine Spur für Einspieler verwendet und diese die Kapitelübergänge markieren, so kann man diese Spur auswählen und dann das erste Icon "Stille entfernen aktivieren - es startet ein Dialog der relativ lange läuft. Ist er bei 100% kann man mit "Split" die komplette Einspielerspur so zerschneiden lassen, dass nur die einzelnen Einspieler übrig bleiben und Stille komplett entfernt wird. Nun kann man das zweite Icon aktivieren: Kapitelmarken-Foo setzt an den Beginn jeden Einspielers automatisch eine Kapitelmarke. Diese muss man nun nur noch sinnvoll benennen, ein mühsames Marken durch die Gegend schieben ist nicht mehr notwendig (aber natürlich immer noch möglich)"*

* **Theme** - Icon um die Mute-Spur ein- und auszublenden *Ein gängiges Konzept im Podcasting ist die Räuspertaste. Wie in der entsprechenden Ultraschall-Folge erklärt wird diese optimaler Weise über eine Mute-Automation umgesetzt. Da diese Anzeige häufig etwas im Weg ist (besonders beim Schneiden) gibt es nun ein Icon dass die Spuren für alle Tracks ein- oder ausblenden.*

### RC2 - 3.2.2014


* **Preferences** - Menüs angepasst *ein paar sinnvolle Einträge sind wieder zurück gewandert*

* **Preferences** - Diverse Korrekturen *einige Einträge wurden korrigiert: das vertikale Verschieben von Tracks erzeugt keine Automationspuren, Das Verlängern von Tracks loopt nicht den Klanginhalt, ctrl-linke Maus erzeugt einen Maus-Rechtsklick, Es wird wieder nur eine Datei to Spur geschrieben*

* **Theme** - Track-Farbanpassungen *Ein wenig mehr Farbe im Track-Bereich*


### RC1 - 2.2.2014


* **Theme** - Diverse Farbanpassungen *Die Soundspuren haben einen leichten Verlauf erhalten der die Anmutung noch edler macht. Der Hintergrund der großen Zeitanzeige im Aufnahme-View wurde an den Resthintergrund angepasst. Das Icon zur Anzeige des Ripple-Edit Status wurde an die anderen angepasst. Einige Icons wurden für bessere Verständlichkeit ausgetauscht - etwa zum Setzen von Kapitelmarken*

* **Preferences** - Menüs gelichtet *Viele Einträge in den Reaper-Menüs sind für Podcastproduzierende völlig nutzlos und verwirrend. Etliche Einträge wurden daher aus den Menüs entfernt. Die Originalmenüs mit allen Einträgen bleiben dabei als letzter Eintrag in den jeweiligen Menüs erhalten.*

* **Actions** - Ein weiteres Bedienkonzept wird eingeführt: Snapshots zum Speichern und Abrufen von Routing/Mixerpresets *Schon mit den VProdunktions-Views (F7, F8, F9 oder die drei Icons links oben) wurde versucht den klassischen Podcastingworkflow klarer zu unterstützen. Neben diesen Views, die sich auf Fensteraufbau und sichtbare Werkzeuge konzentrieren, tritt nun das Konzept der Snapshots. Diese können im Setup-View (F7 oder Mixer-Icon) rechts unten im Dock als Reiter angesteuert werden und setzen zwingend die SWS-Extension voraus (siehe Installation). Der Ablauf ist simpel: man stellt sich für die verschiedenen Stadien einer Podcastfolge die benötigten Routing-Setups in der Routing-Matrix zusammen und speicher diese in den Snapshots, die sich dann bequem über die Icons links mittig abrufen lassen. Beispiel: während der Preshow können sch bereits alle vor Ort hören, auf den Stream geht aber nur die Fahrstuhlmusik bis die Sendung beginnt. Bevor man das eigentliche Intro abspielt, schaltet man das Preset um auf Produktion (Mikrophon-Icon) und schon gehen alle Sprachkanäle ebenfalls auf den Stream. In der Poshow (Tassebier) kann leise Musik im Hintergrund laufen, im Schnitt-Preset (Schere) ist für das Abhören nur der Kanal hin zur Abhöreinheit (DAW oder lokaler Kopfhörerausgang) aktiviert. Snapshots sind unabhängig von den Views. Man kann also während einer Sendung beliebig in den Views umherschalten. Die Spanshots hingegen greifen direkt in das Routing ein und sollten nur bewusst umgeschaltet werden - sonst ist etwa der Stream tot. Zur Release gibt es eine Ultraschall-Screencast Folge wie man damit produktiv arbeitet.*

* **Misc** - Auphonic verarbeitet nun unser neues Kapitelmarkenformat ohne Frames. *Derzeit rundet Auphonic auf ganze Sekunden ab, man hat also etwas Sicherheitsspielraum nach vorn was eher ein Vorteil ist.*



---------------------------------------
### BETA 4 - 28.1.2014


* **Theme** - Diverse Farbanpassungen *noch stärker als bisher werden Farben und Formen reduziert. Mit diesem Theme dürfte Reaper die reduzierteste DAW überhaupt sein - selbst die Buttonanmutungen wurden reduziert.*

* **Theme** - Neue Iconleiste *dynamische Iconleisten sind in Reaper nicht vorgesehen, was uns nicht davon abhalten sollte mittels Windows Presets welche zu bauen. Man kann nun links neben den Spuren die drei Views Setup, Sendung und Nachbereitung umschalten und hat sogar eine Rücmeldung in welchem View man sich gerade befindet. Dazu gibt es ein erstes Experiment mit SWS Snapshots: links neben dem Mixerbereich finden sich drei frei belegbare Snapshots, mit denen man sämtliche Mixer- und Routingeinstellungen speichern und abrufen kann - etwa um in der Preshow Musik einzuspielen während die Podcaster sich zwar unterhalten können (auch mit einem Skype-Partner) aber nicht auf den Stream gehen, dann die Sendung und anschließend eine Aftershow mit leisem Musikteppich*


### BETA 3 - aka "Der Zeitvernichter" 25.1.2014


* **Preferences** - File/Project Settings... 50 - "Project Framerate" *sorgt für sauberen Export der Kapitelmarken ohne Zeitversatz über die Projektlänge. UNBEDINGT so einstellen, selbst wenn man die Distribution ansonsten nicht nutzen möchte, Hintergrund: <http://ultraschall.wikigeeks.de/2014/01/25/howto-zeitversatz-bei-kapitelmarken-beheben>*

* **Preferences** - Umstellung der Zeiteinheit auf Minuten:Sekunden *an diversen Stellen. Sorgt nachhaltig dafür, dass Kapitelmarken sauber bis auf die Millisekunde nach Auphonic exportiert werden Teil 2.*

* **Preferences** - Audio/Rendering - 0ms "Tail length when rendering project or stems, or freezing track" *Eine Aufnahme ist nach dem Rendern exakt so lang wie vorher in der Timeline angezeigt. Der bisherige Presetwert von 1.000ms fügt eine stille Sekunde am Ende hinzu und verwirrt vielleicht.*

* **Misc** - Footprint der Distribution auf 1/3 reduziert.

### BETA 2 - 23.1.2014


* **Preferences** - Audio/Recording - OFF "Always show full track control panel on armed track" *ermöglicht auch Spuren die für die Aufnahme scharfgeschaltet sind in der Höhe sehr klein zu schieben. Dieser Schalter hat im Ultraschall-DR Theme generell keine Funktion, da es hier über das Theme deaktiviert wird.*

* **Preferences** - Project/Track-Sends Defaults - Input 1 "Record config" *Sorgt dafür, dass bei jeder neu angelegten Spur das Record Monitoring sofort aktiviert ist.*

* **Theme** - neuer VU-Meter Balken *die Pegelanzeige ist nun dreigeteilt bei Aufnahme (Grün-Gelb-Orange) und Abspielen (Blau - Gelb - Orange) für die bessere Aussteuerung im Setup-View (F7): Grün (Blau) reicht von -60db bis -18, Gelbe von -18 bis -6db (gut gepegelter Durchschnitt) und Orange von -6 db bis 0 db (Headroom für Peaks wie lautes Lachen). Wenn man mit einem Hardware-Limiter arbeitet sollte dieser so konfiguriert werden, dass die Aussteuerung knapp in den Orangenen Bereich (-3db) hineinreicht.*


### BETA 1 - 21.1.2014

* **Actions** - Actions/Show Action List... - Mousewheel "View:Scroll vertically"  *Schaltet das Zoomen mit Zweifinger-Trackpad rauf/runter ab und ersetzt es durch vertical-Scrolling wie überall unter OSX*

### Credits:
---------------------------------------
Diese Distribution basiert im Bereich des Designs bis auf wenige Änderungen auf dem Analog Default Theme von lerian <http://lerians.tumblr.com/post/63734186478/analog-default-theme-for-reaper> - seid großzügig und werft dort eine Spende ab. Bedenkt, wie optisch belastend andernfalls noch immer euer Reaperalltag aussähe...

Das grandiose Logodesign stammt von: Das grandiose Logodesign stammt von:@graphorama

Weiterer Dank gehen an die Betatester:
@cyberage
@dafisch
@fbrem
@flowfx
@herrvonspeck
@hoersuppe
@klein_p
@nitramred
@nsonic
@timpritlove
@opendev
@ronbuehler
@audioponies
@pixelpille
@anbru
@mrtoto
@matthiasfromm
@343max
@elicee
@pkurschildgen
@hermes
@ikari
@fernsehmuell
@vollraute
@david_1701
@michaelblum
@kleinesp
