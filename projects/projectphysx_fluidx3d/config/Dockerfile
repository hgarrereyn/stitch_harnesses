ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools needed by the project
RUN apt-get update && apt-get install -y --no-install-recommends make binutils && rm -rf /var/lib/apt/lists/*

# Build and install the project
WORKDIR /fuzz/src
# Use the fuzzing compiler wrappers for C++
ENV CC=gf_libafl_cxx CXX=gf_libafl_cxx
RUN make Linux CC=gf_libafl_cxx CFLAGS="-std=c++17 -pthread -O -Wno-comment" && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    ar rcs /fuzz/install/lib/libfluidx3d.a temp/*.o && \
    cp -a src/*.hpp /fuzz/install/include/ && \
    cp -a src/OpenCL/lib/libOpenCL.so /usr/lib/ && \
    ln -sf /usr/lib/libOpenCL.so /usr/lib/libOpenCL.so.1 || true
