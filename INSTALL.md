# Installation instructions for Ultraschall 3.1

The Ultraschall installation comprises **three mandatory steps (Windows: four)**.
We also explain these steps in a separate [screencast video](https://youtu.be/RTshDTPBMes) in German language.

---

# macOS 10.11 or above

# 1.

### Update / Install REAPER

The Ultraschall open-source project is an extension for the commercially available REAPER audio production software. Ultraschall 3.1 is only compatible to REAPER version 5.70.

[**Download REAPER version v5.70 OS X 64-bit**](http://www.reaper.fm/files/5.x/reaper570_x86_64.dmg)

* Download and open the `.dmg`, and install REAPER or update to version 5.70 respectively.
* Using any other REAPER version will lead to the Ultraschall plugin being deactivated and not being launched. We strongly advise you NOT to update REAPER manually to any other version than 5.70.
* The test version of REAPER is _fully functional for 60 days_ and costs US$ 60 afterwards.

# 2.

### Download Ultraschall and launch the Ultraschall installer

Download our Ultraschall 3.1 distribution and open the `.dmg` file:

[**Download Ultraschall 3.1**](http://url.ultraschall-podcast.de/us31)

* In the new window, run and complete the `Ultraschall-3.1.pkg` installation program.
* **Caution:** Should you experience an error message at the end of the installation routine, please restart macOS and run the Installer again.
* If you launch REAPER now, you would be presented with a couple of nice error messages – so **rather proceed** to step 3:

# 3.

### Install REAPER Ultraschall Configuration

* Launch REAPER. A warning about the theme not being installed or being outdated will be shown.
* Now drag the file `Ultraschall_3.1.ReaperConfigZip` into the **open REAPER main window** and click `Import`.

# 4.

### Verify Success of the Installation

* REAPER will restart automatically after step 3.
* In the new Ultraschall welcome screen click on “Details” and check that all components have been installed correctly and no more error messages appear upon launch.
* Error messages upon launch will notify you that either the plugin (step 2) or theme (step 3) have not been installed correctly. Ultraschall will only work when **both** components have been installed. Should you experience such error messages, please repeat steps 2 and 3.
* Should you experience further error messages please verify that you have REAPER version 5.70 installed (step 1). If in doubt, re-install REAPER.
* It may also help to restart your computer and run the `First Aid` option in the macOS Disk Utility application.
* In case of persisting issues or when you want to update an outdated version of Ultraschall prior to 2.0 we recommend to run the scripts `Uninstall.command` and `Remove legacy audio devices.commend` provided in the .dmg and subsequently restart your computer. After restart please repeat steps 1 to 3.
  Should _any of these measures_ fail, you can ask for help in our user forum: [Ultraschall at Sendegate](https://sendegate.de/c/ultraschall)
* We recommend you watch the release screencast in our [Tutorials area](http://ultraschall.fm/tutorials/) to find out about the new features.

---

### Optional - Install UltraschallHub

In case you want to use purely software-defined N-1 audio-routing for Skype recording, installing our proprietary UltraschallHub audio devices is a prerequisite.

* Run `UltraschallHub.pkg` from the `.dmg` window.
* Restart your computer. The new audio devices should now be present in the macOS Audio MIDI Setup.
  This step is _not required_ for using StudioLink, StudioLink OnAir or the Ultraschall Soundboard.

---

# Windows Version 7 or above

# 1.

### Update / Install REAPER

The Ultraschall open-source project is an extension for the commercially available REAPER audio production software. Ultraschall 3.1 is only compatible to REAPER version 5.70.

[**Download REAPER version v5.70 Windows 64-bit**](http://www.reaper.fm/files/5.x/reaper570_x64-install.exe)

* Download the `.exe`, and install REAPER or update to version 5.70 respectively.
* Using any other REAPER version will lead to the Ultraschall plugin being deactivated and not being launched. We strongly advise you NOT to update REAPER manually to any other version than 5.70.
* The test version of REAPER is _fully functional for 60 days_ and costs US$ 60 afterwards.

# 2.

### Download Ultraschall and launch the Ultraschall installer

Download our Ultraschall 3.1 distribution and open the `.msi` file:

[**Download Ultraschall-3.1.msi (24.1 MB)**](http://url.ultraschall-podcast.de/us31win)

* Run and finish the Installer.
* If you launch REAPER now, you would be presented with a couple of nice error messages – so **rather proceed** to step 3:

# 3.

### Install REAPER Ultraschall Configuration

* Launch REAPER. A warning about the theme not being installed or being outdated will be shown.
* Now drag our `Ultraschall REAPER Theme` from your Windows desktop and drop it into the REAPER main window. Let the import finish. You may delete the file from the Desktop afterwards.

# 4.

### Connect StudioLink and the Ultraschall Soundboard

* Our integrated soundboard for playing jingles etc., StudioLink (as an alternative broadcasting solution to remote Skype recording) and StudioLink OnAir will be installed automatically. After installation you will however notify REAPER on this:
* Go to the menu `Options | Preferences… | Plug-ins/VST`. Now click the `Auto-detect` button in the upper right corner and confirm by clicking `Apply` in the lower right. Close the Preferences again.

# 5.

### Verify Success of the Installation

* REAPER will restart automatically after step 3.
* In the new Ultraschall welcome screen click on “Details” and check that all components have been installed correctly and no more error messages appear upon launch.
* Error messages upon launch will notify you that either the plugin (step 2) or theme (step 3) have not been installed correctly. Ultraschall will only work when **both** components have been installed. Should you experience such error messages, please repeat steps 2 and 3.
* Should you experience further error messages please verify that you have REAPER 64-bit version 5.70 installed (step 1). If in doubt, re-install REAPER.
* Try restarting your computer to solve your issue.
  Should _any of these measures_ fail, you can ask for help in our user forum: [Ultraschall at Sendegate](https://sendegate.de/c/ultraschall)
* We recommend you watch the release screencast in our [Tutorials area](http://ultraschall.fm/tutorials/) to find out about the new features.
