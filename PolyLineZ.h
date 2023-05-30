#pragma once

#include <fstream>
#include <vector>
#include "PointShape.h"  // Include PointShape class definition

class PolyLineZ
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
        double z_min;
        double z_max;
        std::vector<double> z_vector;
        double m_min;
        double m_max;
        std::vector<double> m_vector;
    };
};
