ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Tor
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config \
    libevent-dev libssl-dev zlib1g-dev liblzma-dev libzstd-dev \
    python3 ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# Build Tor and assemble a single static library archive
WORKDIR /fuzz/src

# Generate configure script if needed (for git checkouts)
RUN if [ -f ./autogen.sh ]; then ./autogen.sh; fi

# Configure with fuzzer compilers and minimal extras; install prefix is /fuzz/install
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install \
      --disable-asciidoc --disable-manpage --disable-html-manual \
      --disable-systemd --disable-unittests || (cat config.log || true; exit 1)

# Build tor and create the combined static libtor.a
RUN make -j"$(nproc)" && make -j"$(nproc)" libtor.a

# Install artifacts into /fuzz/install
RUN mkdir -p /fuzz/install/lib \
           /fuzz/install/include/lib/encoding \
           /fuzz/install/include/lib/cc \
           /fuzz/install/include/lib/testsupport \
           /fuzz/install/include/lib/intmath \
  && cp -v libtor.a /fuzz/install/lib/ \
  && cp -v orconfig.h /fuzz/install/include/ \
  && cp -v src/lib/encoding/binascii.h /fuzz/install/include/lib/encoding/ \
  && cp -v src/lib/cc/torint.h /fuzz/install/include/lib/cc/ \
  && cp -v src/lib/testsupport/testsupport.h /fuzz/install/include/lib/testsupport/ \
  && cp -v src/lib/intmath/muldiv.h /fuzz/install/include/lib/intmath/
