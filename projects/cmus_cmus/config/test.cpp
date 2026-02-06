#include <iostream>
extern "C" {
#include <utils.h>
}

int main() {
    // Use a few inline helpers from utils.h so we don't need to link to any symbol
    int a = clamp(150, 0, 100);
    int b = scale_to_percentage(25, 255);
    int c = is_http_url("http://example.com");

    std::cout << a << "," << b << "," << c << "\n";
    return 0;
}
