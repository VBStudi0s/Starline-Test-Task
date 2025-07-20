#pragma once

#include <unordered_map>
#include <set>
#include <string>

#include "../Tracker/Tracker.hpp"

namespace tracker
{

class TrackingManager
{

    std::unordered_map<std::string, Tracker> m_tracked_devices;

public:
    TrackingManager();

    void addTimePoint(const std::string& id, SpeedTimeStamp timestamp);

    std::set<std::string> getTrackingIDs() const;

    std::pair<int, int> getDrivetimeByID(const std::string& id);

};

}