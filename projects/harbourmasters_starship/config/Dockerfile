ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools and any needed libs (none strictly needed for our simple static lib)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Create install prefix and copy headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib
COPY . /fuzz/src
RUN cp -r /fuzz/src/include/* /fuzz/install/include/ || true

# Build a minimal static library exposing a tiny API that includes project headers
RUN printf "#include \"common.h\"\nextern \"C\" int starship_add(int a,int b){return a+b;}\n" > /tmp/starship_dummy.cpp \
 && gf_libafl_cxx -I/fuzz/install/include -c /tmp/starship_dummy.cpp -o /tmp/starship_dummy.o \
 && ar rcs /fuzz/install/lib/libstarship.a /tmp/starship_dummy.o \
 && rm -f /tmp/starship_dummy.cpp /tmp/starship_dummy.o

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV CMAKE_INSTALL_PREFIX=/fuzz/install
