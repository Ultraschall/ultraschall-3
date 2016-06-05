# Installation

## Grundsätzliches

Der Einsatz dieser Distribution erfolgt auf **eigene Gefahr, eigene Einstellungen werden in der Regel ungefragt überschrieben** - es lohnt also, diese vorher über das Menü `Reaper | Preferences | General | Export Configuration…` zu sichern.

Unsere Änderungen greifen auf sehr vielen verschiedenen Ebenen: Dateisystem (Grafiken), Walter-Themingdatei, Projektsettings, Reaper-Settings, Toolbar-Settings. All diese Änderungen sind **quelloffen** ([CC0](https://creativecommons.org/about/cc0)) und können beliebig angepasst werden - man sollte jedoch eine recht klare Vorstellung haben was man tut.


## Installation der 2.1 (Bitte aufmerksam befolgen!)


Je nachdem, ob man bereits eine vorherige Version von Ultraschall im Einsatz hat, unterscheidet sich die Installation: Update oder Clean Install.

### Mac OS X 10.11 (Update)

1. **Reaper aktualisieren:** [Reaper 5.1 64Bit](http://www.reaper.fm/download.php) laden und installieren. Eine Testversion ist uneingeschränkt 60 Tage lauffähig, danach fallen einmalig 54€ Kosten an. Man kann Reaper 5 problemlos über die 4er Version installieren, alle eigenen Presets bleiben erhalten.

2. **Ultraschall 2.1 laden:** [unsere 2.1 Distribution](http://url.ultraschall-podcast.de/us21) laden und das `.dmg` starten

3. **Alte Installation bereinigen:** In dem sich öffnenden Finder-Fenster einmalig `uninstall.command` aus dem `.dmg` durchlaufen lassen. Hiermit werden die alten Einträge aus system/library entfernt. Um alte Soundflower oder USH Geräteeinträge zu entfernen einmalig das Script `Remove legacy audio devices.command`, ebenfalls im `.dmg` zu finden, durchlaufen lassen.

Der weitere Verlauf entsprich der Neuinstallation ab Schritt 3:

### Mac OS X 10.11 (Neuinstallation)


1. **Reaper installieren:** [Reaper 5.1 64Bit](http://www.reaper.fm/download.php) laden und installieren. Eine Testversion ist *uneingeschränkt 60 Tage lauffähig*, danach fallen einmalig 54€ Kosten an.

2. **Ultraschall 2.1 laden:** [unsere 2.1 Distribution](http://url.ultraschall-podcast.de/us21) laden und das `.dmg` starten

3. Unser Installationsprogramm `Ultraschall-2.1.pkg` starten und durchlaufen lassen. Man kann einzelne Komponenten abwählen, das wird jedoch explizit nicht empfohlen. **Achtung:** Sollte die Installation am Ende eine Fehlermeldung ausgeben, bitte einmal OSX neu booten und den Installer erneut durchlaufen lassen – dann funktioniert es mit Sicherheit.

4. **Optional - UltraschallHub installieren:** Wenn man in Ultraschall erweiterte Features wie eine rein in Software modellierte Skype N-1 Schaltung umsetzen möchte, ist die Installation unserer eigenen Ultraschall Devices (ehemals: [Soundflower](https://rogueamoeba.com/freebies/soundflower/)) Voraussetzung. Hierzu das `UltraschallHub.pkg` durchlaufen lassen.

5. **Die Reaper-Ultraschall Konfiguration laden**: Reaper starten. Die Datei `Ultraschall_2.1.ReaperConfigZip` in das geöffnete Reaper Hauptfenster ziehen. Die einzelnen Images und Konfigurationsdateien werden automagisch von Reaper an die richtigen Stellen geschrieben. **WARNUNG:** Wenn man vorher bereits mit eigenen Einstellungen gearbeitet hat empfiehlt es sich, ebendiese **ZUVOR** an gleicher Stelle zu exportieren – es werden von dieser Distribution erhebliche Bereiche ungefragt überschrieben.

6. **Das Ultraschall-Soundboard verbinden:** Unser direkt in die Recordingsoftware integriertes Soundboard zum Einspielen von Jingles und Ähnlichem wird automatisch installiert. Man muss dies jedoch einmalig nach der Installation Reaper mitteilen: Im Menü `Reaper | Preferences… | Plug-ins/VST` anwählen. Nun rechts oben den Button `Auto-detect` drücken und rechts unten mit `Apply` bestätigen. Die Einstellungen können nun wieder geschlossen werden.

7. **Startscreen anpassen:** Damit man beim Starten der Software direkt mit dem Ultraschall-Logo begrüßt wird, legt man die Bilddatei `Ultraschall Reaper Splash Screen.png` an einen beliebigen Ort im Dateisystem ab. In Reaper Startet man aus dem Menü `REAPER | Preferences… | General` und dann unten `Advanced UI/system tweaks…`. Dort aktualsiert man den Pfad unter `Custom splash screen image` zur Datei.

8. **Nur für Neuinstallation:** Damit das neue Ultraschall-Farbset funktioniert, muss anschließend die Preset-Palette des MAC/PC überschrieben werden. **WARNUNG**: wenn bereits mit liebgewonnenen Farb-Presets arbeitet sollte man diesen Import überspringen und sich die Farbwerte lieber manuell einstellen. Der Import funktioniert so: Im Menüpunkt `Extensions` den Punkt Auto Color/Icon aufrufen. Hier kann auch die automagische Zuordnung von Farben und Spurnamen erweitert/angepasst werden. Mit einem Rechtsklick in diesem Fenster `Show Color Management Window` aufrufen. Dort den Punkt `Load color set from file...` auswählen und die in dieser Distribution mitgelieferte Datei `Ultraschall Colorset.SWSColor` laden. Nun stehen alle 11 von @graphorama handgeklöppelten Ultraschall-Farben zur Verfügung.

Zur Handhabung der neuen Funktionen wird der demnächst erscheinende Release Screencast im Ultraschall-Youtube Kanal empfohlen: <https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG>.


##Windows: Installation##

1. **Reaper installieren:** [REAPER v5.201 Windows 64-bit](http://www.reaper.fm/download.php) laden und installieren - eine **Vollversion ist für 60 Tage kostenlos** testbar, danach werden 54 € fällig. Für Windows unterstützen wir nur die **64 Bit** Version.

2. Die [Ultraschall_2.2win.msi (24.1 MB)](http://url.ultraschall-podcast.de/us21win) Datei laden. Den Installer mit Standardeinstellungen durchlaufen lassen.

3. Reaper starten und die nun auf dem Desktop zu findende Datei `Ultraschall REAPER Theme` in das geöffnete Reaper-Fenster fallen lassen. Den Import durchlaufen lassen.

4. Die Verknüpfung `Ultraschall REAPER Theme` wieder vom Desktop löschen.

5. Reaper starten und unter "Podcast"- `About Ultraschall` kontrollieren, dass alle Komponenten richtig installiert sind. 



