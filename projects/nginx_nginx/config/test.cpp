#include <iostream>
#include <nginx.h>

int main() {
    std::cout << "Built against " << NGINX_VER << " (version macro: " << nginx_version << ")\n";
    return 0;
}
