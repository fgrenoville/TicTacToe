#include "HourGlass.h"

void HourGlass::Show(std::atomic_bool& stop)
{
    unsigned int i = 0;

    do
    {
        char chars[] = { '-', '\\', '|', '/' };

        std::cout << '\r' << chars[i++ % sizeof(chars)] << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(150));

    } while (!stop.load());

    std::cout << '\r' << std::flush;
}
