ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static xdgmime library from WebKit ThirdParty sources
RUN set -eux; \
    export CC=stitch_libafl_cc AR=ar; \
    mkdir -p /fuzz/build /fuzz/install/include/xdgmime /fuzz/install/lib; \
    cd /fuzz/build; \
    INCLUDES="-I/fuzz/src/Source/ThirdParty/xdgmime/src"; \
    CFLAGS="-O2 -fPIC -DXDG_PREFIX=_wk_xdg -DLITTLE_ENDIAN=1"; \
    for f in \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimealias.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmime.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimeicon.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimeint.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimemagic.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimeparent.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimecache.c \
        /fuzz/src/Source/ThirdParty/xdgmime/src/xdgmimeglob.c; do \
        $CC $CFLAGS $INCLUDES -c "$f" -o "$(basename "$f").o"; \
    done; \
    $AR rcs /fuzz/install/lib/libxdgmime.a *.o; \
    cp -a /fuzz/src/Source/ThirdParty/xdgmime/src/*.h /fuzz/install/include/xdgmime/
