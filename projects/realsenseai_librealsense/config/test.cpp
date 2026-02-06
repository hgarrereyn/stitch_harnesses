#include <iostream>
#include <librealsense2/rs.hpp>

int main() {
    try {
        rs2::context ctx;
        auto list = ctx.query_devices();
        std::cout << "RealSense devices found: " << list.size() << std::endl;
        // Basic API touch: construct config and pipeline objects (do not start)
        rs2::config cfg;
        rs2::pipeline p(ctx);
        (void)cfg; (void)p;
    } catch (const rs2::error &e) {
        std::cerr << "librealsense error: " << e.get_failed_function() << ": " << e.get_failed_args() << " -> " << e.what() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "std exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
