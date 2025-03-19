//#ifndef APUSPACE_PROTOCOL_LIBRARY_H
//#define APUSPACE_PROTOCOL_LIBRARY_H

#include <stdint.h>

#define HEADER_SIZE 3
#define BNO085_SIZE 36

typedef struct unpk_header {
    uint8_t data_type;  // Tipo de datos (1 byte)
    uint8_t state;      // Flags del mensaje (1 byte)
    uint16_t time;      // Marca de tiempo (2 bytes)
} unpk_header;

typedef struct BNO085_Data {
    int32_t ax, ay, az; // Aceleración (4 bytes)
    int32_t gx, gy, gz; // Giroscopio (4 bytes)
    int32_t mx, my, mz; // Magnetómetro (4 bytes)
} BNO085_Data;

typedef struct BNO085_Packet {
    unpk_header header;
    BNO085_Data data;
} BNO085_Packet;


enum DataFrameType {
    NULLDATAt, panic_buttont, BNO085t, MPL3115A2t,
    SHT31t, Telemetrumt
};


class APUPROTOCOL{
	public:
		static void createBNO085Frame(uint8_t buff[], char *state, uint16_t time,
                       int32_t ax, int32_t ay, int32_t az,
                       int32_t gx, int32_t gy, int32_t gz,
                       int32_t mx, int32_t my, int32_t mz);
                       
	
		static BNO085_Packet unpackBNO085Frame(const uint8_t buff[]);

	private:
    	static void createHeader(uint8_t buff[], DataFrameType type, char *state, uint16_t time);
    	static unpk_header unpackHeader(const uint8_t buff[]);
};







