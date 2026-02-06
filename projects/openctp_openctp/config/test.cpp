#include <iostream>
#include <cstring>
#include "/fuzz/install/include/ThostFtdcMdApi.h"

class TestSpi : public CThostFtdcMdSpi {
public:
    void OnFrontConnected() override {
        std::cout << "OnFrontConnected called" << std::endl;
    }
};

int main() {
    std::cout << "API Version: " << CThostFtdcMdApi::GetApiVersion() << std::endl;
    TestSpi spi;
    CThostFtdcMdApi* api = CThostFtdcMdApi::CreateFtdcMdApi("");
    if (!api) {
        std::cout << "Failed to create API instance" << std::endl;
        return 0;
    }
    api->RegisterSpi(&spi);
    // Do not actually connect or block; just initialize and release
    api->Init();
    api->Release();
    std::cout << "Finished basic API calls" << std::endl;
    return 0;
}
