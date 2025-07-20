#include <iostream>

#include "./core/Tracker/Tracker.hpp"
#include "./core/TrackingManager/TrackingManager.hpp"

int main(int argc, char* argv[])
{
    tracker::TrackingManager tm;
    tm.addTimePoint("123", {12, 6});
    std::cout<<tm.getDrivetimeByID("123").first<<'\n';

    tm.addTimePoint("123", {15, 6});
    tm.addTimePoint("123", {16, 6});
    tm.addTimePoint("123", {19, 6});
    std::cout<<tm.getDrivetimeByID("123").first<<'\n';

}