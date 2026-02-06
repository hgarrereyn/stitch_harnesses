#include <cstdio>
#include <cmath>
extern "C" {
#include "tinyexpr.h"
}

int main() {
    // Simple interpretation
    int err = -1;
    double r1 = te_interp("5*5+sqrt(16)", &err);
    if (err != 0) {
        std::printf("interp error at %d\n", err);
        return 1;
    }

    // Compile with variables and evaluate twice
    double x = 3.0, y = 4.0;
    te_variable vars[] = { {"x", &x, TE_VARIABLE, nullptr}, {"y", &y, TE_VARIABLE, nullptr} };

    te_expr *expr = te_compile("sqrt(x^2 + y^2)", vars, 2, &err);
    if (!expr) {
        std::printf("compile error at %d\n", err);
        return 1;
    }

    double h1 = te_eval(expr);
    x = 5.0; y = 12.0;
    double h2 = te_eval(expr);
    te_free(expr);

    // Print results to verify runtime works without input
    std::printf("r1=%.0f h1=%.0f h2=%.0f\n", r1, h1, h2);
    return 0;
}
