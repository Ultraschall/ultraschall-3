# Installation instructions for Ultraschall 3.0
Please follow precisely!


## Basics

Use this distribution at **your own risk since existing settings are generally overwritten without prompt**. Therefore, please save them via the menu `REAPER | Preferences | General | Export Configuration…` before installing Ultraschall.

## macOS 10.11 or newer

1. **Download and install [Reaper 5.35 OS X 64-bit](http://www.reaper.fm/download.php)**. The test version is fully functional for 60 days and costs US$ 60 afterwards.

2. **Download our [Ultraschall 3.0](http://url.ultraschall-podcast.de/us30) distribution** and open the `.dmg` file.

3. **Start and run `Ultraschall-3.0.2.pkg`** from our `.dmg`. **Please note:** In case an error occurs near the end of the installation, please reboot macOS once and rerun our installer. It definitely works then.

4. **Optional - install UltraschallHub:** In case you want to use advanced Ultraschall features (like purely software-defined N-1 audio-routing for Skype recording), please install our successor to [Soundflower](https://rogueamoeba.com/freebies/soundflower/): `Ultraschall Hub.pkg`. This step is *not required* for using StudioLink, StudioLink OnAir or the soundboard.

5. **Install REAPER Ultraschall configuration:** Launch Reaper. A warning about the theme not being installed or being outdated will be shown. Now drag our `Ultraschall_3.0.ReaperConfigZip` into Reaper's main window and click `Import`. **WARNING:** If you have adjusted settings before, we recommend to export them via the `REAPER | Preferences… | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a considerable portion of REAPER's settings  without further prompts.
In order to learn more about Ultraschall's functions and usage, we recommend the soon-to-be-published Release Screencast in [our YouTube channel](https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG).

7. **Troubleshooting** by running `Uninstall.command` (right-click > Open with > Terminal & confirm with your password). This will remove old entries from `/System/Library`. In order to remove old [Soundflower](https://rogueamoeba.com/freebies/soundflower/) or USH devices please also run `Remove legacy audio devices.command`.


### Windows

1. **Download and run the [Reaper 5.35 Windows 64-bit](http://www.reaper.fm/download.php) installer**. The test version is fully functional for 60 days and costs US$ 60 afterwards.

2. **Download and run [Ultraschall-3.0.2.msi (24.1 MB)](http://url.ultraschall-podcast.de/us30win)**.

3. **Install REAPER Ultraschall configuration:** Start REAPER. A warning about the theme not being installed or being outdated will be shown. Now drag our `Ultraschall REAPER Theme` from your Windows desktop into Reaper's main window. Let the import run complete. Now you can delete the file from your desktop.

4. **Connect StudioLink and the Ultraschall-Soundboard:** Our integrated soundboard plays jingles etc., StudioLink Onair is a broadcasting solution while Studio-Link is a remote recording and alternative to Skype. All three are installed automatically and just need to be activated once in the menu `Options | Preferences… | Plug-ins/VST`. Click `Auto-detect` (top right) and then confirm with `Apply`. You may now close the settings.

5. **Cleanup** Delete the shortcut `Ultraschall REAPER Theme` from your desktop.

6. **Dive in:** Start REAPER and check the menu `Podcast | About Ultraschall...` for complete installation of all components. Warning messages will appear upon startup in case plguins or theme are not correctly installed. Ultraschall only works if **both** components are installed (steps 2 and 3).


