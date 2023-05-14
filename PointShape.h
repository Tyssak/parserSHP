#pragma once

#include <fstream>

class PointShape {

public:
    struct PointData {
        double x;
        double y;
    };
    void read(std::ifstream& file, std::ofstream& outputFile);
};
