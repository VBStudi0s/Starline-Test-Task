#include <iostream>
#include <string>

#include "./core/ProcessTrackedData/ProcessTrackedData.hpp"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr<<"Usage: "<<argv[0]<<" <input.csv> <outout.txt>\n";
        return 1;
    }
    try
    {
        tracker::processTrackedData(std::string(argv[1]), std::string(argv[2]));
    }
    catch(const std::exception& e)
    {
        std::cerr<<"Error: "<<e.what()<<'\n';
        return 2;
    }
    return 0;
}