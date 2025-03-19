#include <stdio.h>
#include "protocol.h"

void testMPL() {
    printf("\nTesting MPL Serialization & Deserialization\n");

    MPL originalMPL;
    originalMPL.hd = {MPLt, 2, 1, 512};
    originalMPL.mpl = {1013.25, 100.5, 25.3};

    uint8_t buffer[HEADER_SIZE + MPL_DATA_SIZE] = {0};
    Protocol::packMPL(buffer, originalMPL);

    MPL unpackedMPL = Protocol::unpackMPL(buffer);

    printf("Original MPL Data: Pressure: %.2f, Altitude: %.2f, Temperature: %.2f\n",
           originalMPL.mpl.pressure, originalMPL.mpl.altitude, originalMPL.mpl.temperature);

    printf("Unpacked MPL Data: Pressure: %.2f, Altitude: %.2f, Temperature: %.2f\n",
           unpackedMPL.mpl.pressure, unpackedMPL.mpl.altitude, unpackedMPL.mpl.temperature);
}

void testBNO() {
    printf("\nTesting BNO Serialization & Deserialization\n");
    
    BNO originalBNO;
    originalBNO.hd = (HEADER){BNOt, 1, 0, 1024};
    originalBNO.bno = (BNO_DATA){100, 200, -300, 400, -500, 600, -700, 800, -900};
    
    uint8_t buffer[HEADER_SIZE + BNO_DATA_SIZE] = {0};
    Protocol::packBNO(buffer, originalBNO);
    
    BNO unpackedBNO = Protocol::unpackBNO(buffer);
    
    printf("Original BNO Data: \n");
    printf("Ax: %d, Ay: %d, Az: %d\n", originalBNO.bno.ax, originalBNO.bno.ay, originalBNO.bno.az);
    printf("Gx: %d, Gy: %d, Gz: %d\n", originalBNO.bno.gx, originalBNO.bno.gy, originalBNO.bno.gz);
    printf("Mx: %d, My: %d, Mz: %d\n", originalBNO.bno.mx, originalBNO.bno.my, originalBNO.bno.mz);
    
    printf("Unpacked BNO Data: \n");
    printf("Ax: %d, Ay: %d, Az: %d\n", unpackedBNO.bno.ax, unpackedBNO.bno.ay, unpackedBNO.bno.az);
    printf("Gx: %d, Gy: %d, Gz: %d\n", unpackedBNO.bno.gx, unpackedBNO.bno.gy, unpackedBNO.bno.gz);
    printf("Mx: %d, My: %d, Mz: %d\n", unpackedBNO.bno.mx, unpackedBNO.bno.my, unpackedBNO.bno.mz);
}

void testTLM() {
    printf("\nTesting TLM Serialization & Deserialization\n");

    TLM originalTLM;
    originalTLM.hd = {TLMt, 3, 0, 1024};
    originalTLM.tlm = {1623456789, -12.3456, 45.6789, 300.0,
                        0.5, -0.2, 0.1, 9.81, 0.0, -9.81,
                        1015.5, 24.7, 3.7, true};

    uint8_t buffer[HEADER_SIZE + TLM_DATA_SIZE] = {0};
    Protocol::packTLM(buffer, originalTLM);

    TLM unpackedTLM = Protocol::unpackTLM(buffer);

    printf("Original TLM Data: Timestamp: %lu, Latitude: %.6f, Longitude: %.6f, Altitude: %.2f, Pressure: %.2f, Temp: %.2f\n",
           originalTLM.tlm.timestamp, originalTLM.tlm.latitude, originalTLM.tlm.longitude,
           originalTLM.tlm.altitude, originalTLM.tlm.pressure, originalTLM.tlm.temperature);

    printf("Unpacked TLM Data: Timestamp: %lu, Latitude: %.6f, Longitude: %.6f, Altitude: %.2f, Pressure: %.2f, Temp: %.2f\n",
           unpackedTLM.tlm.timestamp, unpackedTLM.tlm.latitude, unpackedTLM.tlm.longitude,
           unpackedTLM.tlm.altitude, unpackedTLM.tlm.pressure, unpackedTLM.tlm.temperature);
}

int main() {
    printf("Tamaño de HEADER: %lu bytes. Constante: %lu bytes\n", sizeof(HEADER), HEADER_SIZE);
    printf("Tamaño de MPL_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(MPL_DATA), MPL_DATA_SIZE);
    printf("Tamaño de MPL: %lu bytes\n", sizeof(MPL));
    printf("Tamaño de TLM_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(TLM_DATA), TLM_DATA_SIZE);
    printf("Tamaño de TLM: %lu bytes\n", sizeof(TLM));
    printf("Tamaño de BNO_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(BNO_DATA), BNO_DATA_SIZE);
    printf("Tamaño de BNO: %lu bytes\n", sizeof(BNO));

    testMPL();
    testBNO();
    testTLM();

    return 0;
}
