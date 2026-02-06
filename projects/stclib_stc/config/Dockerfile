ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Install a recent Meson via pip (project requires >=1.1)
RUN python3 -m pip install --no-cache-dir --upgrade pip && \
    python3 -m pip install --no-cache-dir 'meson>=1.1'

# Configure, build, and install STC using meson
WORKDIR /fuzz/src
ENV DESTDIR=
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx meson setup build --buildtype=release --prefix /fuzz/install -Ddefault_library=static
RUN meson compile -C build
RUN meson install -C build
