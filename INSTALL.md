## The basics

Use of this distribution is **on your own risk. Previous settings are usually overwritten without further prompts.** It is therefore advised to save your existing settings via `Preferences | General | Export Configuration…`.

Our changes affect many levels: file system (graphics), Walter theming file, project settings, Reaper settings, toolbar settings, etc. All changes are **open source** ([CC0](https://creativecommons.org/about/cc0)) an can be adapted as you wish. But you should have a clear idea of what your are doing.

## Installation instructions for Ultraschall 2.0 (Please follow precisely!)

Depending on your previous Reaper and Ultraschall set-up, there are different paths for you to follow: update or clean install.

### Mac (update)

1. **Update Reaper:** Download and install [Reaper 5](http://www.reaper.fm/download-old.php?ver=5x). It can be tested free of charge for 30 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.

2. **Download [Ultraschall 2](http://url.ultraschall-podcast.de/us2rc1)** and open the `.dmg` file.

3. **Purge the old installation** by running `uninstall.command` (alternative click > Open with > Terminal & confirm with your password). This will remove old entries from `/System/Library`. In order to remove old Soundflower or USH devices, please also download and run our [Soundflower Removal Tool](http://url.ultraschall-podcast.de/soundfloweremovalool).

Continue with the clean install instructions at step 3.

### Mac (clean install)

1. **Download and install [Reaper 5](http://www.reaper.fm/download-old.php?ver=5x)**. It can be tested free of charge for 30 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.

2. **Download [Ultraschall 2](http://url.ultraschall-podcast.de/us2rc1)** and open the `.dmg` file.

3. **Launch Ultraschall-2.0.pkg** from our `.dmg`. You can deselect components in the installer, but we explicitly recommend against that. In case an error occurs near the end of the installation, please reboot your Mac and rerun our .pkg`.

4. **Optional:** In case you want to use advanced Ultraschall features like purely software-defined N-1 circuits for Skype recording, please install our successor to Soundflower: `Ultraschall Hub.pkg`.

5. Launch Reaper and drag our `Ultraschall_2.0.ReaperConfigZip` into Reaper's main window. The individual images and config files will be automagically written to the correct locations by Reaper. **WARNING:** If you have adjusted settings before, we recommend to export them via the `Preferences | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a large number of settings without further prompts.

6. **Connect the Ultraschall-Soundboard** via `Preferences | Plug-ins | VST` (bottom left): click `Auto-detect` (top right) and `OK`.

7. **Optional:** In case you want to use our hand-crafted color scheme by [@graphorama](https://sendegate.de/users/graphorama), go to `Extensions | Auto Color/Icon`. Right-click into that window and select Show Color Management Window. Via `Load color set from file…`, go into our `.dmg` and open `/Add-ons/Ultraschall Colorset.SWSColor`.

In order to learn more about Ultraschall's functions and usage, we recommend the soon-to-be-published Release Screencast in [our Youtube channel](https://www.youtube.com/playlist?list=PLrHlJxVCzpcUF8e0pbt60uSK26JNxbFzG).

### Windows

1. Download and install [Reaper 5 **64bit**](http://www.reaper.fm/download-old.php?ver=5x). It can be tested free of charge for 30 days and costs 60 USD afterwards. Presets from an already installed v4 will be retained.
2. Download and install the [SWS Extension](http://www.sws-extension.org/). Without this, many Ultraschall features unfortunately won't work.
3. Launch Reaper and drag our `Ultraschall_2.0.ReaperConfigZip` into Reaper's main window. **WARNING:** If you have adjusted settings before, we recommend to export them via the `Preferences | General | Export Configuration…` menu **before** importing Ultraschall's configuration. Our distribution overwrites a large number of settings without further prompts.
4. Because we weren't yet able to implement Windows versions of several advanced Ultraschall features (virtual sound cards), the Ultraschall Hub installation can be skipped.
5. A Windows version of our Soundboard is in the works.
