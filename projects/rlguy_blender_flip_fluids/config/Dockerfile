ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools and OpenMP for clang
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    libomp-17-dev \
 && rm -rf /var/lib/apt/lists/*

# Set compilers to the required wrappers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Build a static library of the FLIP Fluids engine
RUN set -eux; \
    mkdir -p /fuzz/build/obj /fuzz/install/lib /fuzz/install/include/flipfluids; \
    # Generate versionutils.cpp from template
    sed -e 's/@FFENGINE_VERSION_MAJOR@/0/g' \
        -e 's/@FFENGINE_VERSION_MINOR@/0/g' \
        -e 's/@FFENGINE_VERSION_REVISION@/0/g' \
        -e 's/@FFENGINE_VERSION_LABEL@/dev/g' \
        -e 's/@FFENGINE_VERSION_SUPPORT_LICENSE_TYPE@/MIT/g' \
        -e 's/@FFENGINE_VERSION_SUPPORT_LICENSE_ID@/NONE/g' \
        /fuzz/src/src/engine/versionutils.cpp.in > /fuzz/build/versionutils.cpp; \
    # Compile sources (with OpenMP enabled)
    INC="-I/fuzz/src/src/engine -I/fuzz/src/src/engine/Eigen"; \
    CXXFLAGS="-O2 -fPIC -fopenmp=libomp"; \
    for f in $(find /fuzz/src/src/engine -maxdepth 1 -name '*.cpp' ! -name 'main.cpp'); do \
        $CXX $CXXFLAGS $INC -c "$f" -o "/fuzz/build/obj/$(basename "$f" .cpp).o"; \
    done; \
    for f in /fuzz/src/src/engine/c_bindings/*.cpp; do \
        $CXX $CXXFLAGS $INC -c "$f" -o "/fuzz/build/obj/c_bindings_$(basename "$f" .cpp).o"; \
    done; \
    # Mixbox stub implementation (no external content included in OSS repo)
    $CXX $CXXFLAGS $INC -c /fuzz/src/src/engine/mixbox/mixbox_stub.cpp -o /fuzz/build/obj/mixbox_stub.o; \
    $CXX $CXXFLAGS $INC -c /fuzz/build/versionutils.cpp -o /fuzz/build/obj/versionutils.o; \
    ar rcs /fuzz/install/lib/libflipfluids.a /fuzz/build/obj/*.o; \
    # Install headers (preserve structure under flipfluids/engine)
    mkdir -p /fuzz/install/include/flipfluids/engine; \
    cp -r /fuzz/src/src/engine/* /fuzz/install/include/flipfluids/engine/; \
    # Ensure Eigen headers are available at a stable include path
    mkdir -p /fuzz/install/include/Eigen; \
    cp -r /fuzz/src/src/engine/Eigen/* /fuzz/install/include/Eigen/
