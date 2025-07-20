#include "TrackerFileWriter.hpp"

#include <stdexcept>
#include <iomanip>

namespace tracker
{


TrackerFileWriter::TrackerFileWriter(const std::string& filename):
    m_ofstream(filename)
{
    if(!m_ofstream.is_open())
        throw std::runtime_error("Unable to open file: " + filename);
    m_ofstream<<m_separator;
}

float TrackerFileWriter::convertSecToHours(int seconds)
{
    return seconds/3600.0;
}

void TrackerFileWriter::writeDrivetimeByID(const std::string& id, std::pair<int, int> drivetime)
{
    m_ofstream<<"id: "<<id<<'\n';
    m_ofstream<<"время в пути: " << std::fixed<<std::setprecision(1)<<convertSecToHours(drivetime.second)<<"h\n";
    m_ofstream<<"время стоянки: " << std::fixed<<std::setprecision(1)<<convertSecToHours(drivetime.first)<<"h\n";
    m_ofstream<<m_separator;
}

}