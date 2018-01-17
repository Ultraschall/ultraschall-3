@echo off

set ULTRASCHALL_RELEASE_LABEL=ULTRASCHALL-3.1.1-alpha1

del /f /q %ULTRASCHALL_RELEASE_LABEL%.msi 2> nul

rem clean-up payload folder in case something went wrong before
rd /s /q payload 2> nul
md payload > nul

rem clean-up build folder in case something went wrong before
rd /s /q Build 2> nul
md Build > nul

rem Visual Studio CRT
md payload\VCRedist > nul
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Redist\MSVC\14.12.25810\MergeModules\Microsoft_VC141_CRT_x64.msm" payload\VCRedist

rem Resources
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=payload\README.html ..\README.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=payload\INSTALL.html ..\REAPER\INSTALL.md
pandoc --from=markdown --to=html --standalone --self-contained --css=..\REAPER\Tools\ultraschall.css --output=payload\CHANGELOG.html ..\REAPER\CHANGELOG.md

copy ..\REAPER\Themes\Ultraschall_3.1_WIN.ReaperConfigZip payload\Ultraschall_3.1.ReaperConfigZip

rem Ultraschall Add-ons
md payload\Addons > nul
copy "..\REAPER\Documentation\Keymap.pdf" "payload\Addons\Ultraschall Keyboard Layout.pdf"
copy "..\REAPER\Documentation\Keymap.pptx" "payload\Addons\Ultraschall Keyboard Layout.pptx"
copy "..\REAPER\Resources\Ultraschall App-Icon.png" "payload\Addons\Ultraschall App-Icon.png"
copy "..\REAPER\Resources\Ultraschall Webbanner.pdf" "payload\Addons\Ultraschall Webbanner.pdf"
copy "..\REAPER\Resources\Ultraschall Webbanner 400px.png" "payload\Addons\Ultraschall Webbanner 400px.png"
copy "..\REAPER\Resources\Ultraschall Webbanner 800px.png" "payload\Addons\Ultraschall Webbanner 800px.png"
copy "..\REAPER\Resources\Ultraschall Webbanner 2000px.jpg" "payload\Addons\Ultraschall Webbanner 2000px.jpg"

rem Build Ultraschall REAPER Plug-in
md payload\Plugin > nul
pushd ..\REAPER\
call build.bat build release x64
popd
copy ..\REAPER\Plugin\reaper_ultraschall\x64\Release\reaper_ultraschall.dll payload\Plugin

rem Build installer package
candle -nologo -arch x64 -out Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj Scripts\distribution.wxs
light -nologo -ext WixUIExtension -cultures:en-us -loc Scripts\distribution_en-us.wxl -spdb Build\%ULTRASCHALL_RELEASE_LABEL%.wixobj -out %ULTRASCHALL_RELEASE_LABEL%.msi

rem Clean-up
rd /s /q Build > nul
rd /s /q payload > nul

