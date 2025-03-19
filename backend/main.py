from flask import Flask
from flask_socketio import SocketIO
import threading
import random as rd
import time
import json

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

#Envio de datos 

def send_data():
    t = 1
    i = 0
    while True:
        data = {
            "altura": {
                "valor": rd.normalvariate(100,0.5),
                "tiempo": time.time() 
            }
        }
        i += 1
        socketio.emit('send_data', data)
        time.sleep(t)


threading.Thread(target=send_data, daemon=True).start()

# Evento para recibir datos desde el cliente y reenviarlos a todos los clientes conectados
@socketio.on('send_data')
def handle_send_data(data):
    print(f"Datos recibidos: {data}")

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=3000, debug=True)


