ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a static sqlite3 library from the amalgamation in this repo
RUN set -eux; \
    mkdir -p /fuzz/install/include/sqlite3 /fuzz/install/lib; \
    cd /fuzz/src; \
    gf_libafl_cc -O2 -fPIC -DSQLITE_THREADSAFE=0 -DSQLITE_OMIT_LOAD_EXTENSION -c include/sqlite3/sqlite3.c -o /tmp/sqlite3.o; \
    ar rcs /tmp/libsqlite3.a /tmp/sqlite3.o; \
    ranlib /tmp/libsqlite3.a; \
    cp include/sqlite3/sqlite3.h include/sqlite3/sqlite3ext.h /fuzz/install/include/sqlite3/; \
    cp /tmp/libsqlite3.a /fuzz/install/lib/
