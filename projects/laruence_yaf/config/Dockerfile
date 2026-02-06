ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install PHP dev tools to build the Yaf PHP extension
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    php-dev php-pear autoconf automake libtool make pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install

# Build and "install" Yaf into /fuzz/install
WORKDIR /fuzz/src

# Use stitch_libafl_cc/stitch_libafl_cxx for compilation via ./configure
RUN phpize \
 && CC=stitch_libafl_cc CXX=stitch_libafl_cxx ./configure \
 && make -j"$(nproc)"

# Stage install: copy artifacts to /fuzz/install
RUN mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include \
 && if [ -f modules/yaf.so ]; then cp modules/yaf.so ${INSTALL_PREFIX}/lib/; fi \
 && find . -maxdepth 1 -type f -name "*.h" -exec cp {} ${INSTALL_PREFIX}/include/ \; \
 && find configs requests responses routes views -type f -name "*.h" -exec cp --parents {} ${INSTALL_PREFIX}/include/ \; || true
