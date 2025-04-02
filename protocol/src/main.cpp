#include <stdio.h>
#include "apuspace_protocol.h"

void testMPL() {
    printf("\nTesting MPL Serialization & Deserialization\n");

    MPL_Packet originalMPL;
    originalMPL.hd = {MPLt, 2, 1, 512};
    originalMPL.mpl = {1013.25, 100.5, 25.3};

    uint8_t buffer[HEADER_SIZE + MPL_DATA_SIZE] = {0};
    Protocol::packMPL(buffer, originalMPL);

    MPL_Packet unpackedMPL = Protocol::unpackMPL(buffer);

    printf("Original MPL Data: Pressure: %.2f, Altitude: %.2f, Temperature: %.2f\n",
           originalMPL.mpl.pressure, originalMPL.mpl.altitude, originalMPL.mpl.temperature);

    printf("Unpacked MPL Data: Pressure: %.2f, Altitude: %.2f, Temperature: %.2f\n",
           unpackedMPL.mpl.pressure, unpackedMPL.mpl.altitude, unpackedMPL.mpl.temperature);
}

void testBNO() {
    printf("\nTesting BNO Serialization & Deserialization\n");
    
    BNO085_Packet originalBNO;
    originalBNO.hd = (HEADER){BNOt, 1, 0, 1024};
    originalBNO.bno = (BNO_DATA){100, 200, -300, 400, -500, 600, -700, 800, -900};
    
    uint8_t buffer[HEADER_SIZE + BNO_DATA_SIZE] = {0};
    Protocol::packBNO(buffer, originalBNO);
    
    BNO085_Packet unpackedBNO = Protocol::unpackBNO(buffer);
    
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

    TLM_Packet originalTLM;
    originalTLM.hd = {TLMt, 3, 0, 1024};
    originalTLM.tlm = {1623456789, -12.3456, 45.6789, 300.0,
                        0.5, -0.2, 0.1, 9.81, 0.0, -9.81,
                        1015.5, 24.7, 3.7, true};

    uint8_t buffer[HEADER_SIZE + TLM_DATA_SIZE] = {0};
    Protocol::packTLM(buffer, originalTLM);

    TLM_Packet unpackedTLM = Protocol::unpackTLM(buffer);

    printf("Original TLM Data: Timestamp: %lu, Latitude: %.6f, Longitude: %.6f, Altitude: %.2f, Pressure: %.2f, Temp: %.2f\n",
           originalTLM.tlm.timestamp, originalTLM.tlm.latitude, originalTLM.tlm.longitude,
           originalTLM.tlm.altitude, originalTLM.tlm.pressure, originalTLM.tlm.temperature);

    printf("Unpacked TLM Data: Timestamp: %lu, Latitude: %.6f, Longitude: %.6f, Altitude: %.2f, Pressure: %.2f, Temp: %.2f\n",
           unpackedTLM.tlm.timestamp, unpackedTLM.tlm.latitude, unpackedTLM.tlm.longitude,
           unpackedTLM.tlm.altitude, unpackedTLM.tlm.pressure, unpackedTLM.tlm.temperature);
}

void testSHT() {
    printf("\nTesting SHT Serialization & Deserialization\n");

    SHT31_Packet originalSHT;
    originalSHT.hd = {SHTt, 1, 0, 200};
    originalSHT.sht = {2500, 6000}; // Temperatura en centésimas de grado (25.00°C), humedad 60.00%

    uint8_t buffer[HEADER_SIZE + SHT_DATA_SIZE] = {0};
    Protocol::packSHT(buffer, originalSHT);

    SHT31_Packet unpackedSHT = Protocol::unpackSHT(buffer);

    printf("Original SHT Data: Temperature: %.2f, Humidity: %.2f\n",
           originalSHT.sht.temperature / 100.0, originalSHT.sht.humidity / 100.0);

    printf("Unpacked SHT Data: Temperature: %.2f, Humidity: %.2f\n",
           unpackedSHT.sht.temperature / 100.0, unpackedSHT.sht.humidity / 100.0);
}

void testPanicButton() {
    printf("\nTesting Panic Button Serialization & Deserialization\n");

    PanicButton_Packet originalPanic;
    originalPanic.hd = {PANIC_BUTTON, 0, 0, 150}; 
    originalPanic.pbutton = {2}; // Nivel de emergencia 2 (Crítico)

    uint8_t buffer[HEADER_SIZE + PanicButton_DATA_SIZE] = {0};
    Protocol::packPanicButton(buffer, originalPanic);

    PanicButton_Packet unpackedPanic = Protocol::unpackPanicButton(buffer);

    printf("Original Panic Button Data: Emergency Level: %d\n", originalPanic.pbutton.emergency_level);
    printf("Unpacked Panic Button Data: Emergency Level: %d\n", unpackedPanic.pbutton.emergency_level);
}

int main() {
    printf("Tamaño de HEADER: %lu bytes. Constante: %lu bytes\n", sizeof(HEADER), HEADER_SIZE);
    printf("Tamaño de MPL_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(MPL_DATA), MPL_DATA_SIZE);
    printf("Tamaño de MPL: %lu bytes\n", sizeof(MPL_DATA));
    printf("Tamaño de TLM_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(TLM_DATA), TLM_DATA_SIZE);
    printf("Tamaño de TLM: %lu bytes\n", sizeof(TLM_DATA));
    printf("Tamaño de BNO_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(BNO_DATA), BNO_DATA_SIZE);
    printf("Tamaño de BNO: %lu bytes\n", sizeof(BNO_DATA));

    printf("Tamaño de SHT_DATA: %lu bytes. Constante: %lu bytes\n", sizeof(SHT31_DATA), SHT_DATA_SIZE);
    printf("Tamaño de SHT: %lu bytes\n", sizeof(SHT31_DATA));

    printf("Tamaño de Panic Button: %lu bytes. Constante: %lu bytes\n", sizeof(PanicButton_DATA), PanicButton_DATA_SIZE);
    printf("Tamaño de Panic Button: %lu bytes\n", sizeof(PanicButton_DATA));

    testMPL();
    testBNO();
    testTLM();

    testSHT();
    testPanicButton();


    return 0;
}
