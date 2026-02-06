#include <iostream>
#include <kvrocks/time_util.h>

int main() {
    auto ms = util::GetTimeStampMS();
    auto us = util::GetTimeStampUS();
    std::cout << "kvrocks time util works: ms=" << ms << ", us=" << us << "\n";
    return 0;
}
