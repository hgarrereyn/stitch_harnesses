ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    make binutils \
 && rm -rf /var/lib/apt/lists/*

# Build libflv static library with fuzzing compilers
WORKDIR /fuzz/src/libflv
RUN make -j"$(nproc)" RELEASE=1 CC=gf_libafl_cc CXX=gf_libafl_cxx

# Install: copy headers and static lib
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -f include/*.h /fuzz/install/include/ \
 && find . -type f -path "*/release.*linux*/libflv.a" -exec cp -f {} /fuzz/install/lib/ \;
