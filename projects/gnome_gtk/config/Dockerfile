ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal toolchain and headers needed
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
    libglib2.0-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Install minimal headers and build a minimal static lib exposing version symbols
RUN mkdir -p /fuzz/install/include/gtk-4.0/gtk && \
    mkdir -p /fuzz/install/lib && \
    printf "#ifndef __GTK_VERSION_H__\n#define __GTK_VERSION_H__\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n#define GTK_MAJOR_VERSION 4\n#define GTK_MINOR_VERSION 21\n#define GTK_MICRO_VERSION 5\n#define GTK_BINARY_AGE 2105\n#define GTK_INTERFACE_AGE 0\nunsigned gtk_get_major_version(void);\nunsigned gtk_get_minor_version(void);\nunsigned gtk_get_micro_version(void);\nunsigned gtk_get_binary_age(void);\nunsigned gtk_get_interface_age(void);\nconst char * gtk_check_version (unsigned required_major, unsigned required_minor, unsigned required_micro);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/gtk-4.0/gtk/gtkversion.h && \
    printf "" > /tmp/config.h && \
    "$CC" -O2 -fPIC -Dguint=unsigned -include stddef.h \
      -I/fuzz/install/include/gtk-4.0 -I/fuzz/install/include/gtk-4.0/gtk -I/tmp \
      -c gtk/gtkversion.c -o /tmp/gtkversion.o && \
    ar rcs /fuzz/install/lib/libgtk-4.a /tmp/gtkversion.o && \
    rm -f /tmp/gtkversion.o
