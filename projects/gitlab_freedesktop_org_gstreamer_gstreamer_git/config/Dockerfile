ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and meson
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    python3 python3-pip python3-setuptools python3-wheel \
    pkg-config git ca-certificates \
    build-essential \
    libglib2.0-dev libffi-dev zlib1g-dev \
 && pip3 install --no-cache-dir meson==1.4.0 \
 && rm -rf /var/lib/apt/lists/*

# Build and install GStreamer core statically from subproject, using system glib
WORKDIR /fuzz/src/subprojects/gstreamer
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN meson setup builddir \
      --prefix=/fuzz/install \
      --libdir=lib \
      --default-library=static \
      -Dauto_features=disabled \
      -Dtools=disabled \
      -Dexamples=disabled \
      --wrap-mode=nofallback \
  && meson compile -C builddir \
  && meson install -C builddir

