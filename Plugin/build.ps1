$action = ""
if ($args.Count -gt 0) {
    $action = $args[0]
}
if (Get-Command "cmake.exe" -ErrorAction SilentlyContinue) {
    $buildDirectory = "./_build"
    if (Test-Path -PathType Container $buildDirectory) {
        if ($action -eq "--help") {
            Write-Host "Usage: build.ps1 [--clean|--rebuild]"
        }
        elseif ($action -eq "--clean") {
            Push-Location $buildDirectory
            if (Test-Path x64) {
                Remove-Item -Force -Recurse x64
            }
            if (Test-Path reaper_ultraschall) {
                Remove-Item -Force -Recurse reaper_ultraschall
            }
            Pop-Location
        }
        elseif ($action -eq "--rebuild") {
            Push-Location $buildDirectory
            & cmake.exe --build . --clean-first --target reaper_ultraschall --config Debug -j
            if ($LASTEXITCODE -ne 0) {
                Write-Host -ForegroundColor Red  "The cmake build step failed, status = " $LASTEXITCODE
            }
            Pop-Location
        }
        else {
            Push-Location $buildDirectory
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
