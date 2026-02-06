#include <iostream>
#include "game_overlay_renderer_lib.h"

int main() {
    // Basic calls to the library
    SetNotificationInset(10, 20);
    SetNotificationPosition(ENotificationPosition::k_EPositionTopRight);

    ValveHookScreenshots(true);
    if (ValveIsScreenshotsHooked()) {
        std::cout << "Screenshots are hooked" << std::endl;
    } else {
        std::cout << "Screenshots are NOT hooked" << std::endl;
    }

    float sx = -1.0f, sy = -1.0f;
    VulkanSteamOverlayGetScaleFactors(&sx, &sy);
    std::cout << "Scale factors: " << sx << ", " << sy << std::endl;

    std::cout << "Overlay enabled? " << (IsOverlayEnabled() ? "yes" : "no") << std::endl;

    return 0;
}
