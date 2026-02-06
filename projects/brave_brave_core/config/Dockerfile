ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra packages are required; we'll install public headers only

# Create install directories and copy header-only public API from mounted source tree
RUN mkdir -p /fuzz/install/include/brave/components/brave_ads/core/public \
 && cp /fuzz/src/components/brave_ads/core/public/ads_constants.h /fuzz/install/include/brave/components/brave_ads/core/public/ads_constants.h || (echo "Source not found" && ls -R /fuzz/src && false)

# Environment variables for potential future builds
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

# Nothing to build (header-only API installed)
