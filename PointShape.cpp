#include "PointShape.h"
#include <iostream>


void PointShape::read(std::ifstream& file, std::ofstream& outputFile) {
    // Czytaj bounding box
    PointData point;
    file.read(reinterpret_cast<char*>(&point), sizeof(point));

    outputFile << "Point X: " << point.x << std::endl;
    outputFile << "Point Y: " << point.y << std::endl;
}
