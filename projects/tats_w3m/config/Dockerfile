ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    libgc-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build only the libwc library and package it for installation
WORKDIR /fuzz/src

# Configure to generate Makefiles (keeps defaults but we won't build the app)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --disable-image || true

# Build libwc static library
WORKDIR /fuzz/src/libwc
RUN make -j$(nproc)

# Build supporting objects needed by libwc users (Str and myctype)
WORKDIR /fuzz/src
RUN stitch_libafl_cc -I. -Ilibwc -c Str.c myctype.c

# Create combined static library that includes libwc plus Str/myctype
RUN mkdir -p /fuzz/install/lib /fuzz/install/include /tmp/wcbuild \
 && cp libwc/libwc.a /tmp/wcbuild/ \
 && ar x /tmp/wcbuild/libwc.a \
 && ar rcs /fuzz/install/lib/libw3mwc.a *.o Str.o myctype.o \
 && rm -rf /tmp/wcbuild *.o

# Install all libwc headers plus a few top-level headers and config.h
RUN cp libwc/*.h /fuzz/install/include/ \
 && cp Str.h myctype.h config.h /fuzz/install/include/

ENV CPATH=/fuzz/install/include LIBRARY_PATH=/fuzz/install/lib
