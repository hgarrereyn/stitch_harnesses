ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install Qt5 minimal development packages
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      qtbase5-dev \
    && rm -rf /var/lib/apt/lists/*

# Build a static lib from qrtplib sources only, and install headers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN set -eux; \
    install -d /fuzz/install/lib /fuzz/install/include/qrtplib /tmp/qrtplib_build; \
    cd /tmp/qrtplib_build; \
    SRC=/fuzz/src/qrtplib; \
    INC_EXPORT=/fuzz/src/exports; \
    QINC1=/usr/include/x86_64-linux-gnu/qt5; \
    QINC2=/usr/include/x86_64-linux-gnu/qt5/QtCore; \
    QINC3=/usr/include/x86_64-linux-gnu/qt5/QtNetwork; \
    for f in \
      rtcpapppacket.cpp \
      rtcpbyepacket.cpp \
      rtcpcompoundpacket.cpp \
      rtcpcompoundpacketbuilder.cpp \
      rtcppacketbuilder.cpp \
      rtcprrpacket.cpp \
      rtcpscheduler.cpp \
      rtcpsdesinfo.cpp \
      rtcpsdespacket.cpp \
      rtcpsrpacket.cpp \
      rtpaddress.cpp \
      rtpcollisionlist.cpp \
      rtperrors.cpp \
      rtpinternalsourcedata.cpp \
      rtppacket.cpp \
      rtppacketbuilder.cpp \
      rtprandom.cpp \
      rtprandomrand48.cpp \
      rtprandomrands.cpp \
      rtprandomurandom.cpp \
      rtpsession.cpp \
      rtpsessionparams.cpp \
      rtpsessionsources.cpp \
      rtpsourcedata.cpp \
      rtpsources.cpp \
      rtptimeutilities.cpp \
      rtpudptransmitter.cpp; do \
        "$CXX" -O1 -fPIC -g -I"$SRC" -I"$INC_EXPORT" -I"$QINC1" -I"$QINC2" -I"$QINC3" -c "$SRC/$f" -o "$f.o"; \
    done; \
    ar rcs libqrtplib.a *.o; \
    ranlib libqrtplib.a; \
    cp libqrtplib.a /fuzz/install/lib/; \
    cp "$INC_EXPORT/export.h" /fuzz/install/include/qrtplib/; \
    cp "$SRC"/*.h /fuzz/install/include/qrtplib/
