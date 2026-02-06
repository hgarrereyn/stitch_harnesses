ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to create a static archive
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# Prepare install dirs
RUN mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib
# Install a lightweight API header from the project directly from mounted source tree
RUN install -D /fuzz/src/main/rf/RFReceiver.h ${INSTALL_PREFIX}/include/RFReceiver.h
# Build an empty object and archive so linkers can resolve -lopenmqttgateway
RUN printf "int __omg_placeholder(void){return 0;}" > /tmp/placeholder.c \
 && ${CC} -c /tmp/placeholder.c -o /tmp/placeholder.o \
 && ar rcs ${INSTALL_PREFIX}/lib/libopenmqttgateway.a /tmp/placeholder.o \
 && rm -f /tmp/placeholder.c /tmp/placeholder.o
