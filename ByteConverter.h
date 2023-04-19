#define BYTECONVERTER_H

#include <cstdint>

namespace ByteConverter {

    // funkcja konwertuj¹ca liczby typu int z big-endian na little-endian i odwrotnie
    inline void bigEndianIntRead(int* value) {
        uint8_t* bytes = reinterpret_cast<uint8_t*>(value);
        uint8_t tmp = bytes[0];
        bytes[0] = bytes[3];
        bytes[3] = tmp;
        tmp = bytes[1];
        bytes[1] = bytes[2];
        bytes[2] = tmp;
    }

}

