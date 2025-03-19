#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <string.h>

// MPL3115a2
//https://github.com/adafruit/Adafruit_MPL3115A2_Library/blob/master/examples/testmpl3115a2/testmpl3115a2.ino

#define HEADER_SIZE sizeof(HEADER)

#define BNO_DATA_SIZE sizeof(BNO_DATA)
#define MPL_DATA_SIZE sizeof(MPL_DATA)

#define TLM_DATA_SIZE sizeof(TLM_DATA)

enum DataFrameType {
    NULLDATA,      // 0
    PANIC_BUTTON,  // 1
    BNOt,           // 2
    MPLt,          // 3
    SHTt,           // 4
    TLMt           // 5
};

// Estructura de encabezado (HEADER)
typedef struct __attribute__((packed)){
    uint8_t data_type: 3; // tipo de dato            3 bits \-
    uint8_t state: 2;     // estado del sensor       2 bits  |-> 1byte
    uint8_t reserved: 3;  // bits reservadosdel byte 3 bits /-
    uint16_t time;        // tiempo de registro      2 bytes  
} HEADER;

// Estructura de dato del sensor BNO
typedef struct __attribute__((packed)) {
    int32_t ax, ay, az; // Aceleración (4 bytes)
    int32_t gx, gy, gz; // Giroscopio (4 bytes)
    int32_t mx, my, mz; // Magnetómetro (4 bytes)
} BNO_DATA;

typedef struct __attribute__((packed)) {
    HEADER hd;
    BNO_DATA bno;
} BNO;

// Estructura de datos del sensor MPL
typedef struct __attribute__((packed)) {
    float pressure;  
    float altitude;
    float temperature;
}MPL_DATA;

typedef struct __attribute__((packed))  {
    HEADER hd;
    MPL_DATA mpl;
}MPL;

// Estrucutra para los datos del Telemetrum
typedef struct __attribute__((packed)) {
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
}TLM_DATA;

typedef struct __attribute__((packed)){
    HEADER hd;
    TLM_DATA tlm;
}TLM;

class Protocol{
    public:
    // Empaqueta un HEADER en un buffer
    static void packHeader(uint8_t* buff, const HEADER& header);

    // Desempaqueta un HEADER desde un buffer
    static HEADER unpackHeader(const uint8_t* buff);

    // Empaqueta un BNO en un buffer
    static void packBNO(uint8_t* buff, const BNO& packet);

    // Desempaqueta un BNO desde un buffer
    static BNO unpackBNO(const uint8_t* buff);

    // Empaqueta un MPL en un buffer
    static void packMPL(uint8_t* buff, const MPL& packet);

    // Desempaqueta un MPL desde un buffer
    static MPL unpackMPL(const uint8_t* buff);

    // Empaqueta un TLM en un buffer
    static void packTLM(uint8_t* buff, const TLM& packet);

    // Desempaqueta un TLM desde un buffer
    static TLM unpackTLM(const uint8_t* buff);

};

#endif