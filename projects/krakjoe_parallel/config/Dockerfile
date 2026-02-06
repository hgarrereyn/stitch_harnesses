ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies required for installing minimal headers
# Create install prefix and install a minimal static library and headers
RUN set -eux; \
    mkdir -p /fuzz/install/include/parallel /fuzz/install/lib; \
    cp /fuzz/src/src/monitor.h /fuzz/install/include/parallel/monitor.h; \
    # Build a tiny dummy object and archive it as libparallel.a
    echo 'void __parallel_dummy(void){}' | gf_libafl_cc -x c -c - -o /tmp/parallel_dummy.o; \
    ar rcs /fuzz/install/lib/libparallel.a /tmp/parallel_dummy.o; \
    rm -f /tmp/parallel_dummy.o
