#include "MultiPointShape.h"
#include <iostream>

void MultiPointShape::read(std::ifstream& file, std::ofstream& outputFile) {
    // Czytaj bounding box
    MultiPointBox multiPoint;
    file.read(reinterpret_cast<char*>(&multiPoint.xMin), sizeof(multiPoint.xMin));
    file.read(reinterpret_cast<char*>(&multiPoint.yMin), sizeof(multiPoint.yMin));
    file.read(reinterpret_cast<char*>(&multiPoint.xMax), sizeof(multiPoint.xMax));
    file.read(reinterpret_cast<char*>(&multiPoint.yMax), sizeof(multiPoint.yMax));

    outputFile << "X min: " << multiPoint.xMin << " ";
    outputFile << "Y min: " << multiPoint.yMin << std::endl;
    outputFile << "X max: " << multiPoint.xMax << " ";
    outputFile << "Y max: " << multiPoint.yMax << std::endl;

    // Czytaj liczbe punktow
    file.read(reinterpret_cast<char*>(&multiPoint.numPoints), sizeof(multiPoint.numPoints));
    outputFile << "Number of Points: " << multiPoint.numPoints << std::endl;

    // Czytaj poszczegolne punkty
    for (int i = 0; i < multiPoint.numPoints; i++) {
        PointShape::PointData point;
        file.read(reinterpret_cast<char*>(&point), sizeof(point));
        multiPoint.points.push_back(point);
    }

    outputFile << "Points:" << std::endl;
    for (const auto& point : multiPoint.points) {
        outputFile << " X: " << point.x << " ";
        outputFile << " Y: " << point.y << std::endl;
    }
}
