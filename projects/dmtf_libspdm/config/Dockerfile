ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Create install directories and install headers only (static libs require upstream submodules)
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp -r include/* /fuzz/install/include/
