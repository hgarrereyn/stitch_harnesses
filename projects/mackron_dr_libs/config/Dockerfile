ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies needed. Just install the public headers.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/install/include \
    && cp /fuzz/src/dr_wav.h /fuzz/install/include/ \
    && cp /fuzz/src/dr_flac.h /fuzz/install/include/ \
    && cp /fuzz/src/dr_mp3.h /fuzz/install/include/
