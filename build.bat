rem @echo off

set ULTRASCHALL_RELEASE_LABEL=Ultraschall-2.2-prerelease-6

del /f /q %ULTRASCHALL_RELEASE_LABEL%.msi 2> nul

rem clean-up payload folder in case something went wrong before
rd /s /q Payload 2> nul
md Payload > nul

rem clean-up build folder in case something went wrong before
rd /s /q Build 2> nul
md Build > nul

rem Visual Studio CRT
md Payload\VCRedist > nul
copy "%ProgramFiles(x86)%\Common Files\Merge Modules\Microsoft_VC140_CRT_x64.msm" Payload\VCRedist

rem Resources
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\README.html ..\REAPER\README.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\INSTALL.html ..\REAPER\INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\CHANGELOG.html ..\REAPER\CHANGELOG.md
copy ..\REAPER\Themes\Ultraschall_2.2.ReaperConfigZip Payload\Ultraschall_2.2.ReaperConfigZip

rem Ultraschall Add-ons
md Payload\Addons > nul

copy "..\REAPER\Documentation\Rams Edition Release-Poster.pdf" "Payload\Addons\Rams Edition Release-Poster.pdf"
copy "..\REAPER\Documentation\Rams Edition Release-Poster.png" "Payload\Addons\Rams Edition Release-Poster.png"
copy "..\REAPER\Resources\Ultraschall Colorset.SWSColor" "Payload\Addons\Ultraschall Colorset.SWSColor"
copy "..\REAPER\Resources\Ultraschall Microbanner 80x15.png" "Payload\Addons\Ultraschall Microbanner 80x15.png"
copy "..\REAPER\Resources\Ultraschall Webbanner.png" "Payload\Addons\Ultraschall Webbanner.png"
copy "..\REAPER\Resources\Reaper Splashscreen 2.png" "Payload\Addons\Ultraschall Reaper Splash Screen.png"

rem Build Ultraschall REAPER Plug-in
md Payload\Plugin > nul

pushd ..\REAPER\ 
call build.bat rebuild release x64
popd

copy ..\REAPER\Plugin\reaper_ultraschall\x64\Release\reaper_ultraschall.dll Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_delete_last_marker.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_safemode_start_pause.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_safemode_start_stop.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_set_edit.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_set_edit_past.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_set_marker.lua Payload\Plugin
copy ..\REAPER\Plugin\Scripts\ultraschall_set_namedmarker.lua Payload\Plugin

rem Build Ultraschall Soundboard
md Payload\Soundboard > nul
md Payload\Soundboard\Vst > nul
md Payload\Soundboard\Extras > nul
md Payload\Soundboard\Extras\AudioTemplates > nul
md Payload\Soundboard\Extras\TouchOSC > nul

pushd ..\Soundboard
call Build\build_win2.1.cmd rebuild release x64
popd

copy ..\Soundboard\Projects\Plugin\Builds\VisualStudio2015\x64\Release\Soundboard.dll Payload\Soundboard\Vst
copy ..\Soundboard\Extras\AudioTemplates\Off.wav Payload\Soundboard\Extras
copy ..\Soundboard\Extras\TouchOSC\Soundboard.touchosc Payload\Soundboard\Extras
copy ..\Soundboard\Extras\MIDI.md Payload\Soundboard\Extras
copy ..\Soundboard\Extras\OSC.md Payload\Soundboard\Extras

candle -nologo -arch x64 -out Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj Scripts\distribution.wxs
light -nologo -spdb Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj -out %ULTRASCHALL_RELEASE_LABEL%.msi 

rd /s /q Build > nul
rd /s /q Payload > nul

