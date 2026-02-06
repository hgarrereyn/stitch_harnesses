ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none needed beyond build tools already present)
# We'll just ensure basic utilities are present
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Build and install a tiny static library exposing a reusable function from the repo's examples
# We create a small C file implementing buildConnect and a matching public header.
# Install prefix is /fuzz/install
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build

# Create header
RUN printf "#ifndef CKF_H\n#define CKF_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint buildConnect(const char *sIp, int sPort);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /tmp/build/ckf.h

# Create source implementing buildConnect based on tests/network/test08/client.c
RUN printf "#include <netinet/in.h>\n#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n#include <unistd.h>\n#include <arpa/inet.h>\n\nint buildConnect(const char *sIp, int sPort) {\n    int skFd;\n    if ((skFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {\n        return 0;\n    }\n    struct sockaddr_in srvAddr;\n    srvAddr.sin_family = AF_INET;\n    srvAddr.sin_addr.s_addr = inet_addr(sIp);\n    srvAddr.sin_port = htons(sPort);\n    if (connect(skFd, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0) {\n        close(skFd);\n        return 0;\n    }\n    return skFd;\n}\n" > /tmp/build/ckf.c

# Compile with specified compilers and create static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN $CC -fPIC -O2 -c /tmp/build/ckf.c -o /tmp/build/ckf.o && \
    ar rcs /tmp/build/libckf.a /tmp/build/ckf.o && \
    install -m 0644 /tmp/build/ckf.h ${PREFIX}/include/ckf.h && \
    install -m 0644 /tmp/build/libckf.a ${PREFIX}/lib/libckf.a && \
    rm -rf /tmp/build
