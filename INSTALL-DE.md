# Installation von Ultraschall 3.0.3
Die Installation von Ultraschall umfasst **drei zwingend notwendige Schritte**. 
Diese drei Schrittewerden auch in einem [Screencast-Video](https://youtu.be/RTshDTPBMes) erklärt.


--

#1.
###REAPER aktualisieren / installieren

Das Open-Source-Projekt Ultraschall erweitert die kommerzielle Musiksoftware REAPER. Ultraschall 3.0.3 läuft nur mit der Version REAPER 5.40. 

[**REAPER Version v5.40 OS X 64-bit herunterladen**](http://www.reaper.fm/files/5.x/reaper540_x86_64.dmg) 

- Das `.dmg` laden und starten, dann REAPER installieren bzw. auf die Version 5.40 aktualisieren.
- Der Einsatz jeder anderen Version von REAPER führt dazu, dass das Ultraschall-Plugin nicht gestartet wird. Von einem manuellen Update von REAPER auf eine andere Version als 5.40 ist daher zwingend abzusehen.
- Eine Testversion von REAPER ist *uneingeschränkt 60 Tage lauffähig*, danach fallen einmalig 65 € Kosten an.

--
#2.

###Ultraschall laden und den Ultraschall-Installer starten.

Unsere Ultraschall 3.0.3 Distribution laden und das `.dmg` starten:

[**Ultraschall 3.0.3 herunterladen**](http://url.ultraschall-podcast.de/us30)

- Im sich öffnenden Fenster unser Installationsprogramm `Ultraschall-3.0.3.pkg` starten und durchlaufen lassen.
- **Achtung:** Sollte die Installation am Ende eine Fehlermeldung ausgeben, bitte einmal macOS neu booten und den Installer erneut durchlaufen lassen.
- Wenn man nach diesem Schritt REAPER startet, wird man mit Fehlermeldungen begrüßt - daher **unbedingt fortfahren** mit Schritt 3:


--
#3.
###Die REAPER Ultraschall-Konfiguration installieren
- REAPER starten. Es erscheint eine Warnmeldung, dass das Theme noch nicht installiert wurde bzw. nur eine veraltete Version gefunden wurde.
- Nun die Datei `Ultraschall_3.0.ReaperConfigZip` aus dem noch geöffneten `.dmg`-Fenster in das **geöffnete REAPER Hauptfenster ziehen** und `Importieren` klicken.
- Wenn man vorher bereits mit eigenen Einstellungen gearbeitet hat empfiehlt es sich, diese **ZUVOR** zu exportieren – es werden von dieser Distribution erhebliche REAPER-Bereiche ungefragt überschrieben.

--
#4.
###Erfolg der Installation kontrollieren
- REAPER startet nach Schritt 3 automatisch neu.
- Im sich öffnenden Ultraschall-Startscreen auf `Details` drücken und kontrollieren, dass alle Komponenten richtig installiert sind und bei Start keine Warnmeldungen mehr erscheinen.
- Warnmeldungen beim Start zeigen an, wenn entweder Plugin (Schritt 2) oder Theme (Schritt 3) nicht richtig installiert wurden. Ultraschall funktioniert nur, wenn **beide** Komponenten installiert sind. In diesem Fall bitte die Schritte 2 und 3 sorgfältig wiederholen.
- Bei weiteren Fehlermeldungen bitte prüfen, ob wirklich die Version 5.40 von REAPER installiert wurde (Schritt 1). Im Zweifel REAPER noch einmal installieren.
- Es kann weiterhin helfen, den Rechner neu zu starten sowie die `Erste Hilfe` im Festplattendienstprogramm von macOS durchlaufen zu lassen.
- Falls immer noch Probleme auftreten oder eine sehr alte Installation (vor 2.0) aktualisiert werden soll, empfiehlt es sich, die im `.dmg` liegenden Skripte `Uninstall.command` sowie `Remove legacy audio devices.command` durchlaufen zu lassen und den Rechner neu zu starten. Danach die Schritte 1 bis 3 wiederholen.
- Sollten *sämtliche dieser Maßnahmen* nicht zum Erfolg führen, kann man Hilfe in unserem Anwender-Forum erbitten: [Ultraschall im Sendegate
- ](https://sendegate.de/c/ultraschall)
- Zur Handhabung der neuen Funktionen empfehlen wir die Release-Screencast in unserem [Tutorial Bereich](http://ultraschall.fm/tutorials/).

--

###Optional - UltraschallHub installieren
Wenn man in Ultraschall eine rein in Software modellierte SKYPE N-1 Schaltung umsetzen möchte, ist die Installation unserer eigenen Ultraschall Devices Voraussetzung:

- Hierzu das `UltraschallHub.pkg` aus dem `.dmg` Fenster durchlaufen lassen.
- Den Rechner neu starten. Nun sollten die neuen Soundinterfaces in der Audio-Midi-Steuerung von macOS erscheinen.
- Für den Einsatz von StudioLink oder des Ultraschall-Soundboards ist dieser Schritt *nicht* notwendig und kann ignoriert werden.


----





##Windows: Installation##

1. **REAPER aktualisieren / installieren:** [REAPER v5.40 Windows 64-bit](http://www.reaper.fm/files/5.x/reaper540_x64-install.exe) laden und installieren. **Achtung:** Ultraschall setzt wirklich zwingend Version 5.35 oder neuer voraus. Eine Testversion ist *uneingeschränkt 60 Tage lauffähig*, danach fallen einmalig 65 € Kosten an. Für Windows unterstützen wir nur die **64 Bit** Version.

2. **Ultraschall laden:** Die [Ultraschall-3.0.3.msi (24.1 MB)](http://url.ultraschall-podcast.de/us30win) Datei laden. Den Installer starten und durchlaufen lassen.

3. **Die REAPER Ultraschall-Konfiguration installieren:** REAPER starten. Es erscheint eine Warnmeldung, dass das Theme noch nicht installiert wurde bzw. nur eine veraltete Version gefunden wurde. Daher die nun auf dem Desktop zu findende Datei `Ultraschall REAPER Theme` in das geöffnete REAPER-Fenster fallen lassen. Den Import durchlaufen lassen. Danach kann die Datei vom Desktop gelöscht werden.

4. **StudioLink und das Ultraschall-Soundboard verbinden:** Unser integriertes Soundboard zum Einspielen von Jingles und Ähnlichem, sowie StudioLink (als Alternative zu Skype-Remoterecordings) und StudioLink OnAir wird automatisch installiert. Man muss dies jedoch REAPER einmalig nach der Installation mitteilen: Im Menü `Options | Preferences… | Plug-ins/VST` anwählen. Nun rechts oben den Button `Auto-detect` drücken und rechts unten mit `Apply` bestätigen. Die Einstellungen können nun wieder geschlossen werden.

5. **Aufräumen:** Die Verknüpfung `Ultraschall REAPER Theme` vom Desktop löschen.

6. **Loslegen:** REAPER starten und im Menü unter `Podcast | About Ultraschall...` kontrollieren, dass alle Komponenten richtig installiert sind. Warnmeldungen beim Start zeigen an, wenn entweder Plugin oder Theme nicht richtig installiert wurden. Ultraschall funktioniert nur, wenn **beide** Komponenten (Schritte 2 und 3) installiert sind.

