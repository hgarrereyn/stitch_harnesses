ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz

# Install prefix directories
RUN mkdir -p /fuzz/install/bin /fuzz/install/include /fuzz/install/include/api /fuzz/install/lib

# Install headers (omit window.h to avoid GUI deps)
RUN set -eux; \
    cp -v /fuzz/src/errors.h /fuzz/src/helpers.h /fuzz/src/resources.h /fuzz/src/settings.h /fuzz/src/extensions_loader.h /fuzz/src/chrome.h /fuzz/install/include/; \
    for d in app clipboard computer custom debug events extensions fs os res server storage; do \
      mkdir -p /fuzz/install/include/api/$d; \
      cp -v /fuzz/src/api/$d/*.h /fuzz/install/include/api/$d/; \
    done; \
    # Provide third-party header(s) referenced directly by public headers
    mkdir -p /fuzz/install/include/lib/json; \
    cp -v /fuzz/src/lib/json/json.hpp /fuzz/install/include/lib/json/

# Create a tiny static library exposing a small subset of the API for linking
RUN set -eux; \
    printf '%s\n' '#include <cstdint>' '#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)' '#include <unistd.h>' '#elif defined(_WIN32)' '#define _WINSOCKAPI_' '#include <windows.h>' '#endif' 'namespace app { unsigned int getProcessId() {' '#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)' 'return getpid();' '#elif defined(_WIN32)' 'return GetCurrentProcessId();' '#endif' '}}' > /tmp/mini.cpp; \
    gf_libafl_cxx -O2 -fPIC -c /tmp/mini.cpp -o /tmp/app.o; \
    ar rcs /fuzz/install/lib/libneutralinojs_api.a /tmp/app.o; \
    rm -f /tmp/mini.cpp /tmp/app.o
