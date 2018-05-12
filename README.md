# Ultraschall: The podcasting extensions for the Reaper DAW

[Podlove](http://podlove.org/) and [Auphonic](https://auphonic.com/) handed us podcast producers powerful tools, but an optimized environment for the actual recording and production of the podcasts was missing.

The various DAWs (digital audio workstations) have their own pros and cons in terms of costs and features. [Reaper](http://www.reaper.fm/) is hitting a widely recognized sweet spot here: for the slim [price of 60 USD](http://www.reaper.fm/purchase.php) one obtains the Swiss army officer's knife of DAWs, developed by audio nerds (the [old Winamp team](https://en.wikipedia.org/wiki/Winamp#History)). One problem, though: [Reaper](http://www.reaper.fm/)'s aesthetics -- rooted in the Windows world -- are a medium impertinence. Additionally, dozens of presets are well-tuned for music production, but out-of-the-box these are nearly **absurdly wrong** for us podcasters, such as the use of musical bars as time units.

**Ultraschall optimizes [Reaper](http://www.reaper.fm/) for podcasting as far as humanly possible**. A DAW by podcasters for podcasts. This goal is approached on three levels:

- **Design.** A simple, minimalistic impression is aspired to. Distracting ornaments are unwelcome. Superfluous or redundant icons and menu entries are rigorously removed.
- **Guided by workflow.** Podcasters produce completely differently from musicians. We usually have the three phases of preparation, (live) show and post-production. Ultraschall's program composition is guided by these three phases and one can switch between the respective views back and forth at will.
- **Rapid access to podcast features.** Functions that are useful for us podcasters are prominently placed:

## Features

### Preparation

* **Multitrack recording:** Assuming a sound interface that offers multiple tracks, every speaker, Skype/Mumble partners and the soundboard gets her/his own track in Ultraschall.
* **Skype N-1:** Record external speakers without switching a single cable. A clean N-1 circuit can be built purely in software, so that all participants can hear everything and enjoy a clear sound without echoes. Skype callers are recorded on a separate track. If necessary, that can also be replaced with a double-ender recording. The same works with Mumble as well, of course.
* **Custom HUB sound driver:** In order to model complex tasks -- such as Skype N-1 -- in software, one previously needed the abandoned [Soundflower](https://rogueamoeba.com/freebies/soundflower/). Following the latest CoreAudio APIs, we have reimplemented it in a stable and future-proof manner.*
* **Routing:** Track routing can be managed comfortably via a matrix/switchboard. The preset routing can be activated during a show with a single click -- just as on a digital mixing panel. One can switch effortlessly between preshow (only music to the stream, but the podcasts hear each other already and can warm themselves up), show (everything to the stream) and postshow with light background music and cutting (nothing to the stream). You can create and save your own routing presets as well.
* **Multifunctional dock:** You can place and recall different tool in the dock area: track mixer, master mix, media browser, navigator, chapter marks, routing matrix, routing presets, effects, clock. The dock can be split into two or three parts, which can be individually managed via tabs.
* **Workflow and variable user interface:** We offer one preset with custom window arrangement and tools for each of the three workflow steps preparation, show and post-production
* **Podcast menu:** All functions that are necessary for the production of a podcast are neatly summarized in a single menu. The arrangement of the entries form top to bottom corresponds with the workflow of a podcast production.

### Recording

* **Record, cut and export in FLAC format:** The lossless compression format FLAC offers the best compromise between quality and storage requirement. By default, the complete Ultraschall workflow is set to the format. But you can of course switch to WAV or MP3.
* **Chapter marks:** Place named or unnamed chapter marks directly during the recording and export them for the later use in [Podlove](http://podlove.org/) or [Auphonic](https://auphonic.com/).
* **Edit markers:** place these markers in order to quickly find important positions again during the post-production.
* **Soundboard:** Play any number of sound snippets or jingles directly from within the recording software. Manage sets of snippets via the filesystem. Use advanced live functions like fade-in/out, ducking or looping.
* **Ducking:** Add a track for the soundboard that lowers its own volume as soon as someone speaks, and ups it again in a break.
* **Cough buttons:** Each participant can receive a switch that keeps the recording free of unwanted noises. It is recorded, but muted, and can later be optimized or removed.
* **Remote control via MIDI and OSC:** Almost all functions -- such as the cough switches or the placement of chapter or edit markers -- can be remote controlled.
* **Wiimotes and iOS as remove controls:** Wiimotes (or replacement devices) are popular, cheap and flexible remotes- They can be set up with custom MIDI or OSC functions. A control interface based on OSC is offered for iOS.
* **Amp drive:** Large VU meters with peak display (numerical as well) enable the perfect amp drive. The target range of -18dB to -6dB is distinctly colored (yellow).
* **Navigation:** Wherever you are working on within your project, pressing `Y` will jump you back to the current recording position.

### Production

* **Non-destructive cuts for more safety and creativity:** Beginners in particular will like the fact that all changes, cuts and effects can be adjusted or reverted at any time. This can be done independently of the linear undo function and thus enables a confident, creative work with the audio material.
* **Ripple edit:** Cut your multitrack recording without losing sync. Use ripple cut to remove large sections from all tracks simultaneously without introducing gaps.
* **Navigation:** Many shortcuts simplify navigation within a project, such as the direct jump to the next edit marker or object.
* **Variable playback speed:** The playback speed for post-production can be increased. Tone pitch remains constant, of course.
* **Storyboard:** Powerful function that helps you compose audio pieces such as radio features. You can tag areas in your recording -- such as individual answers in an interview -- and later search and filter, also from different projects. Any number of clip databases can be managed. Colors and comments are available, to keep the overview in complex projects. Finished sections and regions can be grouped. Text elements can be distributed freely in the cutting area, in order to manage show notes or comments. The navigator helps you -- independent of the zoom factor -- keep the overview over the whole project.*
* **Effects:** The essential effects for podcasts are integrated directly: expander (composed of soft gate, compressor and limiter) and parametric EQ. The effects are Non-destructive and can be adjusted for each track at any time. Useful settings for these filters are included.
* **Multitrack export:** Export your finished project either as mono, stereo or multitrack file. In the latter case, each speaker track can be optimized by [Auphonic](https://auphonic.com/).

### Installation

* Detailed **Installation instructions** can be found [here](INSTALL.html)

### Contact us

Ultraschall is Open Source.

- Twitter: @[ultraschall_fm](https://twitter.com/ultraschall_fm)
- GitHub: <https://github.com/Ultraschall>
- Support Forum: <https://sendegate.de/c/ultraschall>
- Project Website, download and blog: <http://ultraschall.fm>
- Tutorial Screencast on [Youtube](https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG)

### Credits:

Our grandiose logo and color scheme was designed by @[graphorama](https://twitter.com/graphorama).

