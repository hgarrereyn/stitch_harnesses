ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    pkg-config \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build with Makefile and install into /fuzz/install (disable heavy optional deps)
WORKDIR /fuzz/src
RUN make -j"$(nproc)" \
    NO_TCLTK=YesPlease \
    NO_GETTEXT=YesPlease \
    NO_PERL=YesPlease \
    NO_PYTHON=YesPlease \
    NO_CURL=YesPlease \
    NO_EXPAT=YesPlease \
    NO_ICONV=YesPlease \
    DEVELOPER= \
    V= \
 && make install \
    prefix=/fuzz/install \
    NO_TCLTK=YesPlease \
    NO_GETTEXT=YesPlease \
    NO_PERL=YesPlease \
    NO_PYTHON=YesPlease \
    NO_CURL=YesPlease \
    NO_EXPAT=YesPlease \
    NO_ICONV=YesPlease

# Copy the static library to the install prefix (best effort)
RUN install -d /fuzz/install/lib && \
    if [ -f libgit.a ]; then cp libgit.a /fuzz/install/lib/; fi
