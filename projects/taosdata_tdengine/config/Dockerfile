ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

# Install public headers into /fuzz/install for building fuzz harnesses
RUN mkdir -p /fuzz/install/include \
 && cp -r include/client /fuzz/install/include/
