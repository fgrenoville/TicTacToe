#ifndef HourGlass_hpp
#define HourGlass_hpp

#include <iostream>
#include <chrono>
#include <thread>

class HourGlass
{
public:
    void Show(std::atomic_bool& stop);
};

#endif
