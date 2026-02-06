ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Provide headers and a dummy static library for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib
WORKDIR /fuzz/src
RUN cp -r include/* /fuzz/install/include/ && \
    ar rcs /fuzz/install/lib/libseastar.a
