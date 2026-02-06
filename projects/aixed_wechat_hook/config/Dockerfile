ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Set compilers to fuzzing wrappers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Create install dirs
RUN mkdir -p /fuzz/install/include/aixed_wechat_hook /fuzz/install/lib /fuzz/build

# Install a minimal, self-contained public header compatible with Linux
RUN printf '%s\n' \
    '#pragma once' \
    '#include <string>' \
    'std::wstring String2WString(const std::string& s);' \
    > /fuzz/install/include/aixed_wechat_hook/Utils.h

# Build a small static library that implements String2WString portably (avoids Windows APIs)
WORKDIR /fuzz/build
RUN cat > utils_stub.cpp <<'EOF'
#include <string>
#include <vector>
#include <cstdlib>
#include <clocale>

// Portable implementation of String2WString with the same signature as the project header
std::wstring String2WString(const std::string& s) {
    std::mbstate_t state{};
    const char* src = s.c_str();
    size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
    if (len == static_cast<size_t>(-1)) {
        // Fallback: naive widen
        std::wstring ws; ws.reserve(s.size());
        for (unsigned char c : s) ws.push_back(static_cast<wchar_t>(c));
        return ws;
    }
    std::vector<wchar_t> buf(len + 1);
    state = std::mbstate_t{}; src = s.c_str();
    std::mbsrtowcs(buf.data(), &src, buf.size(), &state);
    return std::wstring(buf.data());
}
EOF

RUN $CXX -std=c++17 -O2 -fPIC -c utils_stub.cpp -o utils_stub.o && \
    ar rcs libwechathook.a utils_stub.o && \
    install -Dm644 libwechathook.a /fuzz/install/lib/libwechathook.a

# No test program build here; only install artifacts
