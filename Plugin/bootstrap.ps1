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

if (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
    $buildDirectory = "./_build"
    if (Test-Path -PathType Container $buildDirectory) {
        Remove-Item -Force -Recurse $buildDirectory
    }
    New-Item -ItemType Directory -Force -Path $buildDirectory | Out-Null
    Push-Location $buildDirectory
    & cmake.exe -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug -Thost=x64 ../
    if ($LASTEXITCODE -eq 0) {
        & cmake.exe --build . --target reaper_ultraschall --config Debug -j
        if ($LASTEXITCODE -ne 0) {
            Write-Host -ForegroundColor Red  "The cmake build step failed, status = " $LASTEXITCODE
        }
    }
    else {
        Write-Host -ForegroundColor Red  "The cmake configure step failed, status = " $LASTEXITCODE
    }
    Pop-Location
}
else {
    Write-Host -ForegroundColor Red  "cmake not found."
}
