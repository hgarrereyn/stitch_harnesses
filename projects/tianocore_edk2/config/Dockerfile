ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building BaseTools C Common library
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Build the BaseTools Common static library with the fuzzing compiler wrappers
WORKDIR /fuzz/src/BaseTools/Source/C/Common
ENV CC=stitch_libafl_cc
# Build only the Common library to avoid extra tool dependencies
RUN make HOST_ARCH=X64

# Install the static library and headers into /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -v ../libs/libCommon.a /fuzz/install/lib/ \
 && cp -v *.h /fuzz/install/include/ \
 && cp -rv ../Include/Common /fuzz/install/include/ \
 && cp -rv ../Include/Guid /fuzz/install/include/ \
 && cp -rv ../Include/Protocol /fuzz/install/include/ \
 && mkdir -p /fuzz/install/include/MdePkg \
 && cp -rv /fuzz/src/MdePkg/Include /fuzz/install/include/MdePkg/
