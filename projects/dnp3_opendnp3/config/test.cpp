#include <opendnp3/DNP3Manager.h>
#include <opendnp3/ConsoleLogger.h>
#include <opendnp3/logging/LogLevels.h>
#include <memory>
#include <iostream>

int main() {
    try {
        auto logger = opendnp3::ConsoleLogger::Create(false);
        opendnp3::DNP3Manager manager(1, logger);
        manager.Shutdown();
        std::cout << "opendnp3 manager constructed and shut down" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
