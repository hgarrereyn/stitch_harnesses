ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies required for installing public headers used for testing
RUN mkdir -p /fuzz/install/include/app \
 && cp /fuzz/src/src/app/sprite_sheet_type.h /fuzz/install/include/app/
