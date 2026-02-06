#include <cstdio>
#include <cstdint>
#include <arcore_c_api.h>

int main() {
    // Use only types/enums/macros to avoid needing the runtime shared library.
    ArStatus status = AR_SUCCESS;
    ArPose* pose_ptr = nullptr; // opaque type pointer
    printf("ARCore header loaded. Status=%d, TrackingState=%d, size(ArPose*)=%zu\n",
           (int)status, (int)AR_TRACKING_STATE_STOPPED, sizeof(pose_ptr));

    // Use some other enums/constants to ensure basic usability.
    int trackable_point = (int)AR_TRACKABLE_POINT;
    int light_mode = (int)AR_LIGHT_ESTIMATION_MODE_AMBIENT_INTENSITY;
    printf("TrackablePoint=%d, LightEstimationMode=%d\n", trackable_point, light_mode);
    return 0;
}
