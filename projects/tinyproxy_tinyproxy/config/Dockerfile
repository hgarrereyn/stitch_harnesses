ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make gcc g++ binutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script and configure the project
RUN ./autogen.sh && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --disable-manpage-support

# Build and install
RUN make -j$(nproc) && make install

# Create a static library from object files (excluding main.o) and install headers
RUN cd src && \
    ar rcs libtinyproxy.a $(find . -maxdepth 1 -name '*.o' ! -name 'main.o') && \
    mkdir -p /fuzz/install/lib && cp libtinyproxy.a /fuzz/install/lib/

# Install headers (project does not install them by default)
RUN mkdir -p /fuzz/install/include/tinyproxy && \
    cp -v /fuzz/src/src/*.h /fuzz/install/include/tinyproxy/ && \
    cp -v /fuzz/src/config.h /fuzz/install/include/
