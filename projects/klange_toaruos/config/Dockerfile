ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (ar, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

# Build a static lib from portable toaru userspace libs
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/toaru \
 && ${CC} -O2 -DNDEBUG -fPIC -I${SRC}/base/usr/include -c ${SRC}/lib/list.c -o /tmp/list.o \
 && ${CC} -O2 -DNDEBUG -fPIC -I${SRC}/base/usr/include -c ${SRC}/lib/hashmap.c -o /tmp/hashmap.o \
 && ${CC} -O2 -DNDEBUG -fPIC -I${SRC}/base/usr/include -c ${SRC}/lib/tree.c -o /tmp/tree.o \
 && ${CC} -O2 -DNDEBUG -fPIC -I${SRC}/base/usr/include -c ${SRC}/lib/json.c -o /tmp/json.o \
 && ${CC} -O2 -DNDEBUG -fPIC -I${SRC}/base/usr/include -c ${SRC}/lib/confreader.c -o /tmp/confreader.o \
 && ar rcs ${PREFIX}/lib/libtoaru.a /tmp/list.o /tmp/hashmap.o /tmp/tree.o /tmp/json.o /tmp/confreader.o \
 && cp -a ${SRC}/base/usr/include/_cheader.h ${PREFIX}/include/ \
 && cp -a ${SRC}/base/usr/include/toaru/list.h ${PREFIX}/include/toaru/ \
 && cp -a ${SRC}/base/usr/include/toaru/hashmap.h ${PREFIX}/include/toaru/ \
 && cp -a ${SRC}/base/usr/include/toaru/tree.h ${PREFIX}/include/toaru/ \
 && cp -a ${SRC}/base/usr/include/toaru/json.h ${PREFIX}/include/toaru/ \
 && cp -a ${SRC}/base/usr/include/toaru/confreader.h ${PREFIX}/include/toaru/
