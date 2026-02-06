ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed (ar from binutils)
RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build and install a minimal static Skia library and headers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Copy public headers
RUN cp -r /fuzz/src/include/* /fuzz/install/include/

# Build a tiny static lib providing just enough symbols for tests
RUN cat > /tmp/miniskia.cpp <<'EOF'
#include "include/core/SkColor.h"
#include <algorithm>
#include <cmath>

static inline float clamp01(float x){return x<0?0:(x>1?1:x);} 

void SkRGBToHSV(U8CPU r, U8CPU g, U8CPU b, SkScalar hsv[3]) {
    float rf = r/255.0f, gf = g/255.0f, bf = b/255.0f;
    float cmax = std::max(rf, std::max(gf, bf));
    float cmin = std::min(rf, std::min(gf, bf));
    float delta = cmax - cmin;
    float h = 0.0f;
    if (delta != 0.0f) {
        if (cmax == rf) { h = 60.0f * fmodf(((gf - bf) / delta), 6.0f); }
        else if (cmax == gf) { h = 60.0f * (((bf - rf) / delta) + 2.0f); }
        else { h = 60.0f * (((rf - gf) / delta) + 4.0f); }
        if (h < 0) h += 360.0f;
    }
    float s = (cmax == 0.0f) ? 0.0f : (delta / cmax);
    float v = cmax;
    hsv[0] = h; hsv[1] = s; hsv[2] = v;
}

SkColor SkHSVToColor(U8CPU alpha, const SkScalar hsv[3]) {
    float h = hsv[0];
    float s = clamp01(hsv[1]);
    float v = clamp01(hsv[2]);
    if (s == 0.0f) {
        U8CPU vi = (U8CPU)lrintf(v * 255.0f);
        return SkColorSetARGB(alpha, vi, vi, vi);
    }
    h = fmodf(h, 360.0f); if (h < 0) h += 360.0f;
    float c = v * s;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    float rf=0, gf=0, bf=0;
    if      (h < 60)  { rf=c; gf=x; bf=0; }
    else if (h < 120) { rf=x; gf=c; bf=0; }
    else if (h < 180) { rf=0; gf=c; bf=x; }
    else if (h < 240) { rf=0; gf=x; bf=c; }
    else if (h < 300) { rf=x; gf=0; bf=c; }
    else              { rf=c; gf=0; bf=x; }
    U8CPU r = (U8CPU)lrintf((rf + m) * 255.0f);
    U8CPU g = (U8CPU)lrintf((gf + m) * 255.0f);
    U8CPU b = (U8CPU)lrintf((bf + m) * 255.0f);
    return SkColorSetARGB(alpha, r, g, b);
}

SkPMColor SkPreMultiplyARGB(U8CPU a, U8CPU r, U8CPU g, U8CPU b) {
    auto mul = [](U8CPU c, U8CPU a){ return (U8CPU)((c * a + 127) / 255); };
    return (a<<24) | (mul(r,a)<<16) | (mul(g,a)<<8) | (mul(b,a));
}

SkPMColor SkPreMultiplyColor(SkColor c) {
    return SkPreMultiplyARGB(SkColorGetA(c), SkColorGetR(c), SkColorGetG(c), SkColorGetB(c));
}
EOF

RUN cd /fuzz/src \
 && gf_libafl_cxx -DNDEBUG -O2 -fPIC -I. -c /tmp/miniskia.cpp -o /tmp/miniskia.o \
 && ar rcs /fuzz/install/lib/libskia.a /tmp/miniskia.o \
 && rm -f /tmp/miniskia.o /tmp/miniskia.cpp
