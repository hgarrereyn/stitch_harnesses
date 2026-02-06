ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra build deps if needed
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Install headers and create a minimal static library for linking
RUN set -eux; \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/scintilla; \
    cp -r scintilla/include/* ${PREFIX}/include/scintilla/; \
    echo 'int scintilla_stub(void) { return 0; }' > /tmp/scintilla_stub.c; \
    stitch_libafl_cc -c /tmp/scintilla_stub.c -o /tmp/scintilla_stub.o; \
    ar rcs ${PREFIX}/lib/libscintilla.a /tmp/scintilla_stub.o
