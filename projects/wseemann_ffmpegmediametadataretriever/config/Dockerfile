ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: FFmpeg development libraries and build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libbz2-dev \
    libzstd-dev \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Provide minimal Android stubs required by the project headers
RUN mkdir -p ${PREFIX}/include/android && \
    printf "#pragma once\n\
typedef struct ANativeWindow ANativeWindow;\n\
typedef struct {\n    void* bits;\n    int width;\n    int height;\n    int stride;\n    int format;\n} ANativeWindow_Buffer;\n\
static inline int ANativeWindow_setBuffersGeometry(ANativeWindow* /*window*/, int /*w*/, int /*h*/, int /*format*/) { return 0; }\n\
static inline int ANativeWindow_lock(ANativeWindow* /*window*/, ANativeWindow_Buffer* /*outBuffer*/, void* /*inOutDirtyBounds*/) { return 0; }\n\
static inline int ANativeWindow_unlockAndPost(ANativeWindow* /*window*/) { return 0; }\n\
static inline void ANativeWindow_release(ANativeWindow* /*window*/) {}\n" > ${PREFIX}/include/android/native_window_jni.h && \
    printf "#pragma once\n\
#define ANDROID_LOG_VERBOSE 2\n\
static inline int __android_log_print(int /*prio*/, const char* /*tag*/, const char* /*fmt*/, ...) { return 0; }\n" > ${PREFIX}/include/android/log.h

# Build a static library from the C sources only (no Android/JNI C++ wrappers)
WORKDIR /fuzz/src/native/src/main/jni/metadata

# Compile objects (force-include some missing standard headers)
RUN gf_libafl_cc -D WINDOW_FORMAT_RGBA_8888=1 -fPIC -I${PREFIX}/include -include string.h -include inttypes.h -c ffmpeg_utils.c -o /tmp/ffmpeg_utils.o && \
    gf_libafl_cc -D WINDOW_FORMAT_RGBA_8888=1 -fPIC -I${PREFIX}/include -include string.h -include inttypes.h -c ffmpeg_mediametadataretriever.c -o /tmp/ffmpeg_mediametadataretriever.o

# Create static archive
RUN ar rcs ${PREFIX}/lib/libfmmr.a /tmp/ffmpeg_utils.o /tmp/ffmpeg_mediametadataretriever.o

# Install public headers
RUN cp ffmpeg_mediametadataretriever.h ${PREFIX}/include/ && \
    cp ffmpeg_utils.h ${PREFIX}/include/
