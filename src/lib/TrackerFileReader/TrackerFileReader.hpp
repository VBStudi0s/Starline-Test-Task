#pragma once

#include <fstream>
#include <string>

#include "../../models/SpeedTimeStamp.hpp"

namespace tracker
{
class TrackerFileReader
{
    std::ifstream m_ifstream;

    // Awaits YYYY-MM-DD HH:MM:SS -> returns HH:MM:SS in seconds
    static int parseTime(const std::string& date_time);

public:

    TrackerFileReader(const std::string& filename);

    bool eof() const;

    std::pair<std::string, SpeedTimeStamp> readNext();
};

}