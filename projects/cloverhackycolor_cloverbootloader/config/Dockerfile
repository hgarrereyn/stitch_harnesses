ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build; \
    install -m 0644 /fuzz/src/PosixCompilation/xcode_utf_fixed.h /fuzz/install/include/; \
    true
RUN cat > /tmp/build/xcode_utf_fixed_min.cpp <<'EOF'
#include <wchar.h>
#include <cstddef>
extern "C" {
size_t wcslen_fixed(const wchar_t* s) { return ::wcslen(s); }
int wcsncmp_fixed(const wchar_t* s1, const wchar_t* s2, size_t n) { return ::wcsncmp(s1, s2, n); }
wchar_t* wcsstr_fixed(const wchar_t* haystack, const wchar_t* needle) { return const_cast<wchar_t*>(::wcsstr(haystack, needle)); }
void xcode_utf_fixed_tests(void) {}
}
EOF
RUN set -eux; \
    stitch_libafl_cxx -O2 -fPIC -c /tmp/build/xcode_utf_fixed_min.cpp -o /tmp/build/xcode_utf_fixed_min.o; \
    ar rcs /fuzz/install/lib/libxcodeutf.a /tmp/build/xcode_utf_fixed_min.o

ENV CPATH=/fuzz/install/include${CPATH:+:$CPATH} \
    LIBRARY_PATH=/fuzz/install/lib${LIBRARY_PATH:+:$LIBRARY_PATH} \
    LD_LIBRARY_PATH=/fuzz/install/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
