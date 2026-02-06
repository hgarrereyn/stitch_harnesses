ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake may not be present in the base image used for testing)
RUN apt-get update && apt-get install -y --no-install-recommends cmake ninja-build make && rm -rf /var/lib/apt/lists/*

# Build libinchi with CMake (shared library produced by upstream)
RUN cmake -G Ninja \
    -S /fuzz/src/INCHI-1-SRC/INCHI_API/libinchi/src \
    -B /fuzz/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /fuzz/build -j$(nproc) && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    # Copy the produced shared library
    cp -a /fuzz/build/lib/*.so /fuzz/install/lib/ && \
    # Ensure both names exist for linking convenience
    bash -lc 'cd /fuzz/install/lib && if [ -f inchi.so ] && [ ! -f libinchi.so ]; then ln -s inchi.so libinchi.so; fi && if [ -f libinchi.so ] && [ ! -f inchi.so ]; then ln -s libinchi.so inchi.so; fi' && \
    # Install public headers used by consumers
    cp /fuzz/src/INCHI-1-SRC/INCHI_BASE/src/inchi_api.h /fuzz/install/include/ && \
    cp /fuzz/src/INCHI-1-SRC/INCHI_BASE/src/ixa.h /fuzz/install/include/
