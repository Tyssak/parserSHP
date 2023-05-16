#pragma once
#include <fstream>
#include <vector>
#include "PointShape.h" 
class MultiPointM
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
        double m_max;
        double m_min;
        std::vector<double> m_vector;
    };
};

