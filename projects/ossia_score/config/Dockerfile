ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install prefix and copy a minimal subset of public headers for building harnesses
RUN mkdir -p /fuzz/install/include/score/tools && \
    install -D /fuzz/src/src/lib/score/tools/Clamp.hpp /fuzz/install/include/score/tools/Clamp.hpp && \
    install -D /fuzz/src/src/lib/score/tools/Version.hpp /fuzz/install/include/score/tools/Version.hpp

# No build needed for the minimal header-only test
