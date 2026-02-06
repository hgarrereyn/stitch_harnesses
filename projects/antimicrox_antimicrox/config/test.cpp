#include <iostream>
#include "statisticsestimator.h"
// Pull in implementation to avoid needing a library link
#include "statisticsestimator.cpp"

int main() {
    StatisticsEstimator est;
    for (int i = 1; i <= 5; ++i) {
        est.process(i);
    }
    std::cout << "Count=" << est.getCount() << ", Mean=" << est.getMean() 
              << ", Var=" << est.calculateVariance() << "\n";
    return 0;
}
