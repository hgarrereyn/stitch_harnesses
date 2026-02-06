ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and prepare install prefix
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libre2-dev \
 && rm -rf /var/lib/apt/lists/*

# "Build and install" re2 into /fuzz/install by copying system artifacts
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib && \
    cp -r /usr/include/re2 ${PREFIX}/include/ && \
    if [ -f /usr/lib/x86_64-linux-gnu/libre2.a ]; then cp /usr/lib/x86_64-linux-gnu/libre2.a ${PREFIX}/lib/; else cp /usr/lib/*/libre2.a ${PREFIX}/lib/; fi && \
    true

# Set compilers as requested for any subsequent compilation steps (none needed here)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
