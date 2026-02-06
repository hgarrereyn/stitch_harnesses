ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config \
    libglib2.0-dev libglib2.0-dev-bin \
    libssl-dev \
  && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure with minimal feature set to reduce external deps
RUN meson setup build \
    --prefix=/fuzz/install \
    -Dservice=false -Dnetwork=false -Dstreaming=false \
    -Djson=disabled -Dgpt=disabled -Dcomposefs=disabled \
    -Dtests=false -Dmanpages=false -Dhtmldocs=false

RUN meson compile -C build
RUN meson install -C build || true

# Manually install headers and static library for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp -a include/*.h /fuzz/install/include/ \
    && cp -a build/librauc.a /fuzz/install/lib/ \
    && cp -a build/librauc.a.p /fuzz/install/lib/ \
    && sed -i 's/\bclass\b/klass/g' /fuzz/install/include/slot.h
