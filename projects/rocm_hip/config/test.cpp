#include <iostream>
#include <hip/hip_common.h>
#include <hip/hip_version.h>
int main(){
    std::cout << "HIP version: "
              << HIP_VERSION_MAJOR << "." << HIP_VERSION_MINOR << "." << HIP_VERSION_PATCH << "\n";
    return 0;
}
