ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none required for our minimal static lib)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build a tiny static library from self-contained core headers only
# and install headers + lib into /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/include/aphrodite_kernels/core /fuzz/install/lib && \
    # Copy self-contained public headers
    cp -v /fuzz/src/aphrodite_kernels/csrc/core/math.hpp /fuzz/install/include/aphrodite_kernels/core/ && \
    cp -v /fuzz/src/aphrodite_kernels/csrc/core/batch_invariant.hpp /fuzz/install/include/aphrodite_kernels/core/ && \
    cp -v /fuzz/src/aphrodite_kernels/csrc/core/exception.hpp /fuzz/install/include/aphrodite_kernels/core/ && \
    # Build an empty translation unit to archive into a static lib
    printf "int aphrodite_kernels_core_dummy() { return 0; }\n" > /fuzz/build/dummy.cpp && \
    $CXX -c /fuzz/build/dummy.cpp -O2 -fPIC -o /fuzz/build/dummy.o && \
    ar rcs /fuzz/install/lib/libaphrodite_kernels_core.a /fuzz/build/dummy.o && \
    ranlib /fuzz/install/lib/libaphrodite_kernels_core.a
