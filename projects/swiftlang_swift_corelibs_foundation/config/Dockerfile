ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/Sources/CoreFoundation/include /fuzz/install/include/CoreFoundation && \
    cp -r /fuzz/src/Sources/_CFXMLInterface/include /fuzz/install/include/_CFXMLInterface

# Build a minimal static library that provides one CFXMLInterface symbol for linking tests
RUN mkdir -p /fuzz/install/lib && \
    cat > /tmp/cfxml_stub.c <<'EOF'
    typedef struct _xmlParserCtxt *_CFXMLInterfaceParserContext;
    int _CFXMLInterfaceSAX2GetLineNumber(_CFXMLInterfaceParserContext ctx) { (void)ctx; return 0; }
EOF
RUN stitch_libafl_cc -c -O2 -fPIC -o /tmp/cfxml_stub.o /tmp/cfxml_stub.c && \
    ar rcs /fuzz/install/lib/libcfxmlstub.a /tmp/cfxml_stub.o && \
    ranlib /fuzz/install/lib/libcfxmlstub.a

ENV CPATH=/fuzz/install/include:/fuzz/install/include/CoreFoundation:/fuzz/install/include/_CFXMLInterface
ENV LIBRARY_PATH=/fuzz/install/lib
