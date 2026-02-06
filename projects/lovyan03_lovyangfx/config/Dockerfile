ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install SDL2 for the PC backend
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libsdl2-dev \
 && rm -rf /var/lib/apt/lists/*

# Build a static LovyanGFX library (SDL backend) and install headers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

RUN mkdir -p /fuzz/build && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include && \
    cd /fuzz/build && \
    SRC_ROOT=/fuzz/src && \
    INCDIR=${SRC_ROOT}/src && \
    CFLAGS="-O2 -fPIC -DLGFX_SDL -I${INCDIR}" && \
    CXXFLAGS="-O2 -fPIC -DLGFX_SDL -I${INCDIR}" && \
    find ${INCDIR}/lgfx/utility -maxdepth 1 -name '*.c' > c_srcs.txt && \
    find ${INCDIR}/lgfx/Fonts/efont -maxdepth 1 -name '*.c' >> c_srcs.txt && \
    find ${INCDIR}/lgfx/Fonts/IPA -maxdepth 1 -name '*.c' >> c_srcs.txt && \
    find ${INCDIR}/lgfx/v1 -maxdepth 1 -name '*.cpp' > cpp_srcs.txt && \
    find ${INCDIR}/lgfx/v1/misc -maxdepth 1 -name '*.cpp' >> cpp_srcs.txt && \
    echo ${INCDIR}/lgfx/v1/panel/Panel_Device.cpp >> cpp_srcs.txt && \
    echo ${INCDIR}/lgfx/v1/panel/Panel_FrameBufferBase.cpp >> cpp_srcs.txt && \
    find ${INCDIR}/lgfx/v1/platforms/sdl -maxdepth 1 -name '*.cpp' >> cpp_srcs.txt && \
    mkdir -p obj && \
    for f in $(cat c_srcs.txt); do \
      echo "Compiling C $f"; \
      ${CC} ${CFLAGS} -c "$f" -o obj/$(basename "$f").o; \
    done && \
    for f in $(cat cpp_srcs.txt); do \
      echo "Compiling C++ $f"; \
      ${CXX} ${CXXFLAGS} -c "$f" -o obj/$(basename "$f").o; \
    done && \
    ar rcs ${PREFIX}/lib/liblovyangfx.a obj/*.o && \
    cp -a ${INCDIR}/* ${PREFIX}/include/

