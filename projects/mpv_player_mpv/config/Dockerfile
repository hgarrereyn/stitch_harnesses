ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No heavy deps needed for stub build; just ensure basic tools and pkg-config
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config make && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Install public headers and build a minimal libmpv stub to satisfy linking
RUN mkdir -p /fuzz/install/include/mpv /fuzz/install/lib && \
    cp -r include/mpv/*.h /fuzz/install/include/mpv/ && \
    printf "#include <mpv/client.h>\nunsigned long mpv_client_api_version(void){return MPV_CLIENT_API_VERSION;}\nmpv_handle* mpv_create(void){return (mpv_handle*)0x1;}\nvoid mpv_terminate_destroy(mpv_handle* ctx){(void)ctx;}\n" > /tmp/mpv_stub.c && \
    $CC -fPIC -c /tmp/mpv_stub.c -I/fuzz/install/include -o /tmp/mpv_stub.o && \
    ar rcs /fuzz/install/lib/libmpv.a /tmp/mpv_stub.o && \
    ranlib /fuzz/install/lib/libmpv.a
