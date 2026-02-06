ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external deps needed; build a minimal static lib exposing some portable headers
RUN mkdir -p /fuzz/install/include/learnffmpeg /fuzz/install/lib /tmp/build && \
    cp /fuzz/src/app/src/main/cpp/common/ThreadSafeQueue.h /fuzz/install/include/learnffmpeg/ && \
    cp /fuzz/src/app/src/main/cpp/player/decoder/Decoder.h /fuzz/install/include/learnffmpeg/ && \
    printf "namespace learnffmpeg { void __dummy(){} }" > /tmp/build/dummy.cpp && \
    stitch_libafl_cxx -fPIC -c /tmp/build/dummy.cpp -o /tmp/build/dummy.o && \
    ar rcs /fuzz/install/lib/liblearnffmpeg.a /tmp/build/dummy.o && \
    rm -rf /tmp/build
