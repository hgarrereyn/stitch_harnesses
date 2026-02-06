ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create install prefix and provide minimal artifacts for building against headers
RUN mkdir -p /fuzz/install/include/wiliwili /fuzz/install/lib

# Copy public headers from the mounted source tree
RUN bash -lc 'shopt -s nullglob && cp -r /fuzz/src/wiliwili/include/* /fuzz/install/include/wiliwili/'

# Build and install a minimal static library to satisfy linkers (contains no functionality)
# Use the required compilers
RUN echo "int wiliwili_minimal_lib_dummy = 0;" > /tmp/dummy.c \
 && stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar crs /fuzz/install/lib/libwiliwili.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Done