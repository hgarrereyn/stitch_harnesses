ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies (Qt5 Core for building and running Path library)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    qtbase5-dev pkg-config && \
    rm -rf /var/lib/apt/lists/*

# Build and install a small static library from the project (Path)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Build static library
RUN mkdir -p /fuzz/build && cd /fuzz/build && \
    ${CXX} -c -O2 -fPIC \
      $(pkg-config --cflags Qt5Core) \
      -I/fuzz/src/app \
      /fuzz/src/app/path.cpp -o path.o && \
    ar rcs libmoonlight_path.a path.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp libmoonlight_path.a /fuzz/install/lib/ && \
    cp /fuzz/src/app/path.h /fuzz/install/include/
