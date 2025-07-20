#include <iostream>

#include "./core/Tracker/Tracker.hpp"

int main(int argc, char* argv[])
{
    std::cout<<"Hello, world!\n";
    tracker::Tracker t;
    t.addTimePoint({2, 0});
    std::cout<<"REs: "<<t.getDrivetime().first<<" sec\n";
}