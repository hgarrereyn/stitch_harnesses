ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Set compilers to libAFL wrappers as required
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Create install prefix
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /work && \
    cd /work && \
    printf "#ifndef DUIX_AVATAR_H\n#define DUIX_AVATAR_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint duix_avatar_version(void);\nconst char* duix_avatar_hello(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > duix_avatar.h && \
    printf "#include <stddef.h>\nint duix_avatar_version(void){return 106;}\nconst char* duix_avatar_hello(void){return \"Duix.Avatar stub\";}\n" > duix_avatar.c && \
    $CC -c duix_avatar.c -o duix_avatar.o && \
    ar rcs libduixavatar.a duix_avatar.o && \
    install -m 0644 duix_avatar.h /fuzz/install/include/duix_avatar.h && \
    install -m 0644 libduixavatar.a /fuzz/install/lib/libduixavatar.a && \
    rm -rf /work

WORKDIR /fuzz/src
