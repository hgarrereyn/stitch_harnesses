ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-pip pkg-config \
    glib2.0-bin libglib2.0-dev libglib2.0-dev-bin \
    libjpeg-dev libpng-dev libtiff-dev \
    ca-certificates \
 && pip3 install --no-cache-dir 'meson>=1.5,<1.6' \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install gdk-pixbuf statically
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN meson setup _build . \
      --prefix=/fuzz/install \
      -Ddefault_library=static \
      -Ddocumentation=false \
      -Dintrospection=disabled \
      -Dtests=false \
      -Dthumbnailer=disabled \
      -Dgio_sniffing=false \
      -Dglycin=disabled \
      -Dman=false \
      -Dbuiltin_loaders=png,jpeg \
    && meson compile -C _build \
    && meson install -C _build
