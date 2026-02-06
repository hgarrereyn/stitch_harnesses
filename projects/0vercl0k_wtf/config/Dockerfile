ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tooling
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
 && rm -rf /var/lib/apt/lists/*

# Configure using the required compilers
RUN cmake -S /fuzz/src/src/libs/kdmp-parser \
    -B /tmp/build-kdmp \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx

# Build to generate the configured header
RUN cmake --build /tmp/build-kdmp -j

# Install headers manually (interface library does not install by default)
RUN mkdir -p /fuzz/install/include/kdmp-parser && \
    cp -v /fuzz/src/src/libs/kdmp-parser/src/lib/*.h /fuzz/install/include/kdmp-parser/
