//Version MARCH 20th
#ifndef APUSPACE_PROTOCOL_LIBRARY_H
#define APUSPACE_PROTOCOL_LIBRARY_H

#include <stdint.h>

// Tamaño de la cabecera
#define HEADER_SIZE 3
#define BYTE_MASK 255
#define BNO085_SIZE 36
#define SHT31_SIZE 4
#define PANIC_SIZE 1

// Sensores y comandos
enum DataFrameType {
    NULLDATAt, PANIC_BUTTONT, BNO085t, MPL3115A2t, SHT31t, Telemetrumt
};

// Estructura de la cabecera
typedef struct {
    uint8_t data_type;  // Tipo de datos (1 byte)
    uint8_t state;      // Estado (1 byte)
    uint16_t time;      // Tiempo (2 bytes)
} unpk_header;

// Estructura de datos del sensor BNO085
typedef struct {
    int32_t ax, ay, az;
    int32_t gx, gy, gz;
    int32_t mx, my, mz;
} BNO085_Data;

// Paquete completo del sensor BNO085
typedef struct {
    unpk_header header;
    BNO085_Data data;
} BNO085_Packet;

// Estructura de datos del sensor SHT31
typedef struct {
    int16_t temperature;
    int16_t humidity;
} SHT31_Data;

// Paquete completo del sensor SHT31
typedef struct {
    unpk_header header;
    SHT31_Data data;
} SHT31_Packet;

// Estructura de datos del botón de pánico
typedef struct {
    uint8_t emergency_level; // 1 = Advertencia, 2 = Crítico, 3 = Inminente
} PanicButtonData;

// Paquete completo del botón de pánico
typedef struct {
    unpk_header header;
    PanicButtonData data;
} PanicButton_Packet;

class APUPROTOCOL {
public:
    // Creación de encabezado
    static void createHeader(uint8_t buff[], DataFrameType type, uint8_t state, uint16_t time);

    // Paquete BNO085
    static void createBNO085Frame(uint8_t buff[], uint8_t state, uint16_t time,
                                  int32_t ax, int32_t ay, int32_t az,
                                  int32_t gx, int32_t gy, int32_t gz,
                                  int32_t mx, int32_t my, int32_t mz);
    static BNO085_Packet unpackBNO085Frame(const uint8_t buff[]);

    // Paquete SHT31
    static void createSHT31Frame(uint8_t buff[], uint8_t state, uint16_t time, int16_t temp, int16_t humidity);
    static SHT31_Packet unpackSHT31Frame(const uint8_t buff[]);

    // Paquete Panic Button
    static void createPanicButtonFrame(uint8_t buff[], uint8_t state, uint16_t time, uint8_t emergency_level);
    static PanicButton_Packet unpackPanicButtonFrame(const uint8_t buff[]);

    // Desempaquetado de encabezado
    static unpk_header unpackHeader(const uint8_t buff[]);
};

#endif




//VERSION MARCH 14
// #include <stdint.h>

// #define HEADER_SIZE 3
// #define BNO085_SIZE 36

// typedef struct unpk_header {
//     uint8_t data_type;  // Tipo de datos (1 byte)
//     uint8_t state;      // Flags del mensaje (1 byte)
//     uint16_t time;      // Marca de tiempo (2 bytes)
// } unpk_header;

// typedef struct BNO085_Data {
//     int32_t ax, ay, az; // Aceleración (4 bytes)
//     int32_t gx, gy, gz; // Giroscopio (4 bytes)
//     int32_t mx, my, mz; // Magnetómetro (4 bytes)
// } BNO085_Data;

// typedef struct BNO085_Packet {
//     unpk_header header;
//     BNO085_Data data;
// } BNO085_Packet;


// enum DataFrameType {
//     NULLDATAt, panic_buttont, BNO085t, MPL3115A2t,
//     SHT31t, Telemetrumt
// };


// class APUPROTOCOL{
// 	public:
// 		static void createBNO085Frame(uint8_t buff[], char *state, uint16_t time,
//                        int32_t ax, int32_t ay, int32_t az,
//                        int32_t gx, int32_t gy, int32_t gz,
//                        int32_t mx, int32_t my, int32_t mz);
                       
	
// 		static BNO085_Packet unpackBNO085Frame(const uint8_t buff[]);

// 	private:
//     	static void createHeader(uint8_t buff[], DataFrameType type, char *state, uint16_t time);
//     	static unpk_header unpackHeader(const uint8_t buff[]);
// };







