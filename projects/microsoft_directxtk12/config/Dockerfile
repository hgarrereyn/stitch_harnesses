ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates curl unzip && rm -rf /var/lib/apt/lists/*

# Install DirectXMath headers (dependency for SimpleMath)
RUN curl -L -o /tmp/directxmath.zip https://github.com/microsoft/DirectXMath/archive/refs/heads/master.zip \
    && unzip -q /tmp/directxmath.zip -d /tmp \
    && mkdir -p /usr/local/include \
    && cp -r /tmp/DirectXMath-*/Inc/* /usr/local/include/ \
    && rm -rf /tmp/directxmath.zip /tmp/DirectXMath-*

# Ensure sal.h exists for DirectXMath on non-Windows
RUN bash -lc 'if [ ! -f /usr/local/include/sal.h ]; then \
  printf "%s\n" \
  "#ifndef _FAKE_SAL_H_" \
  "#define _FAKE_SAL_H_" \
  "#define _In_" \
  "#define _In_opt_" \
  "#define _Out_" \
  "#define _Out_opt_" \
  "#define _In_reads_(x)" \
  "#define _In_reads_bytes_(x)" \
  "#define _Out_writes_(x)" \
  "#define _Out_writes_bytes_(x)" \
  "#define _Inout_" \
  "#define _Inout_opt_" \
  "#define _Ret_maybenull_" \
  "#define _Post_z_" \
  "#define _Post_equal_to_(x)" \
  "#define _Maybenull_" \
  "#define _Field_size_(x)" \
  "#define _Always_(x)" \
  "#define _Analysis_assume_(x)" \
  "#define _Use_decl_annotations_" \
  "#define _Success_(x)" \
  "#endif" \
  > /usr/local/include/sal.h; fi'

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Install headers and create a dummy static library for linking
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r /fuzz/src/Inc/* /fuzz/install/include/ && \
    ${CC} -c -x c /dev/null -o /tmp/empty.o && \
    ar rcs /fuzz/install/lib/libdirectxtk12.a /tmp/empty.o && \
    ranlib /fuzz/install/lib/libdirectxtk12.a && \
    printf "%s\n" \
    "#pragma once" \
    "typedef unsigned int UINT;" \
    "typedef long LONG;" \
    "typedef struct RECT { LONG left; LONG top; LONG right; LONG bottom; } RECT;" \
    > /fuzz/install/include/dx_compat.h
