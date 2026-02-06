#include <iostream>
#include "/fuzz/install/include/paddle/fluid/inference/api/paddle_inference_api.h"

int main() {
    // Do not instantiate or call non-inline methods to avoid linking to full lib
    const char* api_name = "paddle_inference_api.h included";
    // Use a type from the API to prove headers are usable
    using Cfg = paddle_infer::Config;
    (void)sizeof(Cfg); // ensure the type is complete at compile time
    std::cout << api_name << std::endl;
    return 0;
}
