ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install libwebp for webp_image.h and minimal build deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libwebp-dev \
 && rm -rf /var/lib/apt/lists/*

# Install headers to /fuzz/install/include (header-only library)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/install/include && \
    cp -v /fuzz/src/Resize-CLI/app/src/main/jni/stb_image.h /fuzz/install/include/ && \
    cp -v /fuzz/src/Resize-CLI/app/src/main/jni/stb_image_write.h /fuzz/install/include/ && \
    cp -v /fuzz/src/Resize-CLI/app/src/main/jni/stb_image_resize.h /fuzz/install/include/ && \
    cp -v /fuzz/src/Resize-CLI/app/src/main/jni/webp_image.h /fuzz/install/include/ && \
    cp -v /fuzz/src/Resize-CLI/app/src/main/jni/filesystem_utils.h /fuzz/install/include/
