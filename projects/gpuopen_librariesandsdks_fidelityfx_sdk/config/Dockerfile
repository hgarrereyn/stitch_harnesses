ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /fuzz/install/include; \
    cp -R /fuzz/src/Kits/FidelityFX/api/include/ffx_api.h /fuzz/install/include/; \
    cp -R /fuzz/src/Kits/FidelityFX/api/include/ffx_api.hpp /fuzz/install/include/; \
    cp -R /fuzz/src/Kits/FidelityFX/api/include/ffx_api_types.h /fuzz/install/include/
