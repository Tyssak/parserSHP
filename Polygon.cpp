#include "Polygon.h"

void Polygon::read(std::ifstream& file, std::ofstream& outputFile)
{
    // Czytaj bounding box
    PolygonBox polygon;
    file.read(reinterpret_cast<char*>(&polygon.x_min), sizeof(polygon.x_min));
    file.read(reinterpret_cast<char*>(&polygon.y_min), sizeof(polygon.y_min));
    file.read(reinterpret_cast<char*>(&polygon.x_max), sizeof(polygon.x_max));
    file.read(reinterpret_cast<char*>(&polygon.y_max), sizeof(polygon.y_max));

    outputFile << "X min: " << polygon.x_min << " ";
    outputFile << "Y min: " << polygon.y_min << std::endl;
    outputFile << "X max: " << polygon.x_max << " ";
    outputFile << "Y max: " << polygon.y_max << std::endl;

    //Czytaj liczbe czesci
    file.read(reinterpret_cast<char*>(&polygon.num_parts), sizeof(polygon.num_parts));
    outputFile << "Number of Parts: " << polygon.num_parts << std::endl;

    // Czytaj liczbe punktow
    file.read(reinterpret_cast<char*>(&polygon.num_points), sizeof(polygon.num_points));
    outputFile << "Number of Points: " << polygon.num_points << std::endl;

    //Czytaj czesci
    for (int i = 0; i < polygon.num_parts; i++) {
        int part;
        file.read(reinterpret_cast<char*>(&part), sizeof(part));
        polygon.parts.push_back(part);
    }

    // Czytaj poszczegolne Polyline
    for (int i = 0; i < polygon.num_points; i++) {
        PointShape::PointData point;
        file.read(reinterpret_cast<char*>(&point), sizeof(point));
        polygon.points.push_back(point);
    }

    // Wypisz polyline w postaci
   // Czesc n
   // Wszystkie jej punkty
   // Czesc n+1
   // ...
    outputFile << "PolyLines:" << std::endl;
    int points_counter = 0;
    for (int i = 0; i < polygon.parts.size(); ++i)
    {
        auto& part_id = polygon.parts.at(i);
        outputFile << "Id of First Point in Part no. " << i << "is: " << part_id << std::endl;
        int next_part;
        if (i != polygon.parts.size() - 1)
        {
            next_part = polygon.parts.at(i + 1);
        }
        else
        {
            next_part = NULL;
        }
        bool end_of_part = false;
        while (!end_of_part)
        {
            const auto& point = polygon.points.at(points_counter++);
            outputFile << "X: " << point.x << " ";
            outputFile << "Y: " << point.y << std::endl;
            if (next_part == points_counter || points_counter == polygon.points.size())
            {
                end_of_part = true;
            }
        }
    }
}


