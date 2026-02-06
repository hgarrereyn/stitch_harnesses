#include <cstdio>
#include "logs.h"

int main() {
    logs::setLogLevel(logs::DEBUG);
    LOG_I("NsJail logging test: %d + %d = %d", 2, 3, 2+3);
    // Also exercise explicit logging API
    logs::logMsg(logs::INFO, __FUNCTION__, __LINE__, false, "Explicit log message");
    return 0;
}
