#include "PolyLineShape.h"

void PolyLineShape::read(std::ifstream& file, std::ofstream& outputFile)
{
    // Czytaj bounding box
    PolylineBox polyline;
    file.read(reinterpret_cast<char*>(&polyline.x_min), sizeof(polyline.x_min));
    file.read(reinterpret_cast<char*>(&polyline.y_min), sizeof(polyline.y_min));
    file.read(reinterpret_cast<char*>(&polyline.x_max), sizeof(polyline.x_max));
    file.read(reinterpret_cast<char*>(&polyline.y_max), sizeof(polyline.y_max));

    outputFile << "X min: " << polyline.x_min << " ";
    outputFile << "Y min: " << polyline.y_min << std::endl;
    outputFile << "X max: " << polyline.x_max << " ";
    outputFile << "Y max: " << polyline.y_max << std::endl;

    //Czytaj liczbe czesci
    file.read(reinterpret_cast<char*>(&polyline.num_parts), sizeof(polyline.num_parts));
    outputFile << "Number of Parts: " << polyline.num_parts << std::endl;

    // Czytaj liczbe punktow
    file.read(reinterpret_cast<char*>(&polyline.num_points), sizeof(polyline.num_points));
    outputFile << "Number of Points: " << polyline.num_points << std::endl;

    //Czytaj czesci
    for (int i = 0; i < polyline.num_parts; i++) {
        int part;
        file.read(reinterpret_cast<char*>(&part), sizeof(part));
        polyline.parts.push_back(part);
    }

    // Czytaj poszczegolne Polyline
    for (int i = 0; i < polyline.num_points; i++) {
        PointShape::PointData point;
        file.read(reinterpret_cast<char*>(&point), sizeof(point));
        polyline.points.push_back(point);
    }

    // Wypisz polyline w postaci
    // Czesc n
    // Wszystkie jej punkty
    // Czesc n+1
    // ...
    outputFile << "PolyLines:" << std::endl;
    int points_counter = 0;
    for (int i = 0; i < polyline.parts.size(); ++i)
    {
        auto& part_id = polyline.parts.at(i);
        outputFile << " Id of First Point in Part no. " << i << " is: " << part_id << std::endl;
        int next_part;
        if (i != polyline.parts.size() - 1)
        {
	        next_part = polyline.parts.at(i+1);
        }
        else
        {
            next_part = NULL;
        }
        bool end_of_part = false;
        while(!end_of_part)
        {
            try {
                const auto& point = polyline.points.at(points_counter++);

                outputFile << " X: " << point.x << " ";
                outputFile << " Y: " << point.y << std::endl;
            }
            catch (std::exception)
            {
                int a = 0;
            }
            if (next_part == points_counter || points_counter == polyline.points.size()-1)
            {
                end_of_part = true;
            }
        }
    }


}



