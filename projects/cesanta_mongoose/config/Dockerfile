ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install Mongoose as a static library into /fuzz/install
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        binutils \
        make \
    ; \
    rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

# Compile static library and install headers
RUN set -eux; \
    mkdir -p "$PREFIX/include" "$PREFIX/lib"; \
    cd /fuzz/src; \
    "$CC" -O2 -fPIC -DMG_ENABLE_LINES=0 -c mongoose.c -o mongoose.o; \
    ar rcs libmongoose.a mongoose.o; \
    install -m 0644 mongoose.h "$PREFIX/include/mongoose.h"; \
    install -m 0644 libmongoose.a "$PREFIX/lib/libmongoose.a"; \
    rm -f mongoose.o libmongoose.a
