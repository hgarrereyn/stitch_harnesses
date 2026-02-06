ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for httpd and APR
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    autoconf automake libtool pkg-config \
    perl python3 \
    bison flex \
    libapr1-dev libaprutil1-dev \
    libpcre3-dev libpcre2-dev \
    zlib1g-dev \
    libexpat1-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure scripts using system APR via apr-1-config
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx ./buildconf --with-apr=apr-1-config

# Configure for a static build with minimal optional deps and install prefix
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure \
      --prefix=/fuzz/install \
      --enable-static --disable-shared \
      --with-apr=/usr/bin/apr-1-config \
      --with-apr-util=/usr/bin/apu-1-config \
      --without-ssl --without-ldap

# Build and install
RUN make -j"$(nproc)" && make install

# Also copy the core static library to the install lib dir for potential linking
RUN mkdir -p /fuzz/install/lib \
 && if [ -f server/.libs/libmain.a ]; then cp server/.libs/libmain.a /fuzz/install/lib/libhttpd.a; \
    elif [ -f server/libmain.a ]; then cp server/libmain.a /fuzz/install/lib/libhttpd.a; \
    fi
