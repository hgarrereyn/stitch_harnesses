#include <iostream>
#include <dng_point.h>
#include <dng_rect.h>
#include <dng_string.h>
#include <dng_date_time.h>

int main() {
    dng_point p1(10, 20), p2(5, 7);
    dng_point sum = p1 + p2;
    dng_rect r(0, 0, 100, 50);

    dng_string s;
    std::cout << "sum: (" << sum.v << "," << sum.h << ")\n";
    std::cout << "rect top-left: (" << r.t << "," << r.l << ") size (" << r.H() << "," << r.W() << ")\n";

    dng_date_time dt; (void)dt; (void)s;
    return 0;
}
