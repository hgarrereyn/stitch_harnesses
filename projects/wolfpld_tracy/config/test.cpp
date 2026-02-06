#include <tracy/Tracy.hpp>

int main() {
    ZoneScoped; // create a profiling zone
    FrameMark;  // mark a frame
    return 0;
}
