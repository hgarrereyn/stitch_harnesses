ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
    pkg-config \
    libimlib2-dev \
    libx11-dev \
    libxt-dev \
    libpng-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV PREFIX=/fuzz/install
RUN make CC=stitch_libafl_cc curl=0 xinerama=0 exif=0 magic=0 help=0 && \
    make install CC=stitch_libafl_cc PREFIX=/fuzz/install curl=0 xinerama=0 exif=0 magic=0 help=0 && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    ar rcs /fuzz/install/lib/libfeh.a src/*.o && \
    cp -a src/*.h /fuzz/install/include/
