#include "TrackingManager.hpp"

#include <stdexcept>

namespace tracker
{

TrackingManager::TrackingManager()
{
    m_tracked_devices.reserve(10);
}

void TrackingManager::addTimePoint(const std::string& id, SpeedTimeStamp timestamp)
{
    m_tracked_devices[id].addTimePoint(timestamp);
}

std::set<std::string> TrackingManager::getTrackingIDs() const
{
    std::set<std::string> ids;
    for(const auto& elem: m_tracked_devices)
        ids.insert(elem.first);
    return ids;
}

std::pair<int, int> TrackingManager::getDrivetimeByID(const std::string& id)
{
    auto id_it = m_tracked_devices.find(id);
    if(id_it == m_tracked_devices.end())
        throw std::runtime_error("This ID is not tracking");
    return m_tracked_devices[id].getDrivetime();
}

}