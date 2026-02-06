ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build static library with minimal dependencies
# Disable external compressors and extras to avoid third-party libs
RUN make -j \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    LDEF=0 LZMA=0 ZSTD=0 MD5=0 XXH=0 BSD=0 VCD=0 BZIP2=0 DIR_DIFF=1 \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp libhdiffpatch.a /fuzz/install/lib/ \
 && mkdir -p /fuzz/install/include/libHDiffPatch /fuzz/install/include/dirDiffPatch \
 && cp -r libHDiffPatch/HDiff /fuzz/install/include/libHDiffPatch/ \
 && cp -r libHDiffPatch/HPatch /fuzz/install/include/libHDiffPatch/ \
 && cp -r libHDiffPatch/HPatchLite /fuzz/install/include/libHDiffPatch/ \
 && mkdir -p /fuzz/install/include/dirDiffPatch/dir_diff /fuzz/install/include/dirDiffPatch/dir_patch \
 && cp dirDiffPatch/dir_diff/*.h /fuzz/install/include/dirDiffPatch/dir_diff/ \
 && cp dirDiffPatch/dir_patch/*.h /fuzz/install/include/dirDiffPatch/dir_patch/
