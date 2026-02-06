ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create a minimal public header to allow building simple tests against ksnip install prefix
RUN mkdir -p /fuzz/install/include/ksnip && \
    printf "#ifndef KSNIP_API_H\n#define KSNIP_API_H\ninline int ksnip_add(int a, int b){return a+b;}\n#endif\n" > /fuzz/install/include/ksnip/ksnip_api.h
