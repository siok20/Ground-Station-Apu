#pragma once
#pragma pack(1)
#include <cstdint>
#include <cstring>

// MPL3115a2
//https://github.com/adafruit/Adafruit_MPL3115A2_Library/blob/master/examples/testmpl3115a2/testmpl3115a2.ino

#define HEADER_SIZE 3
#define MPL_DATA_SIZE sizeof(MPL_DATA)
#define TLM_DATA_SIZE sizeof(TLM_DATA)

enum DataFrameType {
    NULLDATA,  // 0
    MPLt,      // 1
    TLMt       // 2
};

// Estructura de encabezado (HEADER)
struct HEADER{
    uint8_t data_type: 3;
    uint8_t state: 2;
    uint8_t reserved: 3;
    uint16_t time;
};


struct MPL_DATA {
    float pressure;
    float altitude;
    float temperature;
};

struct MPL {
    HEADER hd;
    MPL_DATA mpl;
};

struct TLM_DATA {
    unsigned long timestamp;  
    float latitude;          
    float longitude;         
    float altitude;           
    float vx, vy, vz;          
    float ax, ay, az;          
    float pressure;          
    float temperature;       
    float batteryVoltage;    
    bool flightStatus;       
};

struct TLM{
    HEADER hd;
    TLM_DATA tlm;
};

class Protocol{
    public:
    // Empaqueta un HEADER en un buffer
    static void packHeader(uint8_t* buff, const HEADER& header) {
        if (!buff) return; 

        buff[0] = (header.data_type & 0x07) << 5 | (header.state & 0x03) << 3 | (header.reserved & 0x07);
        buff[1] = header.time & 0xFF;
        buff[2] = (header.time >> 8) & 0xFF;
    }

    // Desempaqueta un HEADER desde un buffer
    static HEADER unpackHeader(const uint8_t* buff) {
        HEADER header;
        header.data_type = (buff[0] >> 5) & 0x07;
        header.state = (buff[0] >> 3) & 0x03;
        header.reserved = buff[0] & 0x07;
        header.time = buff[1] | (buff[2] << 8);
        return header;
    }

    // Empaqueta un MPL en un buffer
    static void packMPL(uint8_t* buff, const MPL& packet) {
        packHeader(buff, packet.hd);
        memcpy(buff + HEADER_SIZE, &packet.mpl, MPL_DATA_SIZE);
    }

    // Desempaqueta un MPL desde un buffer
    static MPL unpackMPL(const uint8_t* buff) {
        MPL packet;
        packet.hd = unpackHeader(buff);
        memcpy(&packet.mpl, buff + HEADER_SIZE, MPL_DATA_SIZE);
        return packet;
    }

    // Empaqueta un TLM en un buffer
    static void packTLM(uint8_t* buff, const TLM& packet) {
        packHeader(buff, packet.hd);
        memcpy(buff + HEADER_SIZE, &packet.tlm, TLM_DATA_SIZE);
    }

    // Desempaqueta un TLM desde un buffer
    static TLM unpackTLM(const uint8_t* buff) {
        TLM packet;
        packet.hd = unpackHeader(buff);
        memcpy(&packet.tlm, buff + HEADER_SIZE, TLM_DATA_SIZE);
        return packet;
    }

};