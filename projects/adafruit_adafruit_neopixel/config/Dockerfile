ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any needed build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build

# Install public headers from the mounted source tree
RUN cp /fuzz/src/Adafruit_NeoPixel.h ${PREFIX}/include/

# Create a minimal object to archive into a static library
RUN echo "// Minimal object for libneopixel.a" > /tmp/build/empty.cpp && \
    "$CXX" -c -O2 -fPIC /tmp/build/empty.cpp -o /tmp/build/empty.o && \
    ar rcs ${PREFIX}/lib/libneopixel.a /tmp/build/empty.o && \
    ranlib ${PREFIX}/lib/libneopixel.a

ENV CMAKE_PREFIX_PATH=${PREFIX}
