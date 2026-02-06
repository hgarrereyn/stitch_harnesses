ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libsqlite3-dev libpcre2-dev zlib1g-dev libbz2-dev libarchive-dev \
    libcurl4-openssl-dev libunistring-dev libgpm-dev libncursesw5-dev \
    cargo rustc \
    ca-certificates git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build with fuzzing compilers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install

# Copy static libraries and headers to install prefix for linking
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/lnav; \
    # Copy libraries built in the tree
    for f in \
      src/libdiag.a \
      src/libdatascanner.a \
      src/base/libbase.a \
      src/formats/logfmt/liblogfmt.a \
      src/fmtlib/libcppfmt.a \
      src/third-party/date/src/libdatepp.a \
      src/third-party/scnlib/src/libscnlib.a \
      src/pcrepp/libpcrepp.a \
      src/pugixml/libpugixml.a \
      src/tailer/libtailerservice.a \
      src/tailer/libtailercommon.a \
      src/tailer/libtailerpp.a \
      src/yajl/libyajl.a \
      src/yajlpp/libyajlpp.a \
      src/third-party/base64/lib/libbase64.a \
      src/third-party/notcurses/src/lib/liblnavnotcurses.a \
      src/third-party/lnav-rs-ext/target/release/liblnav_rs_ext.a \
    ; do \
      if [ -f "$f" ]; then cp -a "$f" /fuzz/install/lib/; fi; \
    done; \
    # Copy headers (and required includes) for external builds
    cp -a src/* /fuzz/install/include/lnav/ && \
    true
