# Ultraschall: Die Podcasting-Erweiterung für Reaper

Mit [Podlove](http://podlove.org/) und [Auphonic](https://auphonic.com/) wurden uns Produzierenden von Podcasts mächtige Werkzeuge an die Hand gegeben. Was jedoch fehlte, war eine für Podcasts optimierte Umgebung für Aufnahme und Produktion der eigentlichen Podcasts.

Die verschiedenen DAWs (Digital Audio Workstations) haben verschiedene Vor- und Nachteile, seien sie finanzieller Natur oder in Bezug auf Features. [Reaper](http://www.reaper.fm/) besetzt hier nach Meinung vieler einen Sweet Spot: für schlanke 44 € erhält man das Schweizer Offiziersmesser unter den DAWs, entwickelt von Audio-Nerds (das alte Winamp-Team). Das Problem: Ästhetisch ist Reaper - in der Windowswelt verankert - eine mittlere Zumutung. Zudem sind dutzende Presets gut für Musikproduktionen eingestellt, out-of-the-box jedoch nahezu **absurd falsch** für uns Podcaster - etwa die Orientierung an Takten statt an Zeiteinheiten.

**Ultraschall optimiert Reaper soweit wie nur irgend möglich für Podcasting**. Eine DAW von Podcastern für Podcaster. Hierbei werden drei Ebenen angegangen:

* **Design.** Es wird eine schlichte, minimalistische Anmutung angestrebt. Ornamente die von der Funktion ablenken sind unerwünscht. Überflüssige sowie redundante Icons und Menüeinträge werden rigoros entfernt.
* **Orientierung am Workflow.** Podcaster produzieren komplett anders als Musiker. Bei uns gibt es zumeist die drei Phasen Vorbereitung, (Live-)Sendung und Nachbereitung. An diesen Phasen orientiert sich der Programmaufbau, man kann beliebig zwischen den Views hin- und herschalten.
* **Podcast-Features im Schnellzugriff.** Für uns nützliche Funktionen werden prominent platziert. Ultraschall bietet:


## Features

Die Feature-Entwicklung von Ultraschall erfolgt entlang dem dreigeteilten Workflow Vorbereitung > Aufnahme > Produktion:

### Vorbereitung

* **Mehrspuraufnahme:** Jeder Sprecher bekommt eine eigene Spur (ein passendes Soundinterface vorausgesetzt), ebenso wie Skype/Mumble-Partner oder Einspieler. Dies ermöglicht maximale Freiheit und Kreativität bei der Nachbearbeitung.
* **Skype N-1:** Binde externe Teilnehmer ein, ohne ein einziges Kabel zu ziehen. Allein in Software wird eine saubere N-1 Schaltung aufgebaut, so dass alle Teilnehmer alles hören und einen perfekten Klang ohne Echos genießen. Die Skype-Teilnehmer landen auf einer separaten Spur, die man zur Not auch durch die Aufnahme eines Double-Enders ersetzen kann. Natürlich funktioniert der Aufbau ebenso mit Mumble.
* **Eigener HUB-Soundtreiber:** Um komplexere Aufnahmen - etwa Skype N-1 - in Software modelliert durchführen zu können, benötigte man bisher das nicht mehr weiter entwickelte [Soundflower](https://rogueamoeba.com/freebies/soundflower/). Wir haben entlang der aktuellsten Audio-APIs eine vollständige Neuimplementierung vorgenommen die stabil und zukunftssicher läuft.
* **Routing:** Das Routing von Spuren kann komfortabel über eine Matrix (Kreuzschiene) verwaltet werden. Die vorbereiteten Routing-Presets werden während der Sendung mit einem Klick abgerufen – ganz wie bei einem digitalen Mischpult. Man schaltet problemlos zwischen Preshow (Nur Musik auf dem Livestream, aber alle PodcasterInnen können sich bereits hören und warmlaufen, Sendung (alles auf dem Stream), Postshow mit leisem Musikteppich und Schnitt (nichts auf dem Stream) hin und her. Beliebige eigene Routing-Presets können abgelegt werden.
* **Multifunktionsdock** Im Dockbereich können verschiedene Werkzeuge abgerufen und geordnet werden: Spurenmixer, Mastermix, Medienbrowser, Navigator, Kapitelmarken, Routingmatrix, Routingpresets, Effekte, Uhr. Der Dockbereich kann in zwei oder drei Teile gegliedert werden. Über Reiter können wiederum Werkzeuge pro Dock verwaltet werden.
* **Workflow und variable Nutzeroberfläche:** Für die drei Arbeitsschritte Vorbereitung, Sendung und Nachbereitung wird je ein Preset für Fensteraufteilung und Werkzeuge angeboten. Die Presets können beliebig angepasst werden. Zusätzliche Presets sind einfach zu definieren und mit Icons oder Shortcuts zu versehen.
* **Podcast Menü:** Alle für die Produktion eines Podcasts benötigten Funktionen sind übersichtlich in einem Menü zusammengefasst. Die Reihenfolge innerhalb des Menüs entspricht dabei dem Workflow einer Produktion.




### Aufnahme

* **Aufnahme, Schnitt und Export im FLAC-Format:** Das verlustfreie Kompressionsformat FLAC bietet den besten Kompromiss aus Qualität und Speicheranforderung. Standardmäßig ist der komplette Ultraschall-Workflow daher auf dieses Format hin ausgerichtet. Man kann natürlich auf WAV oder MP3 wechseln.
* **Kapitelmarken:** setze direkt bei der Aufnahme benamte oder unbenamte Kapitelmarken und exportiere sie für eine Weiterverarbeitung in Podlove oder Auphonic.
* **Editiermarken:** setze Marker um schnell wichtige Stellen für eine Nachbearbeitung wiederzufinden.
* **Soundboard:** Spiele direkt aus der Aufnahmesoftware heraus beliebige Einspieler oder Jingles ab. Verwalte Sets von Einspielern über das Dateisystem. Nutze erweiterte Live-Funktionen wie Fade-In/Out, Ducking oder Looping.
* **Ducking:** Füge eine Spur für Einspieler ein, die sich automatisch in der Lautstärke runterregelt, sobald jemand zu sprechen beginnt, und wieder lauter wird in Pausen.
* **Räuspertasten:** Pro Teilnehmer können Räuspertasten konfiguriert werden, die die Aufnahmen von ungewollten Störgeräuschen frei halten. Die eigentliche Aufnahme bleibt erhalten, die Stummschalt-Funktion kann also auch im Nachhinein optimiert oder wieder entfernt werden.
* **Fernsteuerung über MIDI und OSC:** Fast alle Funktionen lassen sich fernsteuern - etwa die Räuspertasten oder das Setzen von Kapitel- und Editiermarken.
* **Wiimotes und iOS Geräte als Fernsteuerungen:** Wiimotes (oder deren Nachbauten) erfreuen sich als günstige und flexible Fernsteuerungen großer Beliebtheit. Sie können mit beliebigen MIDI- oder OSC-Funktionen belegt werden. Für iOS wird ein Steuer-Interface auf OSC-Basis angeboten.
* **Aussteuerung:** Große VU-Meter mit Peak-Anzeige (auch numerisch) ermöglichen die perfekte Aussteuerung. Der Zielbereich von -18dB bis -6dB ist farblich gesondert gekennzeichnet.
* **Navigation:** Wo auch immer man sich gerade zur Kontrolle im Projekt oder im Kapitelmarken-Editor bewegt: mit einem Druck auf `Y` gelangt man verlässlich wieder zu aktuellen Aufnahmeposition.


### Produktion

* **Nicht-destruktiver Schnitt für mehr Sicherheit und Kreativität:** Gerade AnfängerInnen kommt entgegen, dass sämtliche Änderungen im Schnitt oder beim Einsatz von Effekten jederzeit wieder angepasst oder zurückgenommen werden können - völlig unabhängig von einer linearen Undo-Funktion. Dies ermöglicht einen angstfreien und kreativen Umgang mit dem Audiomaterial.
* **Ripple-Edit:** Schneide deine mehrspurige Aufnahme ohne dass zwischen den Spuren ein Versatz entsteht. Verwende Ripple-Cut um schnell ganze Abschnitte über alle Spuren hinweg zu schneiden und die Lücke direkt zu schließen.
* **Variable Abspielgeschwindigkeit:** Die Abhörgeschwindigkeit kann für die Nachproduktion erhöht werden. Die Tonhöhe bleibt dabei konstant.
* **Navigation:** Viele Shortcuts vereinfachen die Orientierung und Navigation im Projekt, etwa das direkte Anspringen der nächsten Schnittmarken oder Objekte.
* **Storyboard:** Mächtige Funktionen, die dich bei "gebauten Beiträgen" wie Radio-Features unterstützen! Versieh beliebige Bereiche einer Aufnahme (z.B. etwa einzelne Antworten) mit Schlagworten, nach denen du auch projektübergreifend suchen und filtern kannst. Verwalte so beliebig viele Clip-Datenbanken. Verwende Farben und Kommentare, um in komplexen Projekten den Überblick zu behalten. Verbinde fertige Abschnitte mit Regionen oder Gruppen, um sie zusammen zu halten. Text-Elemente können frei im Schnittbereich verteilt werden, etwa um Shownotes oder Kommentare zu verwalten. Im Navigator behält man unabhängig vom Zoom-Faktor jederzeit den Überblick über das gesamte Projekt.
* **Effekte:** Die für Podcasts essentiellen Effekte sind direkt eingebunden: Expander (bestehend aus weichem Gate, Kompressor, Limiter) und parametrischer EQ. Die Effekte sind nicht-destruktiv und können jederzeit pro Spur angepasst werden. Für Podcasts sinnvolle Einstellungen der Filter werden mitgeliefert.
* **Multitrack-Export:** Exportiere dein fertiges Projekt entweder als Mono-, Stereo- oder Mehrkanal Datei. Im letzteren Fall kann jede einzelne Sprechspur beispielsweise von [Auphonic](https://auphonic.com/) optimiert werden.


## Community und Kontakt

Wir versuchen die Weiterentwicklung von Reaper mit Unterstützung der PodcasterInnen-Community voranzutreiben. Hierzu gibt es diese Anlaufstellen:

* Die Projektseite - wo wir unter anderem in nunmehr vier Videos erkläre was eigentlich Sinn und Zweck des ganzen Projektes ist: <http://ultraschall.fm>

* Ultraschall-Screencast: Alle Funktionen werden in einer Serie von Screencast auf YouTube <https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG> ausführlich erläutert. Durch die ständige Weiterentwicklung entsteht hier das Problem, dass ältere Folgen oft einen viel umständlicheren Weg beschreiben, als er mit späteren Releases möglich ist. Dennoch sind die alten Folgen insofern sinnvoll, als dass man hier Grundlagenwissen "von der Pike auf" vermittelt bekommt. Wer also ein Wochenende Zeit...
Geplant ist eine Text-Überarbeitung der alten Folgen an Stellen, die wirklich nicht mehr dem Status-Quo entsprechen.

* Das Support-Forum auf sendegate.de: wir haben einen eigenen Ultraschall-Bereich im Sendegate eingerichtet, auf dem sich alle Entwickler und die meisten anwendenden PodcasterInnen tummeln: <https://sendegate.de/c/ultraschall> - eine sehr gute Anlaufstelle für den schnellen Austausch von Ideen oder zur konkreten Problemlösung.

Alle Kanäle ist lesend frei geschaltet. Wenn du beitragen möchtest, melde dich bei @[ultraschall_fm](https://twitter.com/ultraschall_fm) oder im [Sendegate](https://sendegate.de/users/rstockm/activity).


### Bedienung

Diese Distribution krempelt viele Bereiche von Reaper um - man muss umlernen, egal ob man von einer anderen DAW oder der Reaper-Originalversion kommt. Ein erster Anlaufpunkt mit kompakter Erklärung der drei Workflow-Views und der Icons findet sich im der Release beiliegenden Release-Poster (zur 1.0 - teilweise überholt, siehe Release-History unten).

Begleitend sei unser Screencast empfohlen, in dem ich auf Details eingehe. Fragen gern an mich oder noch besser im Forum <https://sendegate.de/c/ultraschall>

### Installation

Die ausführliche Installationsanleitung befindet sich [hier](INSTALL-DE.html)

### Credits:

Das grandiose Logodesign und das Farbset stammen von @[graphorama](https://twitter.com/graphorama). Weiterer Dank geht an die Betatester:

- @[343max](https://twitter.com/343max)
- @[anbru](https://twitter.com/anbru)
- @[audioponies](https://twitter.com/audioponies)
- @[cyberage](https://twitter.com/cyberage)
- @[dafisch](https://twitter.com/dafisch)
- @[david_1701](https://twitter.com/david_1701)
- @[elicee](https://twitter.com/elicee)
- @[fbrem](https://twitter.com/fbrem)
- @[fernsehmuell](https://twitter.com/fernsehmuell)
- @[flowfx](https://twitter.com/flowfx)
- @[hermes](https://twitter.com/hermes)
- @[herrvonspeck](https://twitter.com/herrvonspeck)
- @[hoersuppe](https://twitter.com/hoersuppe)
- @[ikari](https://twitter.com/ikari)
- @[klein_p](https://twitter.com/klein_p)
- @[kleinesp](https://twitter.com/kleinesp)
- @[KonSciencePod](https://twitter.com/KonSciencePod)
- @[macsnider](https://twitter.com/macsnider)
- @[matthiasfromm](https://twitter.com/matthiasfromm)
- @[michaelblum](https://twitter.com/michaelblum)
- @[mrtoto](https://twitter.com/mrtoto)
- @[nitramred](https://twitter.com/nitramred)
- @[nsonic](https://twitter.com/nsonic)
- @[opendev](https://twitter.com/opendev)
- @[pixelpille](https://twitter.com/pixelpille)
- @[pkurschildgen](https://twitter.com/pkurschildgen)
- @[ronbuehler](https://twitter.com/ronbuehler)
- @[timpritlove](https://twitter.com/timpritlove)
- @[vollraute](https://twitter.com/vollraute)
