ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies for headers-only subset (Eigen, PCL)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libeigen3-dev \
    libpcl-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install a tiny static library and install public headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include/utils ${PREFIX}/lib && \
    # Copy public utils headers
    cp -r /fuzz/src/include/utils/* ${PREFIX}/include/utils/ && \
    # Build a minimal static library (empty object) to satisfy linker
    echo "// minimal util lib TU" > /tmp/utils_stub.cpp && \
    ${CXX} -c /tmp/utils_stub.cpp -o /tmp/utils_stub.o && \
    ar rcs ${PREFIX}/lib/libfastlivo_utils.a /tmp/utils_stub.o && \
    ranlib ${PREFIX}/lib/libfastlivo_utils.a
