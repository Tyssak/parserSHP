#pragma once

#include <fstream>
class PointZ
{
public:

    void read(std::ifstream& file, std::ofstream& outputFile);

private:
    struct PointData {
        double x;
        double y;
        double z;
        double measure;
    };


};

