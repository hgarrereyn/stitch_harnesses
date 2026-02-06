ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install workflow
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DKAFKA=n
RUN cmake --build /fuzz/build --target install --parallel
