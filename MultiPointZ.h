#pragma once

#include <fstream>
#include <vector>
#include "PointShape.h" 
class MultiPointZ
{
public:
    void read(std::ifstream& file, std::ofstream& outputFile);

private:

    struct MultiPointBox {
        double x_min;
        double y_min;
        double x_max;
        double y_max;
        int num_points;
        std::vector<PointShape::PointData> points;
        double z_max;
        double z_min;
        std::vector<double> z_vector;
        double m_max;
        double m_min;
        std::vector<double> m_vector;
    };
};
