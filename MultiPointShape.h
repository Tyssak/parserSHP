#pragma once

#include <fstream>
#include <vector>
#include "PointShape.h"  // Include PointShape class definition

class MultiPointShape{
public:
    void read(std::ifstream& file, std::ofstream& outputFile);

private:
    PointShape::PointData pointData;

    struct MultiPointBox {
        double xMin;
        double yMin;
        double xMax;
        double yMax;
        int numPoints;
        std::vector<PointShape::PointData> points;
    };
};
