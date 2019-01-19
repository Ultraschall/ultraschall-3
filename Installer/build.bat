@echo off

echo **********************************************************************
echo *                                                                    *
echo *            BUILDING ULTRASCHALL INSTALLER PACKAGE                  *
echo *                                                                    *
echo **********************************************************************

rem Specify name of installer package
set ULTRASCHALL_RELEASE_LABEL=ULTRASCHALL-3.2-preview-3

rem Remove previously created installer package
if exist %ULTRASCHALL_RELEASE_LABEL%.msi del /f /q %ULTRASCHALL_RELEASE_LABEL%.msi

rem Clean-up _payload folder in case the last build went wrong
rmdir /s /q _payload 2>nul
if not errorlevel 0 goto failed
rem Create folder for intermediate data
mkdir _payload
rem Enter _payload folder
pushd _payload

echo Copying Microsoft Visual C++ 2017 CRT...
md vcredist
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Redist\MSVC\14.16.27012\MergeModules\Microsoft_VC141_CRT_x64.msm" vcredist > nul
if not errorlevel 0 goto failed
echo Done.

echo Copying Ultraschall Theme...
mkdir theme
copy ..\..\Themes\Ultraschall_3.1_WIN.ReaperConfigZip theme\Ultraschall_3.1.ReaperConfigZip > nul
if not errorlevel 0 goto failed
echo Done.

echo Copying Ultraschall Add-ons...
mkdir add-ons
copy "..\..\Docs\Keymap.pdf" "add-ons\Ultraschall Keyboard Layout.pdf" > nul
if not errorlevel 0 goto failed
copy "..\..\Docs\Keymap.pptx" "add-ons\Ultraschall Keyboard Layout.pptx" > nul
if not errorlevel 0 goto failed
copy "..\..\Resources\Ultraschall App-Icon.png" "add-ons\Ultraschall App-Icon.png" > nul
if not errorlevel 0 goto failed
copy "..\..\Resources\Ultraschall Webbanner.pdf" "add-ons\Ultraschall Webbanner.pdf" > nul
if not errorlevel 0 goto failed
copy "..\..\Resources\Ultraschall Webbanner 400px.png" "add-ons\Ultraschall Webbanner 400px.png" > nul
if not errorlevel 0 goto failed
copy "..\..\Resources\Ultraschall Webbanner 800px.png" "add-ons\Ultraschall Webbanner 800px.png" > nul
if not errorlevel 0 goto failed
copy "..\..\Resources\Ultraschall Webbanner 2000px.jpg" "add-ons\Ultraschall Webbanner 2000px.jpg" > nul
if not errorlevel 0 goto failed
echo Done.

echo Building Ultraschall documentation files...
mkdir resources
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\README.html ..\..\README.md
if not errorlevel 0 goto failed
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\INSTALL.html ..\..\INSTALL.md
if not errorlevel 0 goto failed
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\CHANGELOG.html ..\..\CHANGELOG.md
if not errorlevel 0 goto failed
echo Done.

echo Building Ultraschall REAPER Plug-in...
md plug-in
pushd plug-in
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Release ..\..\..\Plugin > nul
if not errorlevel 0 goto failed
cmake --build . --target reaper_ultraschall --config Release -j > nul
if not errorlevel 0 goto failed
popd
echo Done.

rem Leave _payload folder
popd

echo Building installer package...
candle -nologo -arch x64 -out _payload\%ULTRASCHALL_RELEASE_LABEL%.wixobj Scripts\distribution.wxs
if not errorlevel 0 goto failed
light -nologo -sw1076 -ext WixUIExtension -cultures:en-us -spdb _payload\%ULTRASCHALL_RELEASE_LABEL%.wixobj -out %ULTRASCHALL_RELEASE_LABEL%.msi
if not errorlevel 0 goto failed
echo Done.

rem Clean-up if build completed successfully
rd /s /q _payload
set ULTRASCHALL_RELEASE_LABEL=
goto end

:failed
echo !!! FAILURE !!!
goto end

:end
echo .
