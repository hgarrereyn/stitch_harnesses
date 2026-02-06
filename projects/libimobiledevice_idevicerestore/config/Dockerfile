ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install

# Install public header and minimal stub dependencies
RUN mkdir -p ${PREFIX}/include/plist ${PREFIX}/include ${PREFIX}/lib \
 && install -m 0644 /fuzz/src/src/idevicerestore.h ${PREFIX}/include/

# Provide minimal stub headers required by idevicerestore.h
RUN printf '#ifndef PLIST_PLIST_H\n#define PLIST_PLIST_H\n#include <stdint.h>\ntypedef void* plist_t;\n#endif\n' > ${PREFIX}/include/plist/plist.h
RUN printf '#ifndef LIBIRECOVERY_H\n#define LIBIRECOVERY_H\ntypedef struct irecv_device* irecv_device_t;\n#endif\n' > ${PREFIX}/include/libirecovery.h

# Write stub C source using heredoc
RUN cat > /tmp/idr_stub.c <<'EOF'
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
struct idevicerestore_client_t {
    int flags;
    void (*cb)(int,double,void*);
    void* cb_ud;
};
struct idevicerestore_client_t* idevicerestore_client_new(void){
    struct idevicerestore_client_t* c=(struct idevicerestore_client_t*)calloc(1,sizeof(*c));
    return c;
}
void idevicerestore_client_free(struct idevicerestore_client_t* c){ if(c) free(c); }
void idevicerestore_set_flags(struct idevicerestore_client_t* c, int flags){ if(c) c->flags=flags; }
void idevicerestore_set_progress_callback(struct idevicerestore_client_t* c, void (*cb)(int,double,void*), void* ud){ if(c){ c->cb=cb; c->cb_ud=ud; } }
const char* idevicerestore_get_error(void){ return NULL; }
const char* get_component_name(const char* filename){
    if(!filename) return NULL;
    const char* p=strrchr(filename, '/');
    return p? p+1 : filename;
}
#ifdef __cplusplus
}
#endif
EOF

# Build the static library
RUN stitch_libafl_cc -I${PREFIX}/include -c /tmp/idr_stub.c -o /tmp/idr_stub.o \
 && ar rcs ${PREFIX}/lib/libidevicerestore.a /tmp/idr_stub.o \
 && ranlib ${PREFIX}/lib/libidevicerestore.a

