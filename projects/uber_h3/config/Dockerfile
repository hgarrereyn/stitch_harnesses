ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install uber/h3 (C library) statically into /fuzz/install

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

RUN set -eux; \
    mkdir -p /fuzz/install; \
    mkdir -p build; cd build; \
    cmake -G "Unix Makefiles" \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_TESTING=OFF \
      -DBUILD_FILTERS=OFF \
      -DBUILD_GENERATORS=OFF \
      -DBUILD_BENCHMARKS=OFF \
      -DBUILD_FUZZERS=OFF \
      -DENABLE_DOCS=OFF \
      -DENABLE_LINTING=OFF \
      -DENABLE_FORMAT=OFF \
      ..; \
    make -j"$(nproc)"; \
    make install; \
    rm -rf /fuzz/src/build
