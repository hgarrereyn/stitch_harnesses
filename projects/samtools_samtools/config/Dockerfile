ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config \
    build-essential \
    libncurses-dev \
    zlib1g-dev libbz2-dev liblzma-dev libcurl4-openssl-dev libssl-dev libdeflate-dev \
    ca-certificates wget \
 && rm -rf /var/lib/apt/lists/*

# Build and install HTSlib
WORKDIR /tmp
RUN wget -q https://github.com/samtools/htslib/releases/download/1.18/htslib-1.18.tar.bz2 \
 && tar -xjf htslib-1.18.tar.bz2 \
 && cd htslib-1.18 \
 && CC=stitch_libafl_cc ./configure --enable-libcurl --prefix=/fuzz/install \
 && make -j"$(nproc)" \
 && make install

# Build libst.a and install headers and library
WORKDIR /fuzz/src

# Generate configure script and configure to use installed HTSlib
ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
RUN autoheader || true && autoconf -Wno-syntax \
 && CPPFLAGS="-I/fuzz/install/include" LDFLAGS="-L/fuzz/install/lib" \
    ./configure CC=stitch_libafl_cc CFLAGS="-O2" \
      --prefix=/fuzz/install \
      --with-htslib=system

# Build only the static helper library quickly
RUN make -j"$(nproc)" libst.a

# Install library archive and headers for external linking
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/samtools \
 && cp -a libst.a /fuzz/install/lib/ \
 && cp -a \
    sam_opts.h sam_utils.h bedidx.h bam.h bam2bcf.h bam_lpileup.h bam_plbuf.h \
    sample.h stats_isize.h bam_ampliconclip.h consensus_pileup.h \
    bam_tview.h samtools.h \
    /fuzz/install/include/samtools/ \
 && cp -a lz4/lz4.h /fuzz/install/include/
