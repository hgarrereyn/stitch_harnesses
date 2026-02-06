ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p /tmp/build "$PREFIX/include" "$PREFIX/lib"; \
    cat > /tmp/build/mnr.c <<'EOF'
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void mnr_print(void) {
    printf("[Name] Multiplayer Networking Resources\n");
    printf("[Desc] A curated list of Multiplayer Game Network Programming Resources\n");
    printf("[Repo] https://github.com/0xFA11/MultiplayerNetworkingResources.git\n");
}

const char* mnr_repo(void) {
    return "https://github.com/0xFA11/MultiplayerNetworkingResources.git";
}

#ifdef __cplusplus
}
#endif
EOF

RUN set -eux; \
    cat > "$PREFIX/include/mnr.h" <<'EOF'
#ifndef MNR_H
#define MNR_H

#ifdef __cplusplus
extern "C" {
#endif

void mnr_print(void);
const char* mnr_repo(void);

#ifdef __cplusplus
}
#endif

#endif /* MNR_H */
EOF

RUN set -eux; \
    $CC -O2 -fPIC -c /tmp/build/mnr.c -o /tmp/build/mnr.o; \
    ar rcs /tmp/build/libmnr.a /tmp/build/mnr.o; \
    cp /tmp/build/libmnr.a "$PREFIX/lib/"; \
    echo 'Installed libmnr.a and mnr.h to /fuzz/install'
