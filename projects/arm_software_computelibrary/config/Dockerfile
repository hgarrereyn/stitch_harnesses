ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build: install headers and build a tiny static lib that exposes AclVersionInfo
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Install headers and create a minimal static library implementing AclVersionInfo
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp -r /fuzz/src/arm_compute /fuzz/install/include/ && \
    cp -r /fuzz/src/include/* /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/include && \
    cp -r /fuzz/src/include/CL /fuzz/install/include/include/ && \
    cp -r /fuzz/src/utils /fuzz/install/include/ && \
    cp -r /fuzz/src/support /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/third_party && \
    cp -r /fuzz/src/third_party/kleidiai /fuzz/install/include/third_party/ && \
    mkdir -p /tmp/aclbuild && \
    printf "\"fuzz build\"" > /tmp/aclbuild/arm_compute_version.embed && \
    stitch_libafl_cxx -I/fuzz/src -I/tmp/aclbuild -c /fuzz/src/src/c/AclVersion.cpp -o /tmp/aclbuild/AclVersion.o && \
    ar rcs /fuzz/install/lib/libarm_compute.a /tmp/aclbuild/AclVersion.o
