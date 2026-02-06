#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

int main() {
    // Create and use a colored console logger
    auto logger = spdlog::stdout_color_mt("console");
    logger->set_level(spdlog::level::debug);
    logger->info("Hello from spdlog {}!", SPDLOG_VERSION);
    logger->debug("This is a debug message with number {}", 42);

    // Use the default logger too
    spdlog::set_default_logger(logger);
    spdlog::warn("A warning from default logger");

    // Basic formatting test
    spdlog::info("Pi approx {:.2f}", 3.14159);

    return 0;
}
