#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include "ByteConverter.h"
#include <vector>
#include "PointShape.h"
#include "MultiPointShape.h"

class ShpFile {
public:
    ShpFile(const char* fileName);
    ~ShpFile();

    void readMainHeaders();

    void processRecords();

private:
    std::ifstream file;

    struct MainHeaderBaseInfo {
        int fileCode;
        int unusedBytes[5];
        int fileLength;
        int version;
        int shapeType;
    } mainHeaderBaseInfo;

    struct MainHeaderBoundingBox {
        double xMin;
        double yMin;
        double xMax;
        double yMax;
        double zMin;
        double zMax;
        double mMin;
        double mMax;
    } mainHeaderBoundingBox;

    struct RecordHeader {
        int recordNumber;
        int contentLength;
    } recordHeader;
};

