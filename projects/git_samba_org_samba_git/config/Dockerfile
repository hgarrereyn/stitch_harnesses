ARG BASE_IMAGE
FROM ${BASE_IMAGE}

WORKDIR /fuzz/src

# Create install directories
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Build static libpopt.a from vendored third_party/popt with minimal config defines
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/popt.c -o popt.o \
 && $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/poptparse.c -o poptparse.o \
 && $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/popthelp.c -o popthelp.o \
 && $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/poptconfig.c -o poptconfig.o \
 && $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/lookup3.c -o lookup3.o \
 && $CC -O2 -fPIC -Ithird_party/popt \
    -DHAVE_STPCPY=1 -DHAVE_UNISTD_H=1 -DHAVE_FLOAT_H=1 -DHAVE_STRERROR=1 -DPACKAGE=\"popt\" -DPOPT_SYSCONFDIR=\"/etc\" \
    -c third_party/popt/poptint.c -o poptint.o \
 && ar rcs libpopt.a popt.o poptparse.o popthelp.o poptconfig.o lookup3.o poptint.o \
 && cp libpopt.a /fuzz/install/lib/

# Install headers
RUN cp third_party/popt/popt.h /fuzz/install/include/
