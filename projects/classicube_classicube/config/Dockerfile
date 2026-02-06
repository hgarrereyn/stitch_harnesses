ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Linux (X11, OpenGL, OpenAL)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    libx11-dev libxi-dev libgl1-mesa-dev \
    libopenal-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Build and install a static library from all compiled objects, excluding the program entry point
RUN make linux RELEASE=1 CC=gf_libafl_cc EXTRA_CFLAGS="-fPIC -ffunction-sections -fdata-sections" && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/classicube && \
    OBJ_FILES=$(find build/linux -type f -name '*.o' ! -name 'Platform_Posix.o') && \
    ar rcs ${PREFIX}/lib/libclassiscube.a ${OBJ_FILES} && \
    cp -a src/*.h ${PREFIX}/include/classicube/

ENV LIBRARY_PATH=${PREFIX}/lib
ENV CPATH=${PREFIX}/include:${PREFIX}/include/classicube
