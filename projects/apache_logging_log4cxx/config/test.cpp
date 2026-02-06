#include <log4cxx/basicconfigurator.h>
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/helpers/exception.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

int main() {
    try {
        BasicConfigurator::configure();
        LoggerPtr logger = Logger::getLogger("test.logger");
        LOG4CXX_INFO(logger, "Hello from log4cxx test program");
        LOG4CXX_DEBUG(logger, "Debug message");
        LOG4CXX_ERROR(logger, "Error message");
    } catch (const Exception& e) {
        // Ensure we don't crash in case of configuration issues
    }
    return 0;
}
