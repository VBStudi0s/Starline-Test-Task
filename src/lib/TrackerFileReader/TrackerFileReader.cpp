#include "TrackerFileReader.hpp"

#include <stdexcept>
#include <sstream>

namespace tracker
{

TrackerFileReader::TrackerFileReader(const std::string& filename):
    m_ifstream(filename)
{
    if(!m_ifstream.is_open())
        throw std::runtime_error("Unable to open input file: " + filename);
}

int TrackerFileReader::parseTime(const std::string& date_time)
{
    // awaits YYYY-MM-DD HH:MM:SS
    // string parsing is pretty hellish

    // "checking" format matching
    if(date_time.size() < 19 || date_time[10] != ' ' ||
            date_time[13] != ':' || date_time[16] != ':')      // still faster than regex
        throw std::runtime_error("Invalid string date_time format: " + date_time);

    int hh = std::stoi(date_time.substr(11, 2));
    int mm = std::stoi(date_time.substr(14, 2));
    int ss = std::stoi(date_time.substr(17, 2));

    if(hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59)
        throw std::runtime_error("Invalid string date_time format: " + date_time);

    return hh*3600 + mm*60 + ss;

}

bool TrackerFileReader::eof() const
{
    return m_ifstream.eof();
}

std::pair<std::string, SpeedTimeStamp> TrackerFileReader::readNext()
{
    std::string line;
    if(!getline(m_ifstream, line))
        throw std::runtime_error("Unable to read new line");

    std::istringstream ss(line);
    std::string date_time_str, id_str, speed_str;

    // Might be shortened, but anyway like this. And that is the fastest way to do this
    if(!getline(ss, date_time_str, ','))
        throw std::runtime_error("Unable to parse date_time string from line:" + line);
    if(!getline(ss, id_str, ','))
        throw std::runtime_error("Unable to parse id string from line:" + line);
    if(!getline(ss, speed_str, ','))
        throw std::runtime_error("Unable to parse speed string from line:" + line);

    if(date_time_str[0] == '"')
        date_time_str = date_time_str.substr(1, date_time_str.size()-1);
    if(date_time_str.back() == '"')
        date_time_str = date_time_str.substr(0, date_time_str.size()-1);

    int time_seconds = parseTime(date_time_str);
    int speed = std::stoi(speed_str);
    SpeedTimeStamp ts{ time_seconds, speed};

    return {id_str, ts};
}

}