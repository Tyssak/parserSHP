#include "ShpFile.h"

using namespace std;

ofstream outputFile;

ShpFile::ShpFile(const char* fileName) : file(fileName, ios::binary) {
    outputFile.open("output.txt", ofstream::trunc);
    if (!file) {
        throw runtime_error("Couldn't open SHP file!");
    }
}
ShpFile::~ShpFile() {
    file.close();
    outputFile.close();
}

void ShpFile::readMainHeaders() {
    file.read(reinterpret_cast<char*>(&mainHeaderInt), sizeof(mainHeaderInt));
    if (file.gcount() != sizeof(mainHeaderInt)) {
        throw runtime_error("Couldn't read main header of SHP file!");
    }

    file.read(reinterpret_cast<char*>(&mainHeaderDouble), sizeof(mainHeaderDouble));
    if (file.gcount() != sizeof(mainHeaderDouble)) {
        throw runtime_error("Couldn't read main header of SHP file!");
    }

    ByteConverter::bigEndianIntRead(&mainHeaderInt.fileCode);
    ByteConverter::bigEndianIntRead(&mainHeaderInt.fileLength);
    string shapeName;
    switch (mainHeaderInt.shapeType) {
    case 0:
        shapeName = "Null Shape";
        break;
    case 1:
        shapeName = "Point";
        break;
    case 3:
        shapeName = "PolyLine";
        break;
    case 5:
        shapeName = "Polygon";
        break;
    case 8:
        shapeName = "MultiPoint";
        break;
    case 11:
        shapeName = "PointZ";
        break;
    case 13:
        shapeName = "PolyLineZ";
        break;
    case 15:
        shapeName = "PolygonZ";
        break;
    case 18:
        shapeName = "MultiPointZ";
        break;
    case 21:
        shapeName = "PointM";
        break;
    case 23:
        shapeName = "PolyLineM";
        break;
    case 25:
        shapeName = "PolygonM";
        break;
    case 28:
        shapeName = "MultiPOintM";
        break;
    case 31:
        shapeName = "MultiPatch";
        break;
    default:
        shapeName = "Unknown";
    }

    // Wypisz informacje z g³ównego nag³ówka
    cout << "File code: " << mainHeaderInt.fileCode << endl;
    cout << "File length: " << mainHeaderInt.fileLength << endl;
    cout << "Version: " << mainHeaderInt.version << endl;
    cout << "Shape type: " << shapeName << endl;
    cout << "X min: " << mainHeaderDouble.xMin << endl;
    cout << "Y min: " << mainHeaderDouble.yMin << endl;
    cout << "X max: " << mainHeaderDouble.xMax << endl;
    cout << "Y max: " << mainHeaderDouble.yMax << endl;
    cout << "Z min: " << mainHeaderDouble.zMin << endl;
    cout << "Z max: " << mainHeaderDouble.zMax << endl;
    cout << "M min: " << mainHeaderDouble.mMin << endl;
    cout << "M max: " << mainHeaderDouble.mMax << endl;

    outputFile << "File code: " << mainHeaderInt.fileCode << endl;
    outputFile << "File length: " << mainHeaderInt.fileLength << endl;
    outputFile << "Version: " << mainHeaderInt.version << endl;
    outputFile << "Shape type: " << shapeName << endl;
    outputFile << "X min: " << mainHeaderDouble.xMin << endl;
    outputFile << "Y min: " << mainHeaderDouble.yMin << endl;
    outputFile << "X max: " << mainHeaderDouble.xMax << endl;
    outputFile << "Y max: " << mainHeaderDouble.yMax << endl;
    outputFile << "Z min: " << mainHeaderDouble.zMin << endl;
    outputFile << "Z max: " << mainHeaderDouble.zMax << endl;
    outputFile << "M min: " << mainHeaderDouble.mMin << endl;
    outputFile << "M max: " << mainHeaderDouble.mMax << endl;
    outputFile << endl;
    outputFile << endl;
}
void ShpFile::processRecords() {
    while (file) {
        SHPRecordHeader recordHeader;
        file.read(reinterpret_cast<char*>(&recordHeader), sizeof(recordHeader));
        if (file.gcount() != sizeof(recordHeader)) {
            break; // koniec pliku
        }
        ByteConverter::bigEndianIntRead(&recordHeader.recordNumber);
        ByteConverter::bigEndianIntRead(&recordHeader.contentLength);

        outputFile << "Record number: " << recordHeader.recordNumber << endl;
        outputFile << "Content length: " << recordHeader.contentLength << endl;
        outputFile << endl;

        file.seekg(static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(recordHeader.contentLength) * 2, ios::cur);
        if (!file) {
            throw runtime_error("Couldn't skip record content in SHP file!");
        }
    }
}
