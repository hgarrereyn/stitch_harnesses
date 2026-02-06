ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies required by tools/configure
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    acpica-tools \
    libyajl-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build only the needed parts (headers + libs)
WORKDIR /fuzz/src/tools
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install
# Install Xen public headers used by libraries (belt and braces: also copy directly)
RUN make -C include install prefix=/fuzz/install && \
    mkdir -p /fuzz/install/include/xen && \
    cp -a /fuzz/src/xen/include/public/* /fuzz/install/include/xen/
# Build and install required libraries as static and copy to prefix lib dir
RUN make -C libs/toolcore install prefix=/fuzz/install nosharedlibs=y && \
    mkdir -p /fuzz/install/lib && \
    cp -a /fuzz/src/tools/libs/toolcore/libxentoolcore.* /fuzz/install/lib/ || true
RUN make -C libs/store install prefix=/fuzz/install nosharedlibs=y && \
    mkdir -p /fuzz/install/lib && \
    cp -a /fuzz/src/tools/libs/store/libxenstore.* /fuzz/install/lib/ || true
# Ensure xenstore headers are present in the install prefix
RUN install -d /fuzz/install/include && \
    cp -a /fuzz/src/tools/include/xenstore*.h /fuzz/install/include/ && \
    install -d /fuzz/install/include/xenstore-compat && \
    cp -a /fuzz/src/tools/include/xenstore-compat/*.h /fuzz/install/include/xenstore-compat/ && \
    ln -sf xenstore-compat/xs.h /fuzz/install/include/xs.h && \
    ln -sf xenstore-compat/xs_lib.h /fuzz/install/include/xs_lib.h
