ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    meson ninja-build pkg-config \
    libglib2.0-dev libssl-dev \
    binutils \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install only the needed static library and headers
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure with Meson: disable frontends and extras, prefer static library for project targets
RUN meson setup Build \
      --prefix=/fuzz/install \
      -Ddefault_library=static \
      -Dwithout-textui=yes \
      -Dwith-perl=no \
      -Dwith-otr=no \
      -Ddisable-utf8proc=yes \
      -Dinstall-glib=no

# Build and install headers (and any libs that Meson installs)
RUN ninja -C Build install

# Repack libirssi_config as a non-thin static archive and install it
RUN mkdir -p /fuzz/install/lib && \
    ar rcs /fuzz/install/lib/libirssi_config.a Build/src/lib-config/libirssi_config.a.p/*.o
