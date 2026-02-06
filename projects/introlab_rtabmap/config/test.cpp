#include <rtabmap/utilite/ULogger.h>
#include <rtabmap/utilite/UTimer.h>
#include <iostream>

int main() {
    ULogger::setLevel(ULogger::kInfo);
    ULOGGER_INFO("Hello from RTAB-Map utilite!");
    UTimer timer;
    timer.start();
    for (volatile int i=0;i<1000000;++i){}
    double t = timer.ticks();
    std::cout << "Elapsed: " << t << " s" << std::endl;
    return 0;
}
