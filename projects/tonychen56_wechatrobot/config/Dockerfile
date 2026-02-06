ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools (ar for static libs)
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Build and install a minimal static library exposing a tiny subset of the project's headers
# Because the original project targets Windows (Visual Studio, MFC), it cannot be built on Linux.
# We provide a stub static library that matches the signatures in WeChatHelper/Function.h so that
# fuzzers can link against the API surface.

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include/WeChatHelper ${PREFIX}/lib && \
    cp -v /fuzz/src/WeChatHelper/Function.h ${PREFIX}/include/WeChatHelper/Function.h && \
    printf "%s\n" '#include <string>' \
    'using namespace std;' \
    'void AddWxUser(wchar_t* wxid, wchar_t* msg) {(void)wxid; (void)msg;}' \
    'void AntiRevoke() {}' \
    'void OpenUrl(wchar_t * Url) {(void)Url;}' \
    > /tmp/wechatrobot_stub.cpp && \
    ${CXX} -std=c++17 -O2 -fPIC -c /tmp/wechatrobot_stub.cpp -o /tmp/wechatrobot_stub.o && \
    ar rcs ${PREFIX}/lib/libwechatrobot.a /tmp/wechatrobot_stub.o && \
    rm -f /tmp/wechatrobot_stub.cpp /tmp/wechatrobot_stub.o
