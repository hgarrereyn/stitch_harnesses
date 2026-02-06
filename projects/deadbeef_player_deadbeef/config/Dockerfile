ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Create install prefix and install public headers only (sufficient for plugin API consumers)
RUN mkdir -p ${PREFIX}/include/deadbeef && cp -av include/deadbeef/*.h ${PREFIX}/include/deadbeef/
