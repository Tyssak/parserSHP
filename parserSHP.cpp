#include <iostream>
#include <fstream>
#include <cstring>
#include "ByteConverter.h"

using namespace std;

// struktura dla informacji zawartych w głównym nagłówku SHP
struct SHPMainHeaderInt {
    int fileCode;
    int unusedBytes[5];
    int fileLength;
    int version;
    int shapeType;
};
struct SHPMainHeaderDouble {
    double xMin;
    double yMin;
    double xMax;
    double yMax;
    double zMin;
    double zMax;
    double mMin;
    double mMax;
};

// struktura dla informacji zawartych w nagłówkach rekordów SHP
struct SHPRecordHeader {
    int recordNumber;
    int contentLength;
};



int main()
{
    char fileName[] = "pliki_SHP\\polska.shp"; 
    ifstream shpFile(fileName, ios::binary);
    if (!shpFile) {
        cerr << "Couldn't open SHP file!" << endl;
        return 1;
    }

    // zapisuje wyniki też do pliku (teraz bez sensu, ale nagłówków rekordów może być trochę dużo na cout)
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cerr << "Couldn't open output file!" << endl;
        return 1;
    }


    // czytaj informacje z głównego nagłówka SHP
    SHPMainHeaderInt mainHeader1;
    shpFile.read((char*)&mainHeader1, sizeof(mainHeader1));
    if (shpFile.gcount() != sizeof(mainHeader1)) {
        cerr << "Couldn't read main header of SHP file!" << endl;
        return 1;
    }

    SHPMainHeaderDouble mainHeader2;
    shpFile.read((char*)&mainHeader2, sizeof(mainHeader2));
    if (shpFile.gcount() != sizeof(mainHeader2)) {
        cerr << "Couldn't read main header of SHP file!" << endl;
        return 1;
    }

    // konwersja z big-endian do little-endian (reszta wartości jest już little domyślnie w SHP)
    ByteConverter::bigEndianIntRead(&mainHeader1.fileCode);
    ByteConverter::bigEndianIntRead(&mainHeader1.fileLength);

    // Poszczególne wartości int z SHP odpowiadają różnym typom 
    string shapeName;
    switch (mainHeader1.shapeType) {
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

    // Wypisz informacje z głównego nagłówka
    cout << "File code: " << mainHeader1.fileCode << endl;
    cout << "File length: " << mainHeader1.fileLength << endl;
    cout << "Version: " << mainHeader1.version << endl;
    cout << "Shape type: " << shapeName << endl;
    cout << "X min: " << mainHeader2.xMin << endl;
    cout << "Y min: " << mainHeader2.yMin << endl;
    cout << "X max: " << mainHeader2.xMax << endl;
    cout << "Y max: " << mainHeader2.yMax << endl;
    cout << "Z min: " << mainHeader2.zMin << endl;
    cout << "Z max: " << mainHeader2.zMax << endl;
    cout << "M min: " << mainHeader2.mMin << endl;
    cout << "M max: " << mainHeader2.mMax << endl;
    outputFile << "File code: " << mainHeader1.fileCode << endl;
    outputFile << "File length: " << mainHeader1.fileLength << endl;
    outputFile << "Version: " << mainHeader1.version << endl;
    outputFile << "Shape type: " <<shapeName << endl;
    outputFile << "X min: " << mainHeader2.xMin << endl;
    outputFile << "Y min: " << mainHeader2.yMin << endl;
    outputFile << "X max: " << mainHeader2.xMax << endl;
    outputFile << "Y max: " << mainHeader2.yMax << endl;
    outputFile << "Z min: " << mainHeader2.zMin << endl;
    outputFile << "Z max: " << mainHeader2.zMax << endl;
    outputFile << "M min: " << mainHeader2.mMin << endl;
    outputFile << "M max: " << mainHeader2.mMax << endl;
    outputFile << endl;
    outputFile << endl;

    // tutaj coś zacząłem pisać do nagłówków rekordów, ale trzeba ogarnąć
    // jak rozróżniać nagłówek od reszty rekordu
    /*while (shpFile) {
        SHPRecordHeader recordHeader;
        shpFile.read((char*)&recordHeader, sizeof(recordHeader));
        if (shpFile.gcount() != sizeof(recordHeader)) {
            break; // end of file
        }
        ByteConverter::bigEndianIntRead(&recordHeader.recordNumber);
        ByteConverter::bigEndianIntRead(&recordHeader.contentLength);

        outputFile << "Record number: " << recordHeader.recordNumber << endl;
        outputFile << "Content length: " << recordHeader.contentLength << endl;
        outputFile << endl;

    }*/
    outputFile.close();
    return 0;
}

