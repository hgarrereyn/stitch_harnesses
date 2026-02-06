ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for liblwgeom (no PostgreSQL server needed)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    make ninja-build gcc g++ \
    flex bison \
    perl \
    libxml2-dev \
    libgeos-dev \
    libproj-dev \
    gettext \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Generate build system and configure without heavy optional components
RUN ./autogen.sh
RUN ./configure --prefix=/fuzz/install --with-pgconfig=no \
    --without-protobuf \
    --without-raster \
    --without-topology \
    --without-address-standardizer \
    --with-gui=no \
    --without-interrupt-tests

# Build only liblwgeom and stage artifacts manually
RUN make -j"$(nproc)"

# Install headers and static library into /fuzz/install
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include/liblwgeom/topo; \
    cp liblwgeom/.libs/liblwgeom.a /fuzz/install/lib/; \
    cp postgis_config.h /fuzz/install/include/; \
    cp postgis_revision.h /fuzz/install/include/; \
    cp liblwgeom/*.h /fuzz/install/include/liblwgeom/; \
    if [ -d liblwgeom/topo ]; then cp liblwgeom/topo/*.h /fuzz/install/include/liblwgeom/topo/; fi
