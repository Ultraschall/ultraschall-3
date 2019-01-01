@echo off

if exist "build" (
    rd /s /q build 2> nul
    rd /s /q build 2> nul
    rd /s /q build 2> nul
)

if exist "build" (
    echo "Clean failed."
)
