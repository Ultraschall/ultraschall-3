################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

$action = ""
if ($args.Count -gt 0) {
    $action = $args[0]
}
if (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
    $BuildDirectory = "./build"
    if (Test-Path -PathType Container $BuildDirectory) {
        if ($action -eq "--help") {
            Write-Host "Usage: build.ps1 [--clean|--rebuild]"
        }
        elseif ($action -eq "--clean") {
            Push-Location $BuildDirectory
            if (Test-Path x64) {
                Remove-Item -Force -Recurse x64
            }
            if (Test-Path reaper_ultraschall) {
                Remove-Item -Force -Recurse reaper_ultraschall
            }
            Pop-Location
        }
        elseif ($action -eq "--rebuild") {
            Push-Location $BuildDirectory
            & cmake.exe --build . --clean-first --target reaper_ultraschall --config Debug -j
            if ($LASTEXITCODE -ne 0) {
                Write-Host -ForegroundColor Red  "The cmake build step failed, status = " $LASTEXITCODE
            }
            Pop-Location
        }
        else {
            Push-Location $BuildDirectory
            & cmake.exe --build . --target reaper_ultraschall --config Debug -j
            if ($LASTEXITCODE -ne 0) {
                Write-Host -ForegroundColor Red  "The cmake build step failed, status = " $LASTEXITCODE
            }
            Pop-Location
        }
    }
    else {
        Write-Host -ForegroundColor Red  "The build environment hasn't been setup correctly. Run the bootstrap script instead."
    }
}
else {
    Write-Host -ForegroundColor Red  "cmake not found."
}
