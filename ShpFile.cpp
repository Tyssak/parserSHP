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
    file.read(reinterpret_cast<char*>(&mainHeaderBaseInfo), sizeof(mainHeaderBaseInfo));
    if (file.gcount() != sizeof(mainHeaderBaseInfo)) {
        throw runtime_error("Couldn't read main header of SHP file!");
    }

    file.read(reinterpret_cast<char*>(&mainHeaderBoundingBox), sizeof(mainHeaderBoundingBox));
    if (file.gcount() != sizeof(mainHeaderBoundingBox)) {
        throw runtime_error("Couldn't read main header of SHP file!");
    }

    ByteConverter::bigEndianIntRead(&mainHeaderBaseInfo.fileCode);
    ByteConverter::bigEndianIntRead(&mainHeaderBaseInfo.fileLength);
    string shapeName;
    switch (mainHeaderBaseInfo.shapeType) {
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
    cout << "File code: " << mainHeaderBaseInfo.fileCode << endl;
    cout << "File length: " << mainHeaderBaseInfo.fileLength << endl;
    cout << "Version: " << mainHeaderBaseInfo.version << endl;
    cout << "Shape type: " << shapeName << endl;
    cout << "X min: " << mainHeaderBoundingBox.xMin << endl;
    cout << "Y min: " << mainHeaderBoundingBox.yMin << endl;
    cout << "X max: " << mainHeaderBoundingBox.xMax << endl;
    cout << "Y max: " << mainHeaderBoundingBox.yMax << endl;
    cout << "Z min: " << mainHeaderBoundingBox.zMin << endl;
    cout << "Z max: " << mainHeaderBoundingBox.zMax << endl;
    cout << "M min: " << mainHeaderBoundingBox.mMin << endl;
    cout << "M max: " << mainHeaderBoundingBox.mMax << endl;

    outputFile << "File code: " << mainHeaderBaseInfo.fileCode << endl;
    outputFile << "File length: " << mainHeaderBaseInfo.fileLength << endl;
    outputFile << "Version: " << mainHeaderBaseInfo.version << endl;
    outputFile << "Shape type: " << shapeName << endl;
    outputFile << "X min: " << mainHeaderBoundingBox.xMin << endl;
    outputFile << "Y min: " << mainHeaderBoundingBox.yMin << endl;
    outputFile << "X max: " << mainHeaderBoundingBox.xMax << endl;
    outputFile << "Y max: " << mainHeaderBoundingBox.yMax << endl;
    outputFile << "Z min: " << mainHeaderBoundingBox.zMin << endl;
    outputFile << "Z max: " << mainHeaderBoundingBox.zMax << endl;
    outputFile << "M min: " << mainHeaderBoundingBox.mMin << endl;
    outputFile << "M max: " << mainHeaderBoundingBox.mMax << endl;
    outputFile << endl;
    outputFile << endl;
}
void ShpFile::processRecords() {
    while (file) {
        RecordHeader recordHeader;
        file.read(reinterpret_cast<char*>(&recordHeader), sizeof(recordHeader));
        if (file.gcount() != sizeof(recordHeader)) {
            break; // koniec pliku
        }
        ByteConverter::bigEndianIntRead(&recordHeader.recordNumber);
        ByteConverter::bigEndianIntRead(&recordHeader.contentLength);

        outputFile << "Record number: " << recordHeader.recordNumber << endl;
        outputFile << "Content length: " << recordHeader.contentLength << endl;

        int shapeType;
        file.read(reinterpret_cast<char*>(&shapeType), sizeof(shapeType));
        outputFile << "Shape type: " << shapeType << endl;

        // Czytanie róznych typów geometrii
        switch (shapeType) {
        case 1: 
            PointShape point;
            point.read(file, outputFile);
            break;
        case 3:
            PolyLineShape poly_line;
            poly_line.read(file, outputFile);
            break;
        case 5:
            Polygon polygon;
            polygon.read(file, outputFile);
            break;
        case 8: 
            MultiPointShape multiPoint;
            multiPoint.read(file, outputFile);
            break;
        case 21:
            PointM point_m;
            point_m.read(file, outputFile);
            break;
        case 23:
            PolyLineM poli_line_m;
            poli_line_m.read(file, outputFile);
            break;
        case 25:
            PolygonM polygon_m;
            polygon_m.read(file, outputFile);
            break;
        case 28:
            MultiPointM multi_point_m;
            multi_point_m.read(file, outputFile);
            break;
        default:
            // Niewspierane typy, pomijaj zawartosc
            file.seekg(static_cast<std::basic_istream<char, std::char_traits<char>>::off_type>(recordHeader.contentLength) * 2 - 4, ios::cur);
            break;
        }

        outputFile << endl;

        if (!file) {
            throw runtime_error("Couldn't skip record content in SHP file!");
        }
    }
}
