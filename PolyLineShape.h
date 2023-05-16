#pragma once
#include <fstream>
#include <vector>
#include "PointShape.h"  // Include PointShape class definition

class PolyLineShape
{
public:
    void read(std::ifstream& file, std::ofstream& outputFile);


private:
    struct PolylineBox {
        double x_min;
        double y_min;
        double x_max;
        double y_max;
        int num_parts;
        int num_points;
        std::vector<int> parts;
        std::vector<PointShape::PointData> points;
    };
};

