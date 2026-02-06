ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Create install directories
RUN mkdir -p /fuzz/install/include/SafeInt /fuzz/install/lib

# Copy header-only library from the mounted source tree into the install prefix
RUN cp -r /fuzz/src/src/external/inc/SafeInt/*.hpp /fuzz/install/include/SafeInt/

# Build a tiny static library using the required compilers to satisfy linker
RUN bash -lc 'printf "int winui_stub_symbol = 0;\n" > /tmp/stub.c && \
    stitch_libafl_cc -c /tmp/stub.c -o /tmp/stub.o && \
    ar rcs /fuzz/install/lib/libwinui_stub.a /tmp/stub.o && \
    rm -f /tmp/stub.*'
