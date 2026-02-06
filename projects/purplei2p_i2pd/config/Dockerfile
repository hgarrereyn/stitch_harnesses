ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    libboost-all-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/build
RUN cmake -S /fuzz/src/build -B /tmp/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_STATIC=ON \
    -DWITH_LIBRARY=ON \
    -DWITH_BINARY=OFF \
    -DBUILD_TESTING=OFF
RUN cmake --build /tmp/build --target install

RUN mkdir -p /fuzz/install/include/i2pd \
 && cp -v /fuzz/src/libi2pd/*.h /fuzz/install/include/i2pd/ \
 && cp -v /fuzz/src/libi2pd/*.hpp /fuzz/install/include/i2pd/ || true \
 && cp -v /fuzz/src/libi2pd_client/*.h /fuzz/install/include/i2pd/ \
 && cp -v /fuzz/src/i18n/*.h /fuzz/install/include/i2pd/ || true
