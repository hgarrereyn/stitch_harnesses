ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    git build-essential ca-certificates pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build and install dependencies: libfastcommon and libserverframe (to /usr)
RUN git clone --depth 1 --branch V1.0.83 https://github.com/happyfish100/libfastcommon.git /tmp/libfastcommon \
 && cd /tmp/libfastcommon \
 && ./make.sh clean && ./make.sh && ./make.sh install \
 && rm -rf /tmp/libfastcommon

# Patch libfastcommon headers to be C++ friendly (avoid user-defined literal suffix with __FILE__)
RUN grep -Rl '"__FILE__"' /usr/include/fastcommon | xargs -r sed -i 's/"__FILE__"/" __FILE__ "/g'

RUN git clone --depth 1 --branch V1.2.11 https://github.com/happyfish100/libserverframe.git /tmp/libserverframe \
 && cd /tmp/libserverframe \
 && ./make.sh clean && ./make.sh && ./make.sh install \
 && rm -rf /tmp/libserverframe

# Build and install FastDFS using fuzzing compilers, install under /fuzz/install/usr
WORKDIR /fuzz/src

# Force static lib build for client and use fuzzing compilers
RUN sed -i 's/^ENABLE_STATIC_LIB=.*/ENABLE_STATIC_LIB=1/' make.sh \
 && sed -i 's/^ENABLE_SHARED_LIB=.*/ENABLE_SHARED_LIB=0/' make.sh \
 && sed -i 's/^export CC=.*/export CC=gf_libafl_cc/' make.sh \
 && DESTDIR=/fuzz/install ./make.sh clean \
 && DESTDIR=/fuzz/install ./make.sh \
 && DESTDIR=/fuzz/install ./make.sh install

ENV PKG_CONFIG_PATH=/fuzz/install/usr/lib/pkgconfig:/fuzz/install/usr/lib64/pkgconfig
