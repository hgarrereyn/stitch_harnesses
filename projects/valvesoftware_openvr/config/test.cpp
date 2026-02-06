#include <iostream>
#include <openvr/openvr.h>

int main() {
    vr::EVRInitError e = vr::VRInitError_None;
    vr::IVRSystem *pVR = vr::VR_Init(&e, vr::EVRApplicationType::VRApplication_Background);

    if (e != vr::VRInitError_None) {
        std::cout << "OpenVR init failed: " << vr::VR_GetVRInitErrorAsEnglishDescription(e) << "\n";
    } else {
        std::cout << "OpenVR initialized successfully. Runtime pointer: " << pVR << "\n";
    }

    vr::VR_Shutdown();
    std::cout << "OpenVR shutdown called." << std::endl;
    return 0;
}
