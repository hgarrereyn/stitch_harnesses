#include <iostream>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "helper_3dmath.h"

int main() {
    // Use some header-only math types to avoid any I/O in the test
    Quaternion q(1.0f, 0.0f, 0.0f, 0.0f);
    VectorFloat v(1.0f, 2.0f, 3.0f);
    float n = v.getMagnitude();

    MPU6050 mpu; // construct object but do not access hardware

    std::cout << "Quaternion w: " << q.w << ", vec mag: " << n << "\n";
    return 0;
}
