ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: Python dev headers and unixODBC
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-dev \
    unixodbc-dev \
    make \
 && rm -rf /var/lib/apt/lists/*

# Build a static library from the pyodbc C++ extension sources and install headers
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    CXX=stitch_libafl_cxx; \
    CFLAGS="$(odbc_config --cflags 2>/dev/null || true)"; \
    for f in /fuzz/src/src/*.cpp; do \
        "$CXX" -O2 -fPIC -I/fuzz/src/src -I/usr/include/python3.10 $CFLAGS -c "$f" -o "/fuzz/build/$(basename "${f%.cpp}").o"; \
    done; \
    ar rcs /fuzz/install/lib/libpyodbc.a /fuzz/build/*.o; \
    cp /fuzz/src/src/*.h /fuzz/install/include/
