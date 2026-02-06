ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library exposing DFHack version APIs
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        build-essential \
    ; \
    rm -rf /var/lib/apt/lists/*

# Prepare install dirs
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /fuzz/build

# Generate a minimal git-describe.h and build a static lib from DFHackVersion.cpp
WORKDIR /fuzz/src/library
RUN set -eux; \
    printf '%s\n' \
      '#define DFHACK_GIT_DESCRIPTION "dfhack-local-build"' \
      '#define DFHACK_GIT_COMMIT "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"' \
      '#define DFHACK_GIT_XML_COMMIT "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"' \
      '#define DFHACK_GIT_XML_EXPECTED_COMMIT "deadbeefdeadbeefdeadbeefdeadbeefdeadbeef"' \
      '/* define if this build corresponds to a tagged release */' \
      '/* #define DFHACK_GIT_TAGGED */' \
      '/* define if xml commit matches expected */' \
      '/* #define DFHACK_GIT_XML_MATCH */' \
      > include/git-describe.h

# Compile DFHackVersion.cpp into a static library
RUN set -eux; \
    gf_libafl_cxx -c DFHackVersion.cpp \
      -O2 -fPIC \
      -I./include \
      -DDFHACK_VERSION='"53.10-r1"' \
      -DDF_VERSION='"53.10"' \
      -DDFHACK_RELEASE='"r1"' \
      -DDFHACK_BUILD_ID='""' \
      -DDFHACK_ABI_VERSION=2 \
      -DDFHACK_RUN_URL='"https://dfhack.org/run"' \
      -o /fuzz/build/DFHackVersion.o; \
    ar rcs /fuzz/build/libdfhackversion.a /fuzz/build/DFHackVersion.o; \
    install -m 0644 /fuzz/build/libdfhackversion.a ${PREFIX}/lib/; \
    install -m 0644 include/DFHackVersion.h ${PREFIX}/include/

