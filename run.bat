@echo off
echo Bienvenido a la Estación Terrena

echo Desplegando Servidor...
start /B python backend\main.py

echo Desplegando Frontend...
cd fronted
start /B node index.js
cd ..

echo Servidor y frontend corriendo en segundo plano.
echo.
echo Presiona cualquier tecla para detenerlos...
pause >nul

echo Cerrando procesos...
taskkill /F /IM python.exe
taskkill /F /IM node.exe
echo Servidor detenido.

pause
