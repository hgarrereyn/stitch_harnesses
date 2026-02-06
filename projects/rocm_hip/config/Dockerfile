ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install and "build" headers-only HIP: copy headers and generate hip_version.h. Also build a tiny static stub to satisfy static-only builds if needed.
RUN set -eux; \
    mkdir -p /fuzz/install/include/hip; \
    cp -r /fuzz/src/include/hip/* /fuzz/install/include/hip/; \
    # Generate missing hip_version.h from VERSION file
    ver_major=$(awk 'NR==2{print $0}' /fuzz/src/VERSION); \
    ver_minor=$(awk 'NR==4{print $0}' /fuzz/src/VERSION); \
    ver_patch=$(awk 'NR==6{print $0}' /fuzz/src/VERSION); \
    cat > /fuzz/install/include/hip/hip_version.h <<EOF
#ifndef HIP_INCLUDE_HIP_HIP_VERSION_H
#define HIP_INCLUDE_HIP_HIP_VERSION_H
#define HIP_VERSION_MAJOR ${ver_major}
#define HIP_VERSION_MINOR ${ver_minor}
#define HIP_VERSION_PATCH ${ver_patch}
#define HIP_VERSION ((HIP_VERSION_MAJOR)*100*100000 + (HIP_VERSION_MINOR)*100000 + (HIP_VERSION_PATCH))
#endif
EOF

# Create a minimal static library stub (not required by test program, but useful for linking-only scenarios)
RUN set -eux; \
    mkdir -p /fuzz/install/lib; \
    echo 'int hip_stub(void){return 0;}' > /tmp/hip_stub.c; \
    CC=stitch_libafl_cc stitch_libafl_cc -c /tmp/hip_stub.c -o /tmp/hip_stub.o; \
    ar rcs /fuzz/install/lib/libhip_stub.a /tmp/hip_stub.o; \
    rm -f /tmp/hip_stub.c /tmp/hip_stub.o
