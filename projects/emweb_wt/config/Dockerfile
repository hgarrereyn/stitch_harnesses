ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libboost-all-dev \
    zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DSHARED_LIBS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_FUZZ=OFF \
    -DENABLE_SSL=OFF \
    -DENABLE_HARU=OFF \
    -DENABLE_PANGO=OFF \
    -DENABLE_SQLITE=OFF \
    -DENABLE_POSTGRES=OFF \
    -DENABLE_FIREBIRD=OFF \
    -DENABLE_MYSQL=OFF \
    -DENABLE_MSSQLSERVER=OFF \
    -DENABLE_QT4=OFF \
    -DENABLE_QT5=OFF \
    -DENABLE_QT6=OFF \
    -DENABLE_OPENGL=OFF \
    -DCONNECTOR_FCGI=OFF \
    -DCONNECTOR_HTTP=OFF \
    -DWT_WRASTERIMAGE_IMPLEMENTATION=none \
    -DWT_CPP17_FILESYSTEM_IMPLEMENTATION=boost

RUN cmake --build /fuzz/build --target install -j$(nproc)
