ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install step: stage public headers for development against Snort APIs
RUN mkdir -p /fuzz/install/include/snort/utils /fuzz/install/include/snort/main
RUN cp /fuzz/src/src/utils/bits.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/cpp_macros.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/endian.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/safec.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/util.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/util_cstring.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/utils/util_unfold.h /fuzz/install/include/snort/utils/ && \
    cp /fuzz/src/src/main/snort_types.h /fuzz/install/include/snort/main/ && \
    cp /fuzz/src/src/main/snort.h /fuzz/install/include/snort/main/
