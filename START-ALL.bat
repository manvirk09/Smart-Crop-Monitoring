@echo off
setlocal
cd /d "%~dp0"

echo ================================================
echo SMART CROP MONITORING - START ALL
 echo ================================================
echo.

echo Starting Python bridge...
start "Smart Crop Bridge" cmd /k python bridge.py

timeout /t 2 /nobreak >nul

echo Starting dashboard web server...
start "Smart Crop Dashboard Server" cmd /k python -m http.server 8080

timeout /t 2 /nobreak >nul

echo Opening dashboard...
start "" "http://localhost:8080/Smart-Crop-Dashboard-SENSOR.html"

echo.
echo Wokwi must still be started separately in VS Code.
echo Keep all three windows running during the live demo.
echo.
pause
