ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    git ca-certificates curl \
    make \
    libstfl-dev \
    libsqlite3-dev \
    libcurl4-openssl-dev \
    libxml2-dev \
    libjson-c-dev \
    gettext \
    asciidoctor \
    gawk \
    libncursesw6 libncurses-dev \
    && rm -rf /var/lib/apt/lists/*

# Install a recent Rust (stable) via rustup, required >= 1.90
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo PATH=/opt/cargo/bin:$PATH
RUN curl -sSf https://sh.rustup.rs | sh -s -- -y --profile minimal --default-toolchain stable && \
    rustc --version && cargo --version

# Build static libraries and prepare install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx CXX_FOR_BUILD=stitch_libafl_cxx
WORKDIR /fuzz/src

# Configure and build
RUN ./config.sh && \
    make -j$(nproc)

# Install headers and static libraries to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -a include/*.h /fuzz/install/include/ && \
    cp -a stfl/*.h /fuzz/install/include/ || true && \
    cp -a libboat.a librsspp.a libfilter.a /fuzz/install/lib/ && \
    cp -a target/release/libnewsboat.a /fuzz/install/lib/
