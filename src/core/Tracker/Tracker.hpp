#pragma once

#include <vector>
#include <utility>

#include "../../models/SpeedTimeStamp.hpp"

namespace tracker
{

class Tracker
{
    std::vector<SpeedTimeStamp> m_points;
public:
    void addTimePoint(SpeedTimeStamp timepoint);
    
    /* Returns <standing_time, driving_time> */
    std::pair<int, int> getDrivetime();
};

}