ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal deps (ensure cmake present)
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates curl ninja-build cmake && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure, build (header-only, but installs headers and pkg-config), and install
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_XDSP=OFF \
    -DBUILD_SHMATH=OFF && \
    cmake --build build --target install

# Provide sal.h required on non-Windows platforms
RUN curl -fsSL https://raw.githubusercontent.com/dotnet/runtime/main/src/coreclr/pal/inc/rt/sal.h -o /fuzz/install/include/sal.h
