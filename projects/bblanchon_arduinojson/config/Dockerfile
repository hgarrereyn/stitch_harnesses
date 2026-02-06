ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
 && rm -rf /var/lib/apt/lists/*

# Configure and install ArduinoJson (header-only), disable tests
RUN cmake -S /fuzz/src -B /tmp/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=OFF \
 && cmake --build /tmp/build --config Release \
 && cmake --install /tmp/build --config Release \
 && rm -rf /tmp/build
