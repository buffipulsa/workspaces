@echo off
tasklist /FI "IMAGENAME eq EmmPipe.exe" | findstr /C:"EmmPipe.exe" >nul
if %ERRORLEVEL%==0 (
    taskkill /IM EmmPipe.exe /F
)