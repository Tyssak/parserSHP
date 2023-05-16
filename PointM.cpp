#include "PointM.h"


void PointM::read(std::ifstream& file, std::ofstream& outputFile)
{
    PointData point;
    file.read(reinterpret_cast<char*>(&point), sizeof(point));

    outputFile << "Point X: " << point.x << " ";
    outputFile << "Point Y: " << point.y << " ";
    outputFile << "Measure: " << point.measure << std::endl;
}
