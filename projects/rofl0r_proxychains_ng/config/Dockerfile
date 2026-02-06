ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install proxychains-ng
RUN set -eux; \
    cd /fuzz/src; \
    ./configure --prefix=/fuzz/install --sysconfdir=/fuzz/install/etc CC=gf_libafl_cc; \
    make -j"$(nproc)"; \
    make install; \
    make install-config; \
    mkdir -p /fuzz/install/include; \
    cp -v src/core.h src/ip_type.h src/rdns.h src/remotedns.h src/common.h src/debug.h src/allocator_thread.h src/mutex.h src/hash.h /fuzz/install/include/
