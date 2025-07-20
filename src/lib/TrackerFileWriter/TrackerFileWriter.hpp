#pragma once

#include <fstream>
#include <string>

namespace tracker
{

class TrackerFileWriter
{
    std::ofstream m_ofstream;
    std::string m_separator = "-----\n";

    float convertSecToHours(int seconds);

public:
    TrackerFileWriter(const std::string& filename);

    void writeDrivetimeByID(const std::string& id, std::pair<int, int> drivetime);
};

}