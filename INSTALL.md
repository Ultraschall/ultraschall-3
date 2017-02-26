# Installation

## The basics

Use of this distribution is **at your own risk. Previous settings are usually overwritten without further prompts.** It is therefore advised to save your existing settings via the menu `REAPER | Preferences… | General | Export Configuration…`.

Our changes affect on many levels: file system (graphics), Walter theming file, project settings, Reaper settings, toolbar settings, etc. All changes are **open source** ([CC0](https://creativecommons.org/about/cc0)) an can be adapted as wished. Beware: you should have a clear idea of what your are doing.

## Installation instructions for Ultraschall 3.0 (Please follow precisely!)

Depending on your previous Reaper and Ultraschall set-up, there are different paths to follow: update or clean install.

### macOS 10.11 or newer (update)

1. **Update Reaper:** Download and install [Reaper 5.34 64Bit](http://www.reaper.fm/download.php). It can be tested free of charge for 60 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.

2. **Download** [Ultraschall 3.0](http://url.ultraschall-podcast.de/us30) and open the `.dmg` file.

3. **Purge the old installation** by running `Uninstall.command` (right-click > Open with > Terminal & confirm with your password). This will remove old entries from `/System/Library`. In order to remove old [Soundflower](https://rogueamoeba.com/freebies/soundflower/) or USH devices please also run `Remove legacy audio devices.command`.

Continue with the clean install instructions at step 3.

### macOS 10.11 or newer (clean install)

1. **Download and install [Reaper 5.34 64Bit](http://www.reaper.fm/download.php)**. It can be tested free of charge for 30 days and costs US$ 60 afterwards. Presets from an already installed v4 will be retained.

2. **Download** [Ultraschall 3.0](http://url.ultraschall-podcast.de/us30) and open the `.dmg` file.

3. **Launch** `Ultraschall-3.0.pkg` from our `.dmg`. In case an error occurs near the end of the installation, please reboot your Mac and rerun our `.pkg`.

4. **Optional:** In case you want to use advanced Ultraschall features (like purely software-defined N-1 audio-routing for Skype recording), please install our successor to Soundflower: `Ultraschall Hub.pkg`.

5. **Launch Reaper and drag** our `Ultraschall_3.0.ReaperConfigZip` into Reaper's main window. The individual images and config files will be automagically written to the correct locations by Reaper. **WARNING:** If you have adjusted settings before, we recommend to export them via the `REAPER | Preferences… | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a large number of settings without further prompts.

In order to learn more about Ultraschall's functions and usage, we recommend the soon-to-be-published Release Screencast in [our YouTube channel](https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG).

### Windows

<<<<<<< HEAD
1. **Download and install** [Reaper 5.34 **64bit**](http://www.reaper.fm/download.php). It can be tested free of charge for 60 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.

2. **Download the Ultraschall package** via [Ultraschall_3.0.msi (??.? MB)](http://url.ultraschall-podcast.de/us30win) and start the installer. 

3. **Launch Reaper and drag** our `Ultraschall REAPER Theme` from the Desktop into Reaper's main window.. The individual images and config files will automagically be written to the correct locations. **WARNING:** If you are working with adjusted settings, we recommend you export them via the `REAPER | Preferences… | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution will overwrite a large number of settings without further prompts.

4. **Connect StudioLink and the integrated Ultraschall-Soundboard** via `REAPER | Preferences | Plug-ins | VST` (bottom left): click `Auto-detect` (top right) and click `OK`.

5. **Cleanup** Delete the shortcut `Ultraschall REAPER Theme` from the desktop.

=======
1. **Download and install** [Reaper 5.1 **64bit**](http://www.reaper.fm/download.php). It can be tested free of charge for 60 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.
2. **Download and install** the [SWS Extension](http://www.sws-extension.org/). Without this, many Ultraschall features unfortunately won't work.
3. **Download the Ultraschall package** via [Ultraschall_2.1.1win.zip (24.1 MB)](http://url.ultraschall-podcast.de/us21win) and unzip the archive. Search for the  Ultraschall_2.1.ReaperConfigZip file.
4. **Launch Reaper and drag** our [Ultraschall_2.1.ReaperConfigZip](http://url.ultraschall-podcast.de/us21win) into Reaper's main window. **WARNING:** If you have adjusted settings before, we recommend to export them via the `Preferences | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a large number of settings without further prompts.
5. Because we weren't yet able to implement Windows versions of several advanced Ultraschall features (virtual sound cards), the Ultraschall Hub installation can be skipped.
6. A Windows version of our Soundboard is still in the works and we are looking for testers.
>>>>>>> master
