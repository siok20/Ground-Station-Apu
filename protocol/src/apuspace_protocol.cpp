#include "apuspace_protocol.h"

void Protocol::packHeader(uint8_t* buff, const HEADER& header) {
    if (!buff) return; 

    buff[0] = (header.data_type & 0x07) << 5 | (header.state & 0x03) << 3 | (header.reserved & 0x07);
    buff[1] = header.time & 0xFF;
    buff[2] = (header.time >> 8) & 0xFF;
}

HEADER Protocol::unpackHeader(const uint8_t* buff) {
    if (!buff) return HEADER{NULLDATA, 0, 0, 1024}; 

    HEADER header;
    header.data_type = (buff[0] >> 5) & 0x07;
    header.state = (buff[0] >> 3) & 0x03;
    header.reserved = buff[0] & 0x07;
    header.time = buff[1] | (buff[2] << 8);
    return header;
}

void Protocol::packBNO(uint8_t* buff, const BNO085_Packet& packet){
    if (!buff) return; 

    packHeader(buff, packet.hd);
    memcpy(buff + HEADER_SIZE, &packet.bno, BNO_DATA_SIZE);
}

BNO085_Packet Protocol::unpackBNO(const uint8_t* buff){
    BNO085_Packet packet;
    packet.hd = unpackHeader(buff);
    memcpy(&packet.bno, buff + HEADER_SIZE, BNO_DATA_SIZE);
    return packet;
}

void Protocol::packMPL(uint8_t* buff, const MPL_Packet& packet) {
    if (!buff) return; 

    packHeader(buff, packet.hd);
    memcpy(buff + HEADER_SIZE, &packet.mpl, MPL_DATA_SIZE);
}

MPL_Packet Protocol::unpackMPL(const uint8_t* buff) {
    MPL_Packet packet;
    packet.hd = unpackHeader(buff);
    memcpy(&packet.mpl, buff + HEADER_SIZE, MPL_DATA_SIZE);
    return packet;
}

void Protocol::packTLM(uint8_t* buff, const TLM_Packet& packet) {
    if (!buff) return; 

    packHeader(buff, packet.hd);
    memcpy(buff + HEADER_SIZE, &packet.tlm, TLM_DATA_SIZE);
}

TLM_Packet Protocol::unpackTLM(const uint8_t* buff) {
    TLM_Packet packet;
    packet.hd = unpackHeader(buff);
    memcpy(&packet.tlm, buff + HEADER_SIZE, TLM_DATA_SIZE);
    return packet;
}

void Protocol::packSHT(uint8_t* buff, const SHT31_Packet& packet){
    if (!buff) return; 

    packHeader(buff, packet.hd);
    memcpy(buff + HEADER_SIZE, &packet.sht, SHT_DATA_SIZE);
}

SHT31_Packet Protocol::unpackSHT(const uint8_t* buff){
    SHT31_Packet packet;
    packet.hd = unpackHeader(buff);
    memcpy(&packet.sht, buff + HEADER_SIZE, SHT_DATA_SIZE);
    return packet;
}

void Protocol::packPanicButton(uint8_t* buff, const PanicButton_Packet& packet){
    if (!buff) return; 

    packHeader(buff, packet.hd);
    memcpy(buff + HEADER_SIZE, &packet.pbutton, PanicButton_DATA_SIZE);
}

PanicButton_Packet Protocol::unpackPanicButton(const uint8_t* buff){
    PanicButton_Packet packet;
    packet.hd = unpackHeader(buff);
    memcpy(&packet.pbutton, buff + HEADER_SIZE, PanicButton_DATA_SIZE);
    return packet;
}
