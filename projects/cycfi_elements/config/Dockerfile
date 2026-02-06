ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git ca-certificates pkg-config ninja-build build-essential cmake \
    libcairo2-dev libfontconfig1-dev libfreetype6-dev libwebp-dev \
    libgtk-3-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src/lib -B /tmp/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DELEMENTS_HOST_UI_LIBRARY=gtk \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && cmake --build /tmp/build --target elements -j$(nproc)

# Install headers and library, plus headers of fetched dependencies (infra, asio)
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp /tmp/build/libelements.a /fuzz/install/lib/ \
 && cp -R /fuzz/src/lib/include/* /fuzz/install/include/ \
 && if [ -d /tmp/build/_deps/cycfi_infra-src/include ]; then cp -R /tmp/build/_deps/cycfi_infra-src/include/* /fuzz/install/include/; fi \
 && if [ -d /tmp/build/_deps/asio-src/asio/include ]; then cp -R /tmp/build/_deps/asio-src/asio/include/* /fuzz/install/include/; fi
