#include <cstdio>
#include <tinyexpr.h>

int main() {
    const char* expr = "sin(pi/4)^2 + cos(pi/4)^2";
    int err = 0;
    double val = te_interp(expr, &err);
    if (err != 0) {
        std::printf("Parse error at %d\n", err);
        return 1;
    }
    std::printf("Value: %.6f\n", val);
    return 0;
}
