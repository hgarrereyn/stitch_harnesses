ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra packages required. Prepare install layout and install headers + a dummy static library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp /fuzz/src/Multiprotocol/Multiprotocol.h /fuzz/install/include/ && \
    cp /fuzz/src/Multiprotocol/iface_*.h /fuzz/install/include/ && \
    printf "\n" > /tmp/dummy.c && \
    gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs /fuzz/install/lib/libmultiprotocol.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o

ENV CPATH=/fuzz/install/include
ENV LIBRARY_PATH=/fuzz/install/lib
