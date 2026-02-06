ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Dependencies and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    sqlite3 libsqlite3-dev \
    pkg-config ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Use the fuzzing compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz

# Configure, build and install a static PROJ without apps
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DBUILD_APPS=OFF \
    -DENABLE_TIFF=OFF \
    -DENABLE_CURL=OFF \
    -DNLOHMANN_JSON_ORIGIN=internal \
    -DEMBED_RESOURCE_FILES=ON
RUN cmake --build /fuzz/build -j$(nproc)
RUN cmake --install /fuzz/build
