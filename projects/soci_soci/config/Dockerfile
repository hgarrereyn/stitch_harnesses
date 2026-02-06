ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and a recent CMake via pip
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-pip \
    ninja-build \
    make \
 && pip3 install --no-cache-dir cmake \
 && rm -rf /var/lib/apt/lists/*

# Configure and build SOCI (core + empty backend) as static libs
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSOCI_SHARED=OFF -DBUILD_SHARED_LIBS=OFF \
    -DWITH_BOOST=OFF \
    -DSOCI_TESTS=OFF \
    -DSOCI_LTO=OFF \
    -DSOCI_EMPTY=ON \
    -DSOCI_DB2=OFF -DSOCI_FIREBIRD=OFF -DSOCI_MYSQL=OFF -DSOCI_ODBC=OFF -DSOCI_ORACLE=OFF -DSOCI_POSTGRESQL=OFF -DSOCI_SQLITE3=OFF \
 && cmake --build /fuzz/build --target install --config Release
