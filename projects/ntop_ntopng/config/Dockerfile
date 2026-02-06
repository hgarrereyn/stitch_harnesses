ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r include/*.h /fuzz/install/include/ && \
    ar rcs /fuzz/install/lib/libntopng.a
