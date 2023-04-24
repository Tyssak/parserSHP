#ifndef SHPFILE_H
#define SHPFILE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "ByteConverter.h"

class ShpFile {
public:
    ShpFile(const char* fileName);
    ~ShpFile();

    void readMainHeaders();

    void processRecords();

private:
    std::ifstream file;

    struct SHPMainHeaderInt {
        int fileCode;
        int unusedBytes[5];
        int fileLength;
        int version;
        int shapeType;
    } mainHeaderInt;

    struct SHPMainHeaderDouble {
        double xMin;
        double yMin;
        double xMax;
        double yMax;
        double zMin;
        double zMax;
        double mMin;
        double mMax;
    } mainHeaderDouble;

    struct SHPRecordHeader {
        int recordNumber;
        int contentLength;
    } recordHeader;
};

#endif
