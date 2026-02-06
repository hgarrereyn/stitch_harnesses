#include <iostream>
#include <jetson-inference/stub.h>
int main(){
    std::cout << "jetson-inference stub version: " << jetson_inference_stub::version() << std::endl;
    return 0;
}
