ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install LLVM/Clang/LLDB development packages (Ubuntu 22.04 provides version 14)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    llvm-14-dev \
    clang-14 \
    libclang-14-dev \
    lldb-14 \
    liblldb-14-dev \
    libc++-14-dev \
    libc++abi-14-dev \
    zlib1g-dev \
    libzstd-dev \
    libtinfo-dev \
    libedit-dev \
    libxml2-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build static library liblldb_eval.a manually using the provided compilers
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/lldb-eval && \
    cd /fuzz/build && \
    SRCDIR=/fuzz/src && \
    INC_LLVM=/usr/lib/llvm-14/include && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/api.cc -o api.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/ast.cc -o ast.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/context.cc -o context.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/eval.cc -o eval.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/parser.cc -o parser.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/parser_context.cc -o parser_context.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/type.cc -o type.o && \
    $CXX -O2 -fPIC -I"$SRCDIR" -I"$INC_LLVM" -c "$SRCDIR"/lldb-eval/value.cc -o value.o && \
    ar rcs liblldb_eval.a api.o ast.o context.o eval.o parser.o parser_context.o type.o value.o && \
    cp liblldb_eval.a /fuzz/install/lib/ && \
    cp "$SRCDIR"/lldb-eval/api.h /fuzz/install/include/lldb-eval/

