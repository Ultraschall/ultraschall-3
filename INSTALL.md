# Installation instructions for Ultraschall 3.0 
Please follow precisely!


## macOS 10.11 or newer (clean install)

1. **Download and install [Reaper 5.34 64Bit](http://www.reaper.fm/download.php)**. It can be tested free of charge for 30 days and costs US$ 60 afterwards.

2. **Download** [Ultraschall 3.0](http://url.ultraschall-podcast.de/us30) and open the `.dmg` file.

3. **Launch** `Ultraschall-3.0.pkg` from our `.dmg`. In case an error occurs near the end of the installation, please reboot your Mac and rerun our `.pkg`.

4. **Optional:** In case you want to use advanced Ultraschall features (like purely software-defined N-1 audio-routing for Skype recording), please install our successor to Soundflower: `Ultraschall Hub.pkg`.

5. **Launch Reaper and drag** our `Ultraschall_3.0.ReaperConfigZip` into Reaper's main window. The individual images and config files will be automagically written to the correct locations by Reaper. **WARNING:** If you have adjusted settings before, we recommend to export them via the `REAPER | Preferences… | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a large number of settings without further prompts.
In order to learn more about Ultraschall's functions and usage, we recommend the soon-to-be-published Release Screencast in [our YouTube channel](https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG).

7. **Troubleshooting** by running `Uninstall.command` (right-click > Open with > Terminal & confirm with your password). This will remove old entries from `/System/Library`. In order to remove old [Soundflower](https://rogueamoeba.com/freebies/soundflower/) or USH devices please also run `Remove legacy audio devices.command`.


### Windows

1. **Download and install** [Reaper 5.34 **64bit**](http://www.reaper.fm/download.php). It can be tested free of charge for 60 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.

2. **Download the Ultraschall package** via [Ultraschall_3.0.msi (??.? MB)](http://url.ultraschall-podcast.de/us30win) and start the installer. 

3. **Launch Reaper and drag** our `Ultraschall REAPER Theme` from the Desktop into Reaper's main window.. The individual images and config files will automagically be written to the correct locations. **WARNING:** If you are working with adjusted settings, we recommend you export them via the `REAPER | Preferences… | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution will overwrite a large number of settings without further prompts.

4. **Connect StudioLink and the integrated Ultraschall-Soundboard** via `REAPER | Preferences | Plug-ins | VST` (bottom left): click `Auto-detect` (top right) and click `OK`.

5. **Cleanup** Delete the shortcut `Ultraschall REAPER Theme` from the desktop.



