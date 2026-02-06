ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create install tree and a minimal stub static library to link against
WORKDIR /fuzz
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/includes \
 && cp /fuzz/src/src/includes/*.h /fuzz/install/include/includes/ \
 && printf "void strawberry_stub(){}" > /tmp/stub.c \
 && gf_libafl_cc -c /tmp/stub.c -o /tmp/stub.o \
 && ar crs /fuzz/install/lib/libstrawberry_lib.a /tmp/stub.o \
 && rm -f /tmp/stub.c /tmp/stub.o
