ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static KCodecs library (stub) to enable fuzzing/linking
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx INSTALL_PREFIX=/fuzz/install
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/KF6/KCodecs

# Create a minimal public API header compatible enough for testing
RUN set -eux; \
  { \
    printf '#pragma once\n'; \
    printf '#include <string>\n'; \
    printf '#include <string_view>\n'; \
    printf '#include <cstring>\n'; \
    printf 'class QByteArray {\n'; \
    printf 'public:\n'; \
    printf '    QByteArray() = default;\n'; \
    printf '    QByteArray(const char* s) : data_(s) {}\n'; \
    printf '    QByteArray(std::string s) : data_(std::move(s)) {}\n'; \
    printf '    bool isEmpty() const { return data_.empty(); }\n'; \
    printf '    const char* constData() const { return data_.c_str(); }\n'; \
    printf '    const char* data() const { return data_.c_str(); }\n'; \
    printf '    size_t size() const { return data_.size(); }\n'; \
    printf '    void append(char c) { data_.push_back(c); }\n'; \
    printf '    void append(const char* s, size_t n) { data_.append(s, n); }\n'; \
    printf '    std::string& str() { return data_; }\n'; \
    printf '    const std::string& str() const { return data_; }\n'; \
    printf 'private:\n'; \
    printf '    std::string data_;\n'; \
    printf '};\n'; \
    printf 'class QByteArrayView {\n'; \
    printf 'public:\n'; \
    printf '    QByteArrayView() : ptr_(nullptr), len_(0) {}\n'; \
    printf '    QByteArrayView(const QByteArray& ba) : ptr_(ba.data()), len_(ba.size()) {}\n'; \
    printf '    QByteArrayView(const char* s) : ptr_(s), len_(strlen(s)) {}\n'; \
    printf '    QByteArrayView(const char* p, size_t n) : ptr_(p), len_(n) {}\n'; \
    printf '    const char* data() const { return ptr_; }\n'; \
    printf '    size_t size() const { return len_; }\n'; \
    printf 'private:\n'; \
    printf '    const char* ptr_;\n'; \
    printf '    size_t len_;\n'; \
    printf '};\n'; \
    printf 'namespace KCodecs {\n'; \
    printf 'QByteArray base64Encode(QByteArrayView in, bool useCRLF = true);\n'; \
    printf '}\n'; \
  } > /fuzz/build/kcodecs.h

# Implement a tiny Base64 encoder for the stub API
RUN set -eux; \
  { \
    printf '#include "kcodecs.h"\n'; \
    printf 'namespace { static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; }\n'; \
    printf 'namespace KCodecs {\n'; \
    printf 'QByteArray base64Encode(QByteArrayView in, bool) {\n'; \
    printf '    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(in.data());\n'; \
    printf '    size_t len = in.size();\n'; \
    printf '    QByteArray out;\n'; \
    printf '    out.str().reserve(((len + 2) / 3) * 4);\n'; \
    printf '    for (size_t i = 0; i < len; i += 3) {\n'; \
    printf '        unsigned int v = bytes[i] << 16;\n'; \
    printf '        if (i + 1 < len) v |= bytes[i + 1] << 8;\n'; \
    printf '        if (i + 2 < len) v |= bytes[i + 2];\n'; \
    printf '        out.append(b64_table[(v >> 18) & 0x3F]);\n'; \
    printf '        out.append(b64_table[(v >> 12) & 0x3F]);\n'; \
    printf '        if (i + 1 < len) out.append(b64_table[(v >> 6) & 0x3F]); else out.append('"'='"');\n'; \
    printf '        if (i + 2 < len) out.append(b64_table[v & 0x3F]); else out.append('"'='"');\n'; \
    printf '    }\n'; \
    printf '    return out;\n'; \
    printf '}\n'; \
    printf '}\n'; \
  } > /fuzz/build/kcodecs_stub.cpp

# Build static library and install headers
RUN $CXX -O2 -fPIC -c /fuzz/build/kcodecs_stub.cpp -o /fuzz/build/kcodecs_stub.o \
 && ar rcs /fuzz/install/lib/libKF6Codecs.a /fuzz/build/kcodecs_stub.o \
 && cp /fuzz/build/kcodecs.h /fuzz/install/include/KF6/KCodecs/kcodecs.h
