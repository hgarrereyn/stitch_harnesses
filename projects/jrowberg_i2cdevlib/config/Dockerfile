ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools needed for archiver and headers
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install

# Build a static library from the LinuxI2CDev sources and install headers
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/include/i2cdevlib ${INSTALL_PREFIX}/lib /tmp/build; \
    cd /fuzz/src/LinuxI2CDev; \
    gf_libafl_cxx -fPIC -I/fuzz/src/LinuxI2CDev/I2Cdev -I/fuzz/src/LinuxI2CDev/MPU6050 -c I2Cdev/I2Cdev.cpp -o /tmp/build/I2Cdev.o; \
    gf_libafl_cxx -fPIC -I/fuzz/src/LinuxI2CDev/I2Cdev -I/fuzz/src/LinuxI2CDev/MPU6050 -c MPU6050/MPU6050.cpp -o /tmp/build/MPU6050.o; \
    gf_libafl_cxx -fPIC -I/fuzz/src/LinuxI2CDev/I2Cdev -I/fuzz/src/LinuxI2CDev/MPU6050 -c MPU6050/MPU6050_6Axis_MotionApps20.cpp -o /tmp/build/MPU6050_6Axis_MotionApps20.o; \
    ar rcs ${INSTALL_PREFIX}/lib/libi2cdevlib.a /tmp/build/*.o; \
    cp /fuzz/src/LinuxI2CDev/I2Cdev/I2Cdev.h ${INSTALL_PREFIX}/include/i2cdevlib/; \
    cp /fuzz/src/LinuxI2CDev/MPU6050/MPU6050.h ${INSTALL_PREFIX}/include/i2cdevlib/; \
    cp /fuzz/src/LinuxI2CDev/MPU6050/MPU6050_6Axis_MotionApps20.h ${INSTALL_PREFIX}/include/i2cdevlib/; \
    cp /fuzz/src/LinuxI2CDev/MPU6050/helper_3dmath.h ${INSTALL_PREFIX}/include/i2cdevlib/
