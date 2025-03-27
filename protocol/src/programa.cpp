#include "apuspace_protocol.h"
#include <stdint.h>
#include <iostream>
using namespace std;

// Crear cabecera
void APUPROTOCOL::createHeader(uint8_t buff[], DataFrameType type, char *state, uint16_t time) {
    buff[0] = (type << 4) | (*state & 0x0F);
    buff[1] = time >> 8;
    buff[2] = time & 0xFF;
}

// Crear paquete BNO085
void APUPROTOCOL::createBNO085Frame(uint8_t buff[], char *state, uint16_t time,
                                     int32_t ax, int32_t ay, int32_t az,
                                     int32_t gx, int32_t gy, int32_t gz,
                                     int32_t mx, int32_t my, int32_t mz) {
    createHeader(buff, BNO085t, state, time);
    int cnt = HEADER_SIZE;
    int32_t values[] = {ax, ay, az, gx, gy, gz, mx, my, mz};
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < sizeof(int32_t); ++j) {
            buff[cnt + j] = (uint8_t)((values[i] >> (sizeof(int32_t) - j - 1) * 8) & 0xFF);
        }
        cnt += sizeof(int32_t);
    }
}

// Desempaquetar BNO085
BNO085_Packet APUPROTOCOL::unpackBNO085Frame(const uint8_t buff[]) {
    BNO085_Packet packet;
    packet.header = unpackHeader(buff);
    int cnt = HEADER_SIZE;
    int32_t *values[] = {&packet.data.ax, &packet.data.ay, &packet.data.az,
                         &packet.data.gx, &packet.data.gy, &packet.data.gz,
                         &packet.data.mx, &packet.data.my, &packet.data.mz};
    
    for (int i = 0; i < 9; ++i) {
        *values[i] = 0;
        for (int j = 0; j < sizeof(int32_t); ++j) {
            *values[i] = (*values[i] << 8) | buff[cnt + j];
        }
        cnt += sizeof(int32_t);
    }
    return packet;
}

// Crear paquete SHT31
void APUPROTOCOL::createSHT31Frame(uint8_t buff[], uint8_t state, uint16_t time, int16_t temp, int16_t humidity) {
    createHeader(buff, SHT31t, state, time);
    int16_t values[2] = {temp, humidity};
    int cnt = HEADER_SIZE;
    for (int i = 0; i < 2; ++i) {
        buff[cnt++] = (values[i] >> 8) & BYTE_MASK;
        buff[cnt++] = values[i] & BYTE_MASK;
    }
}

// Desempaquetar SHT31
SHT31_Packet APUPROTOCOL::unpackSHT31Frame(const uint8_t buff[]) {
    SHT31_Packet packet;
    packet.header = unpackHeader(buff);
    int cnt = HEADER_SIZE;
    packet.data.temperature = (buff[cnt] << 8) | buff[cnt + 1];
    packet.data.humidity = (buff[cnt + 2] << 8) | buff[cnt + 3];
    return packet;
}

// Crear paquete de botón de pánico
void APUPROTOCOL::createPanicButtonFrame(uint8_t buff[], uint8_t state, uint16_t time, uint8_t emergency_level) {
    createHeader(buff, PANIC_BUTTONT, state, time);
    buff[HEADER_SIZE] = emergency_level;
}

// Desempaquetar botón de pánico
PanicButton_Packet APUPROTOCOL::unpackPanicButtonFrame(const uint8_t buff[]) {
    PanicButton_Packet packet;
    packet.header = unpackHeader(buff);
    packet.data.emergency_level = buff[HEADER_SIZE];
    return packet;
}

// Desempaquetar cabecera
unpk_header APUPROTOCOL::unpackHeader(const uint8_t buff[]) {
    unpk_header header;
    header.data_type = buff[0] >> 4;
    header.state = buff[0] & 0x0F;
    header.time = (buff[1] << 8) | buff[2];
    return header;
}


