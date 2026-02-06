ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends git binutils ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Initialize submodules (third-party dependency)
RUN git submodule update --init --recursive || true

# Build the project with fuzzing compilers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Use the C compiler for preprocessing dependency generation as well
RUN make -j"$(nproc)" CC=${CC} PP=${CC} STRIP=true

# Install: create a static archive from objects (exclude main) and copy headers and third-party deps
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/natmap && \
    ar rcs /fuzz/install/lib/libnatmap.a $(find build -maxdepth 1 -type f -name '*.o' ! -name 'hev-main.o') && \
    cp -r src/*.h /fuzz/install/include/natmap/ && \
    if [ -f third-part/hev-task-system/bin/libhev-task-system.a ]; then \
      cp third-part/hev-task-system/bin/libhev-task-system.a /fuzz/install/lib/; \
    fi && \
    if [ -d third-part/hev-task-system/include ]; then \
      mkdir -p /fuzz/install/include/ && cp -r third-part/hev-task-system/include /fuzz/install/include/hev-task-system; \
    fi && \
    if [ -d third-part/hev-task-system/src/lib/rbtree ]; then \
      cp -r third-part/hev-task-system/src/lib/rbtree /fuzz/install/include/hev-task-system-rbtree; \
    fi
