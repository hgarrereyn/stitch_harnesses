ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies for building sudo (OpenSSL for digest support, pkg-config for feature checks)
RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl-dev \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and install prefix; prefer static libs and disable optional integrations
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --without-pam \
    --without-ldap \
    --without-selinux \
    --without-systemd \
    --without-audit || { cat config.log || true; exit 1; }

# Build and install, then stage the static util lib and headers (and generated config.h)
RUN make -j"$(nproc)" && make install \
 && mkdir -p /fuzz/install/lib /fuzz/install/include/compat \
 && cp -f lib/util/.libs/libsudo_util.a /fuzz/install/lib/ \
 && cp -f include/*.h /fuzz/install/include/ \
 && cp -rf include/compat /fuzz/install/include/ \
 && cp -f config.h /fuzz/install/include/
