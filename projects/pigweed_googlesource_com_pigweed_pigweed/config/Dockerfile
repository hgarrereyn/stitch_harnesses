ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja) and certificates
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install the pw_status static library
ENV PW_ROOT=/fuzz/src
WORKDIR /fuzz/build

# Configure the CMake project using the LibAFL compiler wrappers
RUN cmake -G Ninja \
  -DCMAKE_C_COMPILER=stitch_libafl_cc \
  -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  /fuzz/src

# Build only the target library we need and its deps
RUN cmake --build . --target pw_status

# Create install prefix and copy artifacts
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
  && find . -name "libpw_status*.a" -type f -exec cp {} /fuzz/install/lib/ \; \
  && cp -r /fuzz/src/pw_status/public/* /fuzz/install/include/
