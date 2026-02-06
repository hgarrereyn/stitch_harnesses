ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (ar is in binutils)
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Set compilers to the fuzzing wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build a static library from the Arduino-style sources in /fuzz/src/src
RUN mkdir -p /build /fuzz/install/include/locale /fuzz/install/lib && \
    cd /build && \
    SRC_DIR=/fuzz/src/src && \
    TEST_DIR=/fuzz/src/test && \
    "$CXX" -O2 -fPIC -DUNIT_TEST -D_IR_LOCALE_=en-AU -I"$SRC_DIR" -I"$TEST_DIR" -c "$SRC_DIR"/*.cpp && \
    ar rcs /fuzz/install/lib/libirremoteesp8266.a ./*.o && \
    cp -v "$SRC_DIR"/*.h /fuzz/install/include/ && \
    cp -v "$TEST_DIR"/IRsend_test.h /fuzz/install/include/ && \
    cp -v "$SRC_DIR"/locale/*.h /fuzz/install/include/locale/
