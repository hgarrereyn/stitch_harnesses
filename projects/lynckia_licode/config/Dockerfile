ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra packages required. We'll install headers for a small header-only component.

RUN mkdir -p /fuzz/install/include/erizo/lib \
    && cp /fuzz/src/erizo/src/erizo/lib/Base64.h /fuzz/install/include/erizo/lib/Base64.h

ENV LICODE_INCLUDE=/fuzz/install/include
