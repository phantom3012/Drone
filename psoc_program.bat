@echo off
REM ========================================================================
REM == PSoC Creator Build and Program Automation Script
REM ========================================================================

REM --- Step 1: Configuration ---
REM Set variables for all required paths. Modify these for your system.
set PSOC_CREATOR_PATH="E:\Acads\UWM\PSoC Creator\4.4\PSoC Creator\bin"
set PSOC_PROGRAMMER_PATH="E:\Acads\UWM\Programmer"
set WORKSPACE_FILE="E:\Acads\UWM\Summer 25\PathController\PathController.cydsn\PathController-000.cywrk"
set PROJECT_NAME=PathController
set BUILD_CONFIG=Debug

REM This is the path to the CLI script for PPCli.exe
set CLI_SCRIPT_FILE="E:\Acads\UWM\Summer 25\prog_psoc.py"

REM --- Step 1.5: Parse Arguments ---
set PROGRAM_DEVICE=0
if /I "%1"=="program" (
    set PROGRAM_DEVICE=1
)

echo.
echo [INFO] Starting PSoC Build and Program process...
echo [INFO] Workspace: %WORKSPACE_FILE%
echo [INFO] Configuration: %BUILD_CONFIG%
echo.

REM --- Step 2: Build the Project ---
echo Building project...
%PSOC_CREATOR_PATH%\cyprjmgr.exe -wrk %WORKSPACE_FILE% -build -c %BUILD_CONFIG%

REM --- Step 3: Critical Error Checking ---
REM Check the exit code of the last command (cyprjmgr.exe).
REM A non-zero exit code indicates a build failure.
IF ERRORLEVEL 1 (
    echo.
    echo Build failed. Halting script.
    goto :eof
)

echo Build completed successfully.
echo.

REM --- Step 4: Program the Device (optional) ---
if "%PROGRAM_DEVICE%"=="1" (
    echo Programming device using script: %CLI_SCRIPT_FILE%
    python prog_psoc.py

    IF ERRORLEVEL 1 (
        echo.
        echo Programming failed.
        goto :eof
    ) ELSE (
        echo.
        echo Device programmed successfully.
        echo.
    )
) else (
    echo Skipping programming step.
    echo.
)

REM --- Step 5: Final Status ---
echo [INFO] Automation script finished.