ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: provide a tiny subset of osgEarth API (Version) as a static lib
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        && rm -rf /var/lib/apt/lists/*

# Install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include/osgEarth ${PREFIX}/lib /tmp/build

# Provide a minimal Version header compatible with the test
RUN cat > ${PREFIX}/include/osgEarth/Version <<'EOF'
#pragma once

namespace osgEarth {
    struct Version { int major, minor, patch; };
    Version parseVersion(const char*);
}

extern "C" {
#define OSGEARTH_MAJOR_VERSION 3
#define OSGEARTH_MINOR_VERSION 7
#define OSGEARTH_PATCH_VERSION 3
#define OSGEARTH_SOVERSION 180
const char* osgEarthGetVersion();
const char* osgEarthGetSOVersion();
const char* osgEarthGetLibraryName();
}
EOF

# Build a tiny static library implementing the version functions
RUN cat > /tmp/build/version_shim.cpp <<'EOF'
#include <cstdio>
#include <cstring>
#include <string>
#include <osgEarth/Version>

extern "C" {
const char* osgEarthGetVersion() {
    static char buf[64];
    std::snprintf(buf, sizeof(buf), "%d.%d.%d build %d", OSGEARTH_MAJOR_VERSION, OSGEARTH_MINOR_VERSION, OSGEARTH_PATCH_VERSION, OSGEARTH_SOVERSION);
    return buf;
}
const char* osgEarthGetSOVersion() {
    static char buf[16];
    std::snprintf(buf, sizeof(buf), "%d", OSGEARTH_SOVERSION);
    return buf;
}
const char* osgEarthGetLibraryName() { return "osgEarth"; }
}

osgEarth::Version osgEarth::parseVersion(const char* in) {
    osgEarth::Version v{0,0,0};
    if (in) std::sscanf(in, "%d.%d.%d", &v.major, &v.minor, &v.patch);
    return v;
}
EOF

RUN gf_libafl_cxx -std=c++17 -I${PREFIX}/include -c /tmp/build/version_shim.cpp -o /tmp/build/version_shim.o && \
    ar rcs ${PREFIX}/lib/libosgEarth.a /tmp/build/version_shim.o && \
    rm -rf /tmp/build
