ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install static libFraunhoferAAC and public headers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    make ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build all cpp files into a single static library and install selected public headers
RUN set -eux; \
    mkdir -p /fuzz/build "$PREFIX"/lib "$PREFIX"/include; \
    cd /fuzz/src; \
    INCLUDES="-IlibAACdec/include -IlibAACenc/include -IlibPCMutils/include -IlibFDK/include -IlibSYS/include -IlibMpegTPDec/include -IlibMpegTPEnc/include -IlibSBRdec/include -IlibSBRenc/include -IlibArithCoding/include -IlibDRCdec/include -IlibSACdec/include -IlibSACenc/include"; \
    for d in libAACdec libAACenc libPCMutils libFDK libSYS libMpegTPDec libMpegTPEnc libSBRdec libSBRenc libArithCoding libDRCdec libSACdec libSACenc; do \
      for f in $d/src/*.cpp; do \
        [ -f "$f" ] || continue; \
        $CXX -c -O2 -fPIC $INCLUDES "$f" -o "/fuzz/build/$(basename "$f" .cpp).o"; \
      done; \
    done; \
    ar rcs "$PREFIX"/lib/libFraunhoferAAC.a /fuzz/build/*.o; \
    # Install headers from all exported include directories (including subdirectories)
    for d in libAACdec/include libAACenc/include libPCMutils/include libFDK/include libSYS/include libMpegTPDec/include libMpegTPEnc/include libSBRdec/include libSBRenc/include libArithCoding/include libDRCdec/include libSACdec/include libSACenc/include; do \
      cp -r "$d"/* "$PREFIX"/include/; \
    done
