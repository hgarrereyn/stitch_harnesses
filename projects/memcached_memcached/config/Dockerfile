ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create install prefix and install headers manually (sufficient for fuzzing)
RUN mkdir -p /fuzz/install/include
COPY . /fuzz/src
RUN cp /fuzz/src/protocol_binary.h /fuzz/install/include/ && \
    cp /fuzz/src/xxhash.h /fuzz/install/include/
