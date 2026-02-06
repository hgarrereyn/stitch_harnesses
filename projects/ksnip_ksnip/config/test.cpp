#include <iostream>
#include <ksnip/ksnip_api.h>

int main() {
    int s = ksnip_add(2, 3);
    std::cout << "sum=" << s << std::endl;
    return 0;
}
