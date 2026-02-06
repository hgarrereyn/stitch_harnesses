#include <iostream>
#include <string>
#include "nndeploy/framework.h"

int main() {
    int ret = nndeployFrameworkInit();
    std::cout << "Init ret=" << ret << "\n";
    std::cout << "Version=" << nndeployGetVersion() << "\n";
    ret = nndeployFrameworkDeinit();
    std::cout << "Deinit ret=" << ret << "\n";
    return 0;
}
