ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install runtime dependency for the prebuilt shared library
RUN apt-get update && apt-get install -y --no-install-recommends \
    libc++1 \
    && rm -rf /var/lib/apt/lists/*

# Environment: compilers and install prefix
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Install headers and the prebuilt Linux x64 shared library
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib && \
    cp /fuzz/src/include/ten_vad.h ${PREFIX}/include/ && \
    cp /fuzz/src/lib/Linux/x64/libten_vad.so ${PREFIX}/lib/
