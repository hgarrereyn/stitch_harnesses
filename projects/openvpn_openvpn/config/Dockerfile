ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies to use public headers (mbedTLS for plugin header)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libmbedtls-dev \
      ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Install public API headers into /fuzz/install/include
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include

# Generate configured openvpn-plugin.h from template using version.m4
RUN MAJOR=$(awk '/define\(\[PRODUCT_VERSION_MAJOR\]/{print $3}' version.m4 | sed 's/[),]//g') \
 && MINOR=$(awk '/define\(\[PRODUCT_VERSION_MINOR\]/{print $3}' version.m4 | sed 's/[),]//g') \
 && PATCH=$(awk '/define\(\[PRODUCT_VERSION_PATCH\]/{print $3}' version.m4 | sed 's/[),]//g') \
 && sed -e "s/@OPENVPN_VERSION_MAJOR@/${MAJOR}/g" \
        -e "s/@OPENVPN_VERSION_MINOR@/${MINOR}/g" \
        -e "s/@OPENVPN_VERSION_PATCH@/${PATCH}/g" \
        include/openvpn-plugin.h.in > /fuzz/install/include/openvpn-plugin.h

