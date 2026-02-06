#include <log4cplus/initializer.h>
#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/tstring.h>
#include <iostream>

int main() {
    log4cplus::Initializer initializer;

    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test.logger"));

    log4cplus::SharedAppenderPtr appender(new log4cplus::ConsoleAppender());
    appender->setName(LOG4CPLUS_TEXT("console"));
    std::unique_ptr<log4cplus::Layout> layout(new log4cplus::PatternLayout(LOG4CPLUS_TEXT("%D{%H:%M:%S} %-5p %c - %m%n")));
    appender->setLayout(std::move(layout));
    logger.addAppender(appender);

    logger.forcedLog(log4cplus::INFO_LOG_LEVEL, LOG4CPLUS_TEXT("Hello from log4cplus test program!"));

    std::cout << "log4cplus test completed" << std::endl;
    return 0;
}
