ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install Ruby and build deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ruby \
    ruby-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    AR=llvm-ar \
    RANLIB=llvm-ranlib \
    PREFIX=/fuzz/install

# Build the Ruby C extension and install artifacts
RUN set -eux; \
    mkdir -p "$PREFIX/lib" "$PREFIX/include/oj" "$PREFIX/lib/ruby/oj"; \
    cd /fuzz/src/ext/oj; \
    ruby extconf.rb; \
    make -j"$(nproc)"; \
    cp -v oj.so "$PREFIX/lib/"; \
    cp -v oj.so "$PREFIX/lib/ruby/oj/oj.so"; \
    cp -v *.h "$PREFIX/include/oj/"; \
    cd /fuzz/src/lib; \
    cp -v oj.rb "$PREFIX/lib/ruby/"; \
    cp -v oj/*.rb "$PREFIX/lib/ruby/oj/"
