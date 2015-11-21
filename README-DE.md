# Ultraschall Podcasting-Erweiterung für die Reaper DAW

Mit [Podlove](http://podlove.org/) und [Auphonic](https://auphonic.com/) wurden uns Produzierenden von Podcasts mächtige Werkzeuge an die Hand gegeben. Was jedoch fehlte, war eine für Podcasts optimierte Umgebung für Aufnahme und Produktion der eigentlichen Podcasts.

Die verschiedenen DAWs (Digital Audio Workstations) haben verschiedene Vor- und Nachteile, seien sie finanzieller Natur oder in Bezug auf Features. [Reaper](http://www.reaper.fm/) besetzt hier nach Meinung vieler einen Sweet Spot: für schlanke 44 € erhält man das Schweizer Offiziersmesser unter den DAWs, entwickelt von Audio-Nerds (das alte Winamp-Team). Das Problem: Ästhetisch ist Reaper - in der Windowswelt verankert - eine mittlere Zumutung. Zudem sind dutzende Presets gut für Musikproduktionen eingestellt, out-of-the-box jedoch nahezu **absurd falsch** für uns Podcaster - etwa die Orientierung an Takten statt an Zeiteinheiten.

Diese Distribution von Presets, Layouts und Theme versucht Reaper soweit wie nur irgend möglich für Podcasting zu optimieren. Hierbei werden drei Ebenen angegangen:

* **Design.** Es wird eine schlichte, minimalistische Anmutung angestrebt. Ornamente die von der Funktion ablenken sind unerwünscht. Überflüssige sowie redundante Icons und Menüeinträge werden rigoros entfernt.
* **Orientierung am Workflow** Podcaster produzieren komplett anders als Musiker. Bei uns gibt es zumeist die drei Phasen Vorbereitung, (Live-)Sendung und Nachbereitung. An diesen Phasen orientiert sich der Programmaufbau, man kann beliebig zwischen den Views hin- und herschalten.
* **Podcast-Features im Schnellzugriff** Für uns nützliche Funktionen werden prominent platziert: das Setzen und Benennen von Kapitelmarken, deren Export zu Auphonic oder Podlove, Routing-Presets für Preshow und Sendung, Soundboard-Einspieler oder Ripple-Edit damit die Spuren immer synchron bleiben u.v.A.m

Der Einsatz dieser Distribution erfolgt auf **eigene Gefahr, eigene Einstellungen werden in der Regel ungefragt überschrieben** - es lohnt also, diese vorher zu sichern über Preferences/General/Export Configuration...

Unsere Änderungen sind so angelegt, dass sie **vermutlich** einen Versionssprung von Reaper ohne Einschränkungen überleben. Unsere Änderungen greifen auf sehr vielen verschiedenen Ebenen: Dateisystem (Grafiken), Walter-Themingdatei, Projektsettings, Reaper-Settings, Toolbar-Settings. All diese Änderungen sind **quelloffen** ([CC0](https://creativecommons.org/about/cc0)) und können beliebig angepasst werden - man sollte jedoch eine recht klare Vorstellung haben was man tut. Eine Screencast-Folge, die nur auf das Modding eingeht, ist in Planung.

Alle Angaben beziehen sich auf die [englische 64bit-Version von Reaper](http://www.reaper.fm/download-old.php?ver=4x) auf dem MAC (El Capitan). Eine Übersicht, welche der Features auch auf dem PC laufen, findet sich hier: <http://ultraschall.fm/?page_id=462>. 

### Community

Wie unter <http://ultraschall.wikigeeks.de/2014/01/21/gesucht-betatester-fuer-ultraschall-dr-edition-von-reaper/> beschrieben, versuchen wir die Weiterentwicklung von Reaper mit Unterstützung der PodcasterInnen-Community voranzutreiben. Hierzu gibt es diese Anlaufstationen:

* Die Projektseite - wo ich unter anderem in nunmehr drei Videos erkläre was eigentlich Sinn und Zweck des ganzen Projektes ist: <http://ultraschall.fm>

* Ultraschall-Screencast: Alle Funktionen werden in einem Screencast auf Youtube <https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG> ausführlich erläutert. Durch die ständige Weiterentwicklung entsteht hier das Problem, dass ältere Folgen oft einen viel umständlicheren Weg beschreiben, als er mit späteren Releases möglich ist. Dennoch sind die alten Folgen insofern sinnvoll, als dass man hier Grundlagenwissen "von der Pike auf" vermittelt bekommt. Wer also ein Wochenende Zeit... 
Geplant ist eine Text-Überarbeitung der alten Folgen an Stellen, die wirklich nicht mehr dem Status-Quo entsprechen. 

* Das Support-Forum auf sendegate.de: wir haben einen eigenen Ultraschall-Bereich im Sendegate eingerichtet, auf dem sich alle Entwickler und die meisten anwendenden PodcasterInnen tummeln: <https://sendegate.de/c/ultraschall> - eine sehr gute Anlaufstelle für den schnellen Austausch von Ideen oder zur konkreten Problemlösung.

* Unser Board auf Trello für die Weiterentwicklung: <https://trello.com/b/c1ulqLBu/ultraschall-dr-reaper> derzeit eher stiefmütterlich aktualisiert.

* Unser Dokuwiki, in dem wir gern Stück für Stück eine Dokumentation zusammentragen sowie einzelne Einsatz-Szenarien vorstellen würden: <http://wiki.ultraschall-podcast.de>

Alle Kanäle ist lesend frei geschaltet. Wenn du beitragen möchtest, melde dich bei @[rstockm](https://twitter.com/rstockm) oder im [Sendegate](https://sendegate.de/users/rstockm/activity).


### Bedienung

Diese Distribution krempelt viele Bereiche von Reaper um - man muss umlernen, egal ob man von einer anderen DAW oder der Reaper-Originalversion kommt. Ein erster Anlaufpunkt mit kompakter Erklärung der drei Workflow-Views und der Icons findet sich im der Release beiliegenden Release-Poster (zur 1.0 - teilweise überholt, siehe Release-History unten).

Begleitend sei mein Screencast empfohlen, in dem ich auf Details eingehe. Fragen gern an mich oder noch besser im Forum <https://sendegate.de/c/ultraschall>

### Flattr

Hier könnt ihr Flattr-Liebe loswerden:

Daniel: https://flattr.com/profile/danlin
Heiko: https://flattr.com/profile/heikopanjas
Ralf: https://flattr.com/profile/rstockm

Ultraschall insgesamt: https://flattr.com/thing/2490245/Ultraschall-der-Wegbegleiter-durch-das-Fledermausland-der-Podcastsoftware

### Credits:

Diese Distribution basiert im Bereich des Designs bis auf wenige Änderungen auf dem Analog Default Theme von lerian <http://lerians.tumblr.com/post/63734186478/analog-default-theme-for-reaper> - seid großzügig und werft dort eine Spende ab. Bedenkt, wie optisch belastend andernfalls noch immer euer Reaperalltag aussähe...

Das grandiose Logodesign stammt von @graphorama

Weiterer Dank geht an die Betatester:

- [@cyberage](https://twitter.com/cyberage)
- [@dafisch](https://twitter.com/dafisch)
- [@fbrem](https://twitter.com/fbrem)
- [@flowfx](https://twitter.com/flowfx)
- [@herrvonspeck](https://twitter.com/herrvonspeck)
- [@hoersuppe](https://twitter.com/hoersuppe)
- [@klein_p](https://twitter.com/klein_p)
- [@nitramred](https://twitter.com/nitramred)
- [@nsonic](https://twitter.com/nsonic)
- [@timpritlove](https://twitter.com/timpritlove)
- [@opendev](https://twitter.com/opendev)
- [@ronbuehler](https://twitter.com/ronbuehler)
- [@audioponies](https://twitter.com/audioponies)
- [@pixelpille](https://twitter.com/pixelpille)
- [@anbru](https://twitter.com/anbru)
- [@mrtoto](https://twitter.com/mrtoto)
- [@matthiasfromm](https://twitter.com/matthiasfromm)
- [@343max](https://twitter.com/343max)
- [@elicee](https://twitter.com/elicee)
- [@pkurschildgen](https://twitter.com/pkurschildgen)
- [@hermes](https://twitter.com/hermes)
- [@ikari](https://twitter.com/ikari)
- [@fernsehmuell](https://twitter.com/fernsehmuell)
- [@vollraute](https://twitter.com/vollraute)
- [@david_1701](https://twitter.com/david_1701)
- [@michaelblum](https://twitter.com/michaelblum)
- [@kleinesp](https://twitter.com/kleinesp)
- [@KonSciencePod](https://twitter.com/KonSciencePod)
