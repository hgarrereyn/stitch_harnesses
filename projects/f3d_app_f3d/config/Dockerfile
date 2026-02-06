ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install tree with public headers only (no heavy deps required)
WORKDIR /fuzz
RUN mkdir -p /fuzz/install/include/f3d && \
    cp -v /fuzz/src/library/public/exception.h /fuzz/install/include/f3d/ && \
    cp -v /fuzz/src/library/public/types.h /fuzz/install/include/f3d/ && \
    cp -v /fuzz/src/library/public/utils.h /fuzz/install/include/f3d/ && \
    cp -v /fuzz/src/library/public/log.h /fuzz/install/include/f3d/ && \
    printf '%s\n' '#ifndef F3D_EXPORT_H' '#define F3D_EXPORT_H' '#define F3D_EXPORT' '#define F3D_NO_EXPORT' '#define F3D_DEPRECATED' '#endif' > /fuzz/install/include/f3d/export.h
