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

rem Specify build directory
set ULTRASCHALL_BUILD_DIRECTORY=Build

rem Create folder for intermediate data
if not exist %ULTRASCHALL_BUILD_DIRECTORY% (
    mkdir %ULTRASCHALL_BUILD_DIRECTORY%
)
rem Enter %ULTRASCHALL_BUILD_DIRECTORY% folder
pushd %ULTRASCHALL_BUILD_DIRECTORY%

echo Copying Microsoft Visual C++ 2017 CRT...
if not exist vcredist (
    mkdir vcredist
)
copy "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Preview\VC\Redist\MSVC\14.20.27508\MergeModules\Microsoft_VC141_CRT_x64.msm" vcredist > nul
if not errorlevel 0 goto failed
echo Done.

echo Copying Ultraschall Theme...
if not exist theme (
    mkdir theme
)
copy ..\..\Themes\Ultraschall_3.1_WIN.ReaperConfigZip theme\Ultraschall_3.1.ReaperConfigZip > nul
if not errorlevel 0 goto failed
echo Done.

echo Copying Ultraschall Add-ons...
if not exist add-ons (
    mkdir add-ons
)
copy "..\..\Docs\Release\Keymap.pdf" "add-ons\Ultraschall Keyboard Layout.pdf" > nul
if not errorlevel 0 goto failed
copy "..\..\Docs\Release\Keymap.pptx" "add-ons\Ultraschall Keyboard Layout.pptx" > nul
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
if not exist resources (
    mkdir resources
)
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\README.html ..\..\Docs\Release\README.md
if not errorlevel 0 goto failed
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\INSTALL.html ..\..\Docs\Release\INSTALL.md
if not errorlevel 0 goto failed
pandoc --from=markdown --to=html --standalone --quiet --self-contained --css=..\..\Tools\ultraschall.css --output=resources\CHANGELOG.html ..\..\Docs\Release\CHANGELOG.md
if not errorlevel 0 goto failed
echo Done.

echo Building Ultraschall REAPER Plug-in...
if not exist plug-in (
    mkdir plug-in
)
pushd plug-in
cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 -DCMAKE_BUILD_TYPE=Release ..\..\..\Plugin > nul
if not errorlevel 0 goto failed
cmake --build . --target reaper_ultraschall --config Release -j > nul
if not errorlevel 0 goto failed
popd
echo Done.

rem Leave %ULTRASCHALL_BUILD_DIRECTORY% folder
popd

echo Building installer package...
candle -nologo -arch x64 -out %ULTRASCHALL_BUILD_DIRECTORY%\%ULTRASCHALL_RELEASE_LABEL%.wixobj Scripts\distribution.wxs
if not errorlevel 0 goto failed
light -nologo -sw1076 -ext WixUIExtension -cultures:en-us -spdb %ULTRASCHALL_BUILD_DIRECTORY%\%ULTRASCHALL_RELEASE_LABEL%.wixobj -out %ULTRASCHALL_RELEASE_LABEL%.msi
if not errorlevel 0 goto failed
echo Done.

rem Clean-up if build completed successfully
set ULTRASCHALL_BUILD_DIRECTORY=
set ULTRASCHALL_RELEASE_LABEL=
goto end

:failed
echo !!! FAILURE !!!
goto end

:end
echo .