int main() {
    uint8_t buffer[BNO085_SIZE + HEADER_SIZE] = {0};
    char state = 0x0A;
    uint16_t time = 12345;
    
    // Crear paquete
    APUPROTOCOL::createBNO085Frame(buffer, &state, time, 100, 200, 300, 400, 500, 600, 700, 800, 900);
    
    // Desempaquetar paquete
    BNO085_Packet packet = APUPROTOCOL::unpackBNO085Frame(buffer);
    
    cout << "Tipo de dato: " << (int)packet.header.data_type << endl;
    cout << "Estado: " << (int)packet.header.state << endl;
    cout << "Tiempo: " << packet.header.time << endl;
    cout << "Aceleración: " << packet.data.ax << ", " << packet.data.ay << ", " << packet.data.az << endl;
    cout << "Giroscopio: " << packet.data.gx << ", " << packet.data.gy << ", " << packet.data.gz << endl;
    cout << "Magnetómetro: " << packet.data.mx << ", " << packet.data.my << ", " << packet.data.mz << endl;
    
    return 0;
}



//VERSION MARCH 14
// #include "apuspace_protocol.h"
// #include <stdint.h>
// #include <iostream>
// using namespace std;


// void APUPROTOCOL::createHeader(uint8_t buff[], DataFrameType type, char *state, uint16_t time) {
//     buff[0] = (type << 4) | (*state & 0x0F);
//     buff[1] = time >> 8;
//     buff[2] = time & 0xFF;
// }

// void APUPROTOCOL::createBNO085Frame(uint8_t buff[], char *state, uint16_t time,
//                                      int32_t ax, int32_t ay, int32_t az,
//                                      int32_t gx, int32_t gy, int32_t gz,
//                                      int32_t mx, int32_t my, int32_t mz) {
//     createHeader(buff, BNO085t, state, time);
//     int cnt = HEADER_SIZE;
//     int32_t values[] = {ax, ay, az, gx, gy, gz, mx, my, mz};
    
//     for (int i = 0; i < 9; ++i) {
//         for (int j = 0; j < sizeof(int32_t); ++j) {
//             buff[cnt + j] = (uint8_t)((values[i] >> (sizeof(int32_t) - j - 1) * 8) & 0xFF);
//         }
//         cnt += sizeof(int32_t);
//     }
// }

// BNO085_Packet APUPROTOCOL::unpackBNO085Frame(const uint8_t buff[]) {
//     BNO085_Packet packet;
//     packet.header = unpackHeader(buff);
//     int cnt = HEADER_SIZE;
//     int32_t *values[] = {&packet.data.ax, &packet.data.ay, &packet.data.az,
//                          &packet.data.gx, &packet.data.gy, &packet.data.gz,
//                          &packet.data.mx, &packet.data.my, &packet.data.mz};
    
//     for (int i = 0; i < 9; ++i) {
//         *values[i] = 0;
//         for (int j = 0; j < sizeof(int32_t); ++j) {
//             *values[i] = (*values[i] << 8) | buff[cnt + j];
//         }
//         cnt += sizeof(int32_t);
//     }
//     return packet;
// }

// unpk_header APUPROTOCOL::unpackHeader(const uint8_t buff[]) {
//     unpk_header header;
//     header.data_type = buff[0] >> 4;
//     header.state = buff[0] & 0x0F;
//     header.time = (buff[1] << 8) | buff[2];
//     return header;
// }

// int main() {
//     uint8_t buffer[BNO085_SIZE + HEADER_SIZE] = {0};
//     char state = 0x0A;
//     uint16_t time = 12345;
    
//     // Crear paquete
//     APUPROTOCOL::createBNO085Frame(buffer, &state, time, 100, 200, 300, 400, 500, 600, 700, 800, 900);
    
//     // Desempaquetar paquete
//     BNO085_Packet packet = APUPROTOCOL::unpackBNO085Frame(buffer);
    
//     cout << "Tipo de dato: " << (int)packet.header.data_type << endl;
//     cout << "Estado: " << (int)packet.header.state << endl;
//     cout << "Tiempo: " << packet.header.time << endl;
//     cout << "Aceleración: " << packet.data.ax << ", " << packet.data.ay << ", " << packet.data.az << endl;
//     cout << "Giroscopio: " << packet.data.gx << ", " << packet.data.gy << ", " << packet.data.gz << endl;
//     cout << "Magnetómetro: " << packet.data.mx << ", " << packet.data.my << ", " << packet.data.mz << endl;
    
//     return 0;
// }
