ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install WiringPi into /fuzz/install using the fuzzing toolchain
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /fuzz/src

# Build and install core wiringPi
RUN make -C wiringPi clean || true \
 && make -C wiringPi CC=stitch_libafl_cc EXTRA_CFLAGS="$CFLAGS" \
 && make -C wiringPi CC=stitch_libafl_cc DESTDIR=/fuzz/install PREFIX= install

# Build and install device library (wiringPiDev), include installed headers
RUN make -C devLib clean || true \
 && make -C devLib CC=stitch_libafl_cc EXTRA_CFLAGS="-I/fuzz/install/include $CFLAGS" \
 && make -C devLib CC=stitch_libafl_cc DESTDIR=/fuzz/install PREFIX= install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
