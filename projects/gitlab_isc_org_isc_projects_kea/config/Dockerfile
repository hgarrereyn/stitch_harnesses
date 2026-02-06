ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install system build dependencies (minimal)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    ninja-build \
    pkg-config \
    python3 \
    python3-pip \
    libboost-dev \
    libboost-system-dev \
    libboost-thread-dev \
    liblog4cplus-dev \
    libssl-dev \
 && rm -rf /var/lib/apt/lists/*

# Install a recent Meson (project requires >= 1.1.0)
RUN python3 -m pip install --no-cache-dir --upgrade pip setuptools wheel && \
    python3 -m pip install --no-cache-dir 'meson>=1.4.0'

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN meson setup build \
    --prefix=/fuzz/install \
    --libdir=lib \
    --buildtype=release \
    -Dinstall_umask=0022 \
    -Dtests=disabled \
    -Dfuzz=disabled \
    -Dmysql=disabled \
    -Dpostgresql=disabled \
    -Dnetconf=disabled \
    -Dkrb5=disabled \
    -Dcrypto=openssl \
    -Dcpp_std=c++17

RUN meson compile -C build -j"$(nproc)"
RUN meson install -C build
