ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    pkg-config \
    libopencv-dev \
    libtesseract-dev \
    libleptonica-dev \
 && rm -rf /var/lib/apt/lists/*

# Patch sources for C++17 compatibility
RUN sed -i 's/transform\.starts_with(\"whitepaper\")/transform.rfind(\"whitepaper\", 0) == 0/' /fuzz/src/cpp/src/DocumentDetector.cpp && \
    sed -i 's/transform\.starts_with(\"enhance\")/transform.rfind(\"enhance\", 0) == 0/' /fuzz/src/cpp/src/DocumentDetector.cpp && \
    sed -i 's/transform\.starts_with(\"color\")/transform.rfind(\"color\", 0) == 0/' /fuzz/src/cpp/src/DocumentDetector.cpp

# Build static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include

# Compile source files (excluding QRCode.cpp and DocumentOCR.cpp for minimal deps)
RUN set -eux; \
    INC="-I/fuzz/src/cpp/src/include"; \
    CXXFLAGS="-O2 -fPIC $INC $(pkg-config --cflags opencv4)"; \
    gf_libafl_cxx -c /fuzz/src/cpp/src/Utils.cpp $CXXFLAGS -o /fuzz/build/Utils.o; \
    gf_libafl_cxx -c /fuzz/src/cpp/src/ColorSimplificationTransform.cpp $CXXFLAGS -o /fuzz/build/ColorSimplificationTransform.o; \
    gf_libafl_cxx -c /fuzz/src/cpp/src/WhitePaperTransform.cpp $CXXFLAGS -o /fuzz/build/WhitePaperTransform.o; \
    gf_libafl_cxx -c /fuzz/src/cpp/src/DocumentDetector.cpp $CXXFLAGS -o /fuzz/build/DocumentDetector.o; \
    ar rcs /fuzz/install/lib/libdocumentscanner.a /fuzz/build/*.o

# Install headers (including bundled jsoncons)
RUN cp -v /fuzz/src/cpp/src/include/*.h /fuzz/install/include/ && \
    cp -rv /fuzz/src/cpp/src/include/jsoncons /fuzz/install/include/
