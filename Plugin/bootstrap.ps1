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
            Write-Host -ForegroundColor Red  "cmake build step failed, status = " $LASTEXITCODE
        }
    }
    else {
        Write-Host -ForegroundColor Red  "cmake configure step failed, status = " $LASTEXITCODE
    }
    Pop-Location
}
else {
    Write-Host -ForegroundColor Red  "cmake not found."
}
