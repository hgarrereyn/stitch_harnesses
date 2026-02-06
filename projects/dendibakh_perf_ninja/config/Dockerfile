ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to build a static library
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Build and install a small static library from the warmup lab
# using the required compilers and install prefix /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/perf_ninja \
 && ${CXX} -O2 -fPIC -c /fuzz/src/labs/misc/warmup/solution.cpp -o /tmp/solution.o \
 && ar rcs /tmp/libperfninja_warmup.a /tmp/solution.o \
 && cp /tmp/libperfninja_warmup.a ${PREFIX}/lib/ \
 && cp /fuzz/src/labs/misc/warmup/solution.h ${PREFIX}/include/perf_ninja/solution.h
