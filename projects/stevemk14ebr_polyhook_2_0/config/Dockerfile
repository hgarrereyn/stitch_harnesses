ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies (if any)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build PolyHook_2 as a static library
ENV INSTALL_PREFIX=/fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DPOLYHOOK_BUILD_SHARED_LIB=OFF \
    -DPOLYHOOK_BUILD_DLL=ON \
    -DPOLYHOOK_USE_EXTERNAL_ASMTK=OFF \
    -DPOLYHOOK_USE_EXTERNAL_ASMJIT=OFF \
    -DPOLYHOOK_USE_EXTERNAL_ZYDIS=OFF \
 && cmake --build /fuzz/build --config Release --parallel \
 && cmake --install /fuzz/build || true \
 && mkdir -p ${INSTALL_PREFIX}/lib \
 && (test -f /fuzz/build/libPolyHook_2.a && cp /fuzz/build/libPolyHook_2.a ${INSTALL_PREFIX}/lib/ || true) \
 && (test -f /fuzz/build/zydis/libZydis.a && cp /fuzz/build/zydis/libZydis.a ${INSTALL_PREFIX}/lib/ || true) \
 && (test -f /fuzz/build/zydis/dependencies/zycore/libZycore.a && cp /fuzz/build/zydis/dependencies/zycore/libZycore.a ${INSTALL_PREFIX}/lib/ || true) \
 && (test -f /fuzz/build/asmtk/libasmtk.a && cp /fuzz/build/asmtk/libasmtk.a ${INSTALL_PREFIX}/lib/ || true) \
 && (test -f /fuzz/build/asmjit/libasmjit.a && cp /fuzz/build/asmjit/libasmjit.a ${INSTALL_PREFIX}/lib/ || true) \
 && find /fuzz/build -name "*.a" -exec cp {} ${INSTALL_PREFIX}/lib/ \; \
 && mkdir -p ${INSTALL_PREFIX}/include/polyhook2 \
 && cp -r /fuzz/src/polyhook2/* ${INSTALL_PREFIX}/include/polyhook2/ \
 && mkdir -p ${INSTALL_PREFIX}/include \
 && test -d /fuzz/src/asmjit/src && mkdir -p ${INSTALL_PREFIX}/include/asmjit && cp -r /fuzz/src/asmjit/src/* ${INSTALL_PREFIX}/include/asmjit/ || true \
 && test -d /fuzz/src/asmtk/src && mkdir -p ${INSTALL_PREFIX}/include/asmtk && cp -r /fuzz/src/asmtk/src/* ${INSTALL_PREFIX}/include/asmtk/ || true \
 && true
