#!/bin/bash
echo "Bienvenido a la Estación Terrena"

echo "Desplegando Servidor..."
python3 backend/main.py & 
SERVER_PID=$!

echo "Desplegando Frontend..."
cd fronted
node index.js &
FRONTEND_PID=$!
cd ..

echo "Servidor y frontend corriendo en segundo plano."
echo
read -p "Presiona Enter para detenerlos..."

echo "Cerrando procesos..."
kill $SERVER_PID $FRONTEND_PID
echo "Servidor detenido."
