#include <iostream>
#include <fstream>
#include <cstring>
#include "ShpFile.h"

using namespace std;

int main() {
    try {
        ShpFile shpFile("pliki_SHP\\gminy.shp");
        shpFile.readMainHeaders();
        shpFile.processRecords();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
