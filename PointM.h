#pragma once

#include <fstream>
class PointM
{
public:

    void read(std::ifstream& file, std::ofstream& outputFile);

private:
    struct PointData {
        double x;
        double y;
        double measure;
    };


};

