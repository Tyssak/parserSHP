#include "MultiPointM.h"
#include <iostream>

void MultiPointM::read(std::ifstream& file, std::ofstream& outputFile) {
    // Czytaj bounding box
    MultiPointBox multiPoint;
    file.read(reinterpret_cast<char*>(&multiPoint.x_min), sizeof(multiPoint.x_min));
    file.read(reinterpret_cast<char*>(&multiPoint.y_min), sizeof(multiPoint.y_min));
    file.read(reinterpret_cast<char*>(&multiPoint.x_max), sizeof(multiPoint.x_max));
    file.read(reinterpret_cast<char*>(&multiPoint.y_max), sizeof(multiPoint.y_max));

    outputFile << "X min: " << multiPoint.x_min << " ";
    outputFile << "Y min: " << multiPoint.y_min << std::endl;
    outputFile << "X max: " << multiPoint.x_max << " ";
    outputFile << "Y max: " << multiPoint.y_max << std::endl;

    // Czytaj liczbe punktow
    file.read(reinterpret_cast<char*>(&multiPoint.num_points), sizeof(multiPoint.num_points));
    outputFile << "Number of Points: " << multiPoint.num_points << std::endl;

    // Czytaj poszczegolne punkty
    for (int i = 0; i < multiPoint.num_points; i++) {
        PointShape::PointData point;
        file.read(reinterpret_cast<char*>(&point), sizeof(point));
        multiPoint.points.push_back(point);
    }

    file.read(reinterpret_cast<char*>(&multiPoint.m_min), sizeof(multiPoint.m_min));
    file.read(reinterpret_cast<char*>(&multiPoint.m_max), sizeof(multiPoint.m_max));

    // Czytaj poszczegolne punkty M
    for (int i = 0; i < multiPoint.num_points; i++) {
        double m_value;
        file.read(reinterpret_cast<char*>(&m_value), sizeof(m_value));
        multiPoint.m_vector.push_back(m_value);
    }

    outputFile << "Points:" << std::endl;
    for (int i = 0; i < multiPoint.num_points; i++) {
        outputFile << " X: " << multiPoint.points.at(i).x << " ";
        outputFile << " Y: " << multiPoint.points.at(i).y << " ";
    	outputFile << " M: " << multiPoint.m_vector.at(i) << " ";
    }

}