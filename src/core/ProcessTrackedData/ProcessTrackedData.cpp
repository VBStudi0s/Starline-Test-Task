#include "ProcessTrackedData.hpp"

#include "../../lib/TrackerFileReader/TrackerFileReader.hpp"
#include "../../lib/TrackerFileWriter/TrackerFileWriter.hpp"
#include "../TrackingManager/TrackingManager.hpp"

namespace tracker
{

void processTrackedData(const std::string& input_filename, const std::string& output_filename)
{
    TrackerFileReader reader(input_filename);
    TrackingManager manager;

    int i=0;
    std::pair<std::string, SpeedTimeStamp> data_line;
    while(!reader.eof())
    {
        try
        {
            data_line = reader.readNext();
        }
        catch(const std::runtime_error& re)
        { 
            break;
        }
        manager.addTimePoint(data_line.first, data_line.second);
    }

    TrackerFileWriter writer(output_filename);
    std::set<std::string> ids = manager.getTrackingIDs();
    for(const auto& id: ids)
    {
        writer.writeDrivetimeByID(id, manager.getDrivetimeByID(id));
    }
}

}