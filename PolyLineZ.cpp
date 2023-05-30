#include "PolyLineZ.h"

void PolyLineZ::read(std::ifstream& file, std::ofstream& outputFile)
{
    // Czytaj bounding box
    PolylineBox polyline;
    file.read(reinterpret_cast<char*>(&polyline.x_min), sizeof(polyline.x_min));
    file.read(reinterpret_cast<char*>(&polyline.y_min), sizeof(polyline.y_min));
    file.read(reinterpret_cast<char*>(&polyline.x_max), sizeof(polyline.x_max));
    file.read(reinterpret_cast<char*>(&polyline.y_max), sizeof(polyline.y_max));


    // Czytaj liczbe czesci
    file.read(reinterpret_cast<char*>(&polyline.num_parts), sizeof(polyline.num_parts));

    // Czytaj liczbe punktow
    file.read(reinterpret_cast<char*>(&polyline.num_points), sizeof(polyline.num_points));

    // Czytaj czesci
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
    // Czytaj liczbe Z
    file.read(reinterpret_cast<char*>(&polyline.z_min), sizeof(polyline.z_min));
    file.read(reinterpret_cast<char*>(&polyline.z_max), sizeof(polyline.z_max));

    // Czytaj poszczegolne punkty Z
    for (int i = 0; i < polyline.num_points; i++) {
        double z_value;
        file.read(reinterpret_cast<char*>(&z_value), sizeof(z_value));
        polyline.z_vector.push_back(z_value);
    }

    // Czytaj liczbe M
    file.read(reinterpret_cast<char*>(&polyline.m_min), sizeof(polyline.m_min));
    file.read(reinterpret_cast<char*>(&polyline.m_max), sizeof(polyline.m_max));

    outputFile << "X min: " << polyline.x_min << " ";
    outputFile << "Y min: " << polyline.y_min << " ";
    outputFile << "Z min: " << polyline.z_min << " ";
    outputFile << "M min: " << polyline.m_min << std::endl;
    outputFile << "X max: " << polyline.x_max << " ";
    outputFile << "Y max: " << polyline.y_max << " ";
    outputFile << "Z max: " << polyline.z_max << " ";
    outputFile << "M max: " << polyline.m_max << std::endl;

    outputFile << "Number of Parts: " << polyline.num_parts << std::endl;
    outputFile << "Number of Points: " << polyline.num_points << std::endl;

    // Czytaj poszczegolne punkty M
    for (int i = 0; i < polyline.num_points; i++) {
        double m_value;
        file.read(reinterpret_cast<char*>(&m_value), sizeof(m_value));
        polyline.m_vector.push_back(m_value);
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
        outputFile << "Id of First Point in Part no. " << i << " is: " << part_id << std::endl;
        int next_part;
        if (i != polyline.parts.size() - 1)
        {
            next_part = polyline.parts.at(i + 1);
        }
        else
        {
            next_part = -1;
        }
        bool end_of_part = false;
        while (!end_of_part)
        {
            try {
                const auto& point = polyline.points.at(points_counter++);

                outputFile << "X: " << point.x << " ";
                outputFile << "Y: " << point.y << " ";
                outputFile << "Z: " << polyline.z_vector.at(points_counter) << " ";
                outputFile << "M: " << polyline.m_vector.at(points_counter) << std::endl;
            }
            catch (std::exception&)
            {
                int a = 0;
            }
            if (next_part == points_counter || points_counter == polyline.points.size() - 1)
            {
                end_of_part = true;
            }
        }
    }
}
