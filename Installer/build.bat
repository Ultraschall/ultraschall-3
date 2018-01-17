@echo off

set ULTRASCHALL_RELEASE_LABEL=Ultraschall-3.1

del /f /q %ULTRASCHALL_RELEASE_LABEL%.msi 2> nul

rem clean-up payload folder in case something went wrong before
rd /s /q Payload 2> nul
md Payload > nul

rem clean-up build folder in case something went wrong before
rd /s /q Build 2> nul
md Build > nul

rem Visual Studio CRT
md Payload\VCRedist > nul
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Redist\MSVC\14.12.25810\MergeModules\Microsoft_VC141_CRT_x64.msm" Payload\VCRedist

rem Resources
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\README.html ..\REAPER\README.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\INSTALL.html ..\REAPER\INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=Payload\CHANGELOG.html ..\REAPER\CHANGELOG.md

copy ..\REAPER\Themes\Ultraschall_3.1_WIN.ReaperConfigZip Payload\Ultraschall_3.1.ReaperConfigZip

rem Ultraschall Add-ons
md Payload\Addons > nul
copy "..\REAPER\Documentation\Keymap.pdf" "Payload\Addons\Ultraschall Keyboard Layout.pdf"
copy "..\REAPER\Documentation\Keymap.pptx" "Payload\Addons\Ultraschall Keyboard Layout.pptx"
copy "..\REAPER\Resources\Ultraschall App-Icon.png" "Payload\Addons\Ultraschall App-Icon.png"
copy "..\REAPER\Resources\Ultraschall Webbanner.pdf" "Payload\Addons\Ultraschall Webbanner.pdf"
copy "..\REAPER\Resources\Ultraschall Webbanner 400px.png" "Payload\Addons\Ultraschall Webbanner 400px.png"
copy "..\REAPER\Resources\Ultraschall Webbanner 800px.png" "Payload\Addons\Ultraschall Webbanner 800px.png"
copy "..\REAPER\Resources\Ultraschall Webbanner 2000px.jpg" "Payload\Addons\Ultraschall Webbanner 2000px.jpg"

rem Build Ultraschall REAPER Plug-in
md Payload\Plugin > nul
pushd ..\REAPER\
call build.bat rebuild release x64
popd
copy ..\REAPER\Plugin\reaper_ultraschall\x64\Release\reaper_ultraschall.dll Payload\Plugin

rem Build Ultraschall Soundboard
pushd ..\Soundboard\
call Build\build_win_plugin.cmd
popd
md Payload\Soundboard > nul
copy ..\Soundboard\Projects\Plugin\Builds\VisualStudio2015\x64\Release\Soundboard64.dll Payload\Soundboard

rem Build installer package
candle -nologo -arch x64 -out Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj Scripts\distribution.wxs
light -nologo -ext WixUIExtension -cultures:en-us -loc Scripts\distribution_en-us.wxl -spdb Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj -out %ULTRASCHALL_RELEASE_LABEL%.msi

rem Clean-up
rd /s /q Build > nul
rd /s /q Payload > nul

