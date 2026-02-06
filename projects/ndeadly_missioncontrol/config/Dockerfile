ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV PREFIX=/fuzz/install \
    SRC=/fuzz/src

# Create and install a tiny static library shim for linking/testing
RUN set -eux; \
mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build
RUN cat > /tmp/build/missioncontrol_shim.cpp <<'EOF'
#include <cstring>
extern "C" int mc_sum_bytes(const unsigned char* data, int len) {
    int s = 0; if (!data || len <= 0) return 0;
    for (int i = 0; i < len; ++i) s += data[i];
    return s;
}
EOF
RUN cat > ${PREFIX}/include/missioncontrol_shim.h <<'EOF'
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
int mc_sum_bytes(const unsigned char* data, int len);
#ifdef __cplusplus
}
#endif
EOF

RUN set -eux; \
    gf_libafl_cxx -O2 -fPIC -c /tmp/build/missioncontrol_shim.cpp -o /tmp/build/missioncontrol_shim.o; \
    ar rcs ${PREFIX}/lib/libmissioncontrol_shim.a /tmp/build/missioncontrol_shim.o; \
    ranlib ${PREFIX}/lib/libmissioncontrol_shim.a; \
    rm -rf /tmp/build
