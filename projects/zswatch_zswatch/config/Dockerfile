ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to build a tiny static library
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install a minimal static library and public headers subset that are toolchain-only
# Note: The full firmware project requires Zephyr; for fuzzing we expose portable headers.
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/build && \
    printf "int zswatch_dummy(void){return 42;}" > dummy.c && \
    ${CC} -c dummy.c -o dummy.o && \
    ar rcs libzswatch.a dummy.o && \
    cp libzswatch.a /fuzz/install/lib/

# Install selected public headers that are independent of Zephyr
RUN install -m 0644 /fuzz/src/app/src/zsw_settings.h /fuzz/install/include/zsw_settings.h && \
    install -m 0644 /fuzz/src/app/src/zsw_cpu_freq.h /fuzz/install/include/zsw_cpu_freq.h && \
    install -m 0644 /fuzz/src/app/src/zsw_retained_ram_storage.h /fuzz/install/include/zsw_retained_ram_storage.h
