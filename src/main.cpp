#include <iostream>
#include "data.h"

void testMPL() {
    std::cout << "\nTesting MPL Serialization & Deserialization" << std::endl;
    
    MPL originalMPL;
    originalMPL.hd = {MPLt, 2, 1, 512};
    originalMPL.mpl = {1013.25, 100.5, 25.3};
    
    uint8_t buffer[HEADER_SIZE + MPL_DATA_SIZE] = {0};
    Protocol::packMPL(buffer, originalMPL);
    
    MPL unpackedMPL = Protocol::unpackMPL(buffer);
    
    std::cout << "Original MPL Data: "
              << "Pressure: " << originalMPL.mpl.pressure
              << ", Altitude: " << originalMPL.mpl.altitude
              << ", Temperature: " << originalMPL.mpl.temperature << std::endl;
    
    std::cout << "Unpacked MPL Data: "
              << "Pressure: " << unpackedMPL.mpl.pressure
              << ", Altitude: " << unpackedMPL.mpl.altitude
              << ", Temperature: " << unpackedMPL.mpl.temperature << std::endl;
}

void testTLM() {
    std::cout << "\nTesting TLM Serialization & Deserialization" << std::endl;
    
    TLM originalTLM;
    originalTLM.hd = {TLMt, 3, 0, 1024};
    originalTLM.tlm = {1623456789, -12.3456, 45.6789, 300.0,
                        0.5, -0.2, 0.1, 9.81, 0.0, -9.81,
                        1015.5, 24.7, 3.7, true};
    
    uint8_t buffer[HEADER_SIZE + TLM_DATA_SIZE] = {0};
    Protocol::packTLM(buffer, originalTLM);
    
    TLM unpackedTLM = Protocol::unpackTLM(buffer);
    
    std::cout << "Original TLM Data: "
              << "Timestamp: " << originalTLM.tlm.timestamp
              << ", Latitude: " << originalTLM.tlm.latitude
              << ", Longitude: " << originalTLM.tlm.longitude
              << ", Altitude: " << originalTLM.tlm.altitude
              << ", Pressure: " << originalTLM.tlm.pressure
              << ", Temp: " << originalTLM.tlm.temperature << std::endl;
    
    std::cout << "Unpacked TLM Data: "
              << "Timestamp: " << unpackedTLM.tlm.timestamp
              << ", Latitude: " << unpackedTLM.tlm.latitude
              << ", Longitude: " << unpackedTLM.tlm.longitude
              << ", Altitude: " << unpackedTLM.tlm.altitude
              << ", Pressure: " << unpackedTLM.tlm.pressure
              << ", Temp: " << unpackedTLM.tlm.temperature << std::endl;
}

int main() {
    std::cout << "Tamaño de HEADER: " << sizeof(HEADER) << " bytes\n";
    std::cout << "Tamaño de MPL_DATA: " << sizeof(MPL_DATA) << " bytes\n";
    std::cout << "Tamaño de MPL: " << sizeof(MPL) << " bytes\n";
    std::cout << "Tamaño de TLM_DATA: " << sizeof(TLM_DATA) << " bytes\n";
    std::cout << "Tamaño de TLM: " << sizeof(TLM) << " bytes\n";

    testMPL();
    testTLM();

    return 0;
}
