# Installation von Ultraschall 3.0
Bitte aufmerksam befolgen!


## Grundsätzliches

Der Einsatz dieser Distribution erfolgt auf **eigene Gefahr, eigene Einstellungen werden in der Regel ungefragt überschrieben** - es lohnt sich also, diese vorher über das Menü `REAPER | Preferences | General | Export Configuration…` zu sichern.


## macOS ab 10.11


1. **REAPER installieren:** [REAPER v5.35 OS X 64-bit](http://www.reaper.fm/download.php) laden und installieren. Eine Testversion ist *uneingeschränkt 60 Tage lauffähig*, danach fallen einmalig 65 € Kosten an.

2. **Ultraschall laden:** [unsere 3.0 Distribution](http://url.ultraschall-podcast.de/us30) laden und das `.dmg` starten

3. **Ultraschall Plugin installieren:** Unser Installationsprogramm `Ultraschall-3.0.2.pkg` starten und durchlaufen lassen. **Achtung:** Sollte die Installation am Ende eine Fehlermeldung ausgeben, bitte einmal macOS neu booten und den Installer erneut durchlaufen lassen – dann funktioniert es mit Sicherheit.

4. **Optional - UltraschallHub installieren:** Wenn man in Ultraschall erweiterte Features wie eine rein in Software modellierte Skype N-1 Schaltung umsetzen möchte, ist die Installation unserer eigenen Ultraschall Devices (ehemals: [Soundflower](https://rogueamoeba.com/freebies/soundflower/)) Voraussetzung. Hierzu das `UltraschallHub.pkg` durchlaufen lassen. Für den Einsatz von StudioLink oder Soundboard in Ultraschall ist dieser Schritt *nicht* notwendig und kann übersprungen werden.

5. **Die REAPER Ultraschall-Konfiguration installieren**: REAPER starten. Es erscheint eine Warnmeldung, dass das Theme noch nicht installiert wurde bzw. nur eine veraltete Version gefunden wurde. Nun die Datei `Ultraschall_3.0.ReaperConfigZip` in das geöffnete REAPER Hauptfenster ziehen und `Importieren` klicken. **WARNUNG:** Wenn man vorher bereits mit eigenen Einstellungen gearbeitet hat empfiehlt es sich, diese **ZUVOR** an gleicher Stelle wie oben angegeben zu exportieren – es werden von dieser Distribution erhebliche REAPER-Bereiche ungefragt überschrieben.

6. **Loslegen:** REAPER starten und im Menü unter `Podcast | About Ultraschall...` kontrollieren, dass alle Komponenten richtig installiert sind. Warnmeldungen beim Start zeigen an, wenn entweder Plugin oder Theme nicht richtig installiert wurden. Ultraschall funktioniert nur, wenn **beide** Komponenten (Schritte 3 und 5) installiert sind.
Zur Handhabung der neuen Funktionen empfehlen wir den demnächst erscheinenden Release-Screencast im Ultraschall-Youtube-Kanal: <https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG>.

7. **Problembehandlung:** Falls immer noch Probleme auftreten oder eine sehr alte Installation (vor 2.0) aktualisiert werden soll, empfiehlt es sich, die im `.DMG` liegenden Skripte `Uninstall.command` sowie `Remove legacy audio devices.command` durchlaufen zu lassen.


##Windows: Installation##

1. **REAPER installieren:** [REAPER v5.35 Windows 64-bit](http://www.reaper.fm/download.php) laden und installieren. Eine Testversion ist *uneingeschränkt 60 Tage lauffähig*, danach fallen einmalig 65 € Kosten an. Für Windows unterstützen wir nur die **64 Bit** Version.

2. **Ultraschall laden:** Die [Ultraschall-3.0.2.msi (24.1 MB)](http://url.ultraschall-podcast.de/us30win) Datei laden. Den Installer starten und durchlaufen lassen.

3. **Die REAPER Ultraschall-Konfiguration installieren:** REAPER starten. Es erscheint eine Warnmeldung, dass das Theme noch nicht installiert wurde bzw. nur eine veraltete Version gefunden wurde. Daher die nun auf dem Desktop zu findende Datei `Ultraschall REAPER Theme` in das geöffnete REAPER-Fenster fallen lassen. Den Import durchlaufen lassen. Danach kann die Datei vom Desktop gelöscht werden.

4. **StudioLink und das Ultraschall-Soundboard verbinden:** Unser integriertes Soundboard zum Einspielen von Jingles und Ähnlichem, sowie StudioLink (als Alternative zu Skype-Remoterecordings) und StudioLink OnAir wird automatisch installiert. Man muss dies jedoch REAPER einmalig nach der Installation mitteilen: Im Menü `Options | Preferences… | Plug-ins/VST` anwählen. Nun rechts oben den Button `Auto-detect` drücken und rechts unten mit `Apply` bestätigen. Die Einstellungen können nun wieder geschlossen werden.

5. **Aufräumen:** Die Verknüpfung `Ultraschall REAPER Theme` vom Desktop löschen.

6. **Loslegen:** REAPER starten und im Menü unter `Podcast | About Ultraschall...` kontrollieren, dass alle Komponenten richtig installiert sind. Warnmeldungen beim Start zeigen an, wenn entweder Plugin oder Theme nicht richtig installiert wurden. Ultraschall funktioniert nur, wenn **beide** Komponenten (Schritte 2 und 3) installiert sind.

