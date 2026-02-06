ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies (none strictly required for the chosen headers)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    ca-certificates \
    pkg-config \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Copy public headers from the source tree mounted at /fuzz/src
RUN cp -R /fuzz/src/include/* /fuzz/install/include/

# Create a tiny object and archive it as a static library named like the project's static target
RUN echo "int __curaengine_dummy__ = 0;" > /tmp/dummy.c \
 && gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs /fuzz/install/lib/lib_CuraEngine.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o

# Set compilers as requested (for any further builds that may occur)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
