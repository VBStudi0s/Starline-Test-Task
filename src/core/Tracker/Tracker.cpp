#include "Tracker.hpp"

#include <stdexcept>
#include <algorithm>

namespace tracker
{

constexpr int c_standing_time = 2*60;
constexpr int c_day_end = 23*60*60 + 59*60 + 59;

Tracker::Tracker()
{
    m_points.reserve(20);
}

void Tracker::addTimePoint(SpeedTimeStamp timepoint)
{
    if(timepoint.speed < 0)
        throw std::runtime_error("Speed is below zero");
    if(timepoint.time < 0 || timepoint.time > c_day_end)
        throw std::runtime_error("Invalid timestamp time parameter");
    m_points.emplace_back(timepoint);
}
    
/* <standing_time, driving_time> */
std::pair<int, int> Tracker::getDrivetime()
{
    if(m_points.empty())
        return {c_day_end, 0};

    std::sort(m_points.begin(), m_points.end(), 
        [](const SpeedTimeStamp& a, const SpeedTimeStamp& b){return a.time < b.time;});

    int accumutated_still_time = 0, accumulated_drive_time = 0;
    
    // for tracking situasions like [.. 0, 0, 0, 0, 0 ...]
    int zero_speed_consecutive_intervals = 0;

    SpeedTimeStamp prev_ts = {0, 0};    // fictional 00:00:00 zero-speed point
    m_points.emplace_back(SpeedTimeStamp{c_day_end, 0});    // fictional 23:59:59 zero-speed point

    // from prev = 00:00:00 to 23:59:59 = m_points.back()
    for(const SpeedTimeStamp& cur_ts: m_points)
    {
        int time_interval = cur_ts.time - prev_ts.time;

        if(time_interval >= c_standing_time) // => 100% car was standing still
        {
            // adding to the previous zero-speed intervals
            zero_speed_consecutive_intervals += time_interval;
        }
        else    // interval is less than c_standing_time
        {
            if(prev_ts.speed == 0 && cur_ts.speed == 0)   // interval might be small stand less than c_standing time but consecutive
                zero_speed_consecutive_intervals += time_interval;
            else    // interval < c_standing_time and speed was > 0 => (at least now started) moving
            {
                if(zero_speed_consecutive_intervals >= c_standing_time)
                    accumutated_still_time += zero_speed_consecutive_intervals;
                else
                    accumulated_drive_time += zero_speed_consecutive_intervals;
                zero_speed_consecutive_intervals = 0;

                accumulated_drive_time += time_interval;
            }
        }

        prev_ts = cur_ts;
    }

    if(zero_speed_consecutive_intervals >= c_standing_time)
        accumutated_still_time += zero_speed_consecutive_intervals;
    return {accumutated_still_time, accumulated_drive_time};
}

}