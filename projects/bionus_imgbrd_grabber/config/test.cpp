#include <iostream>
#include "exponential-moving-average.h"

int main() {
    ExponentialMovingAverage ema(0.3);
    for (int i = 1; i <= 5; ++i) {
        ema.addValue(i * 10.0);
    }
    std::cout << "EMA average = " << ema.average() << "\n";
    return 0;
}
