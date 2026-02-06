ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (CMake >= 3.24 from Kitware repo) and minimal extras
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    gpg \
    wget \
    ca-certificates \
    ninja-build \
    unzip \
    software-properties-common \
    lsb-release \
 && rm -rf /var/lib/apt/lists/*

# Add Kitware APT repository for newer CMake
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | \
    gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg && \
    echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" \
      > /etc/apt/sources.list.d/kitware.list && \
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake && \
    rm -rf /var/lib/apt/lists/*

# Build and install LIEF
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/build
RUN cmake -G Ninja /fuzz/src \
  -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  -DBUILD_SHARED_LIBS=OFF \
  -DLIEF_PYTHON_API=OFF \
  -DLIEF_EXAMPLES=OFF \
  -DLIEF_TESTS=OFF \
  -DLIEF_INSTALL=ON \
  -DCMAKE_BUILD_TYPE=Release
RUN ninja -j$(nproc) && ninja install
