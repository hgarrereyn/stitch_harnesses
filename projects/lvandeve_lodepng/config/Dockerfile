ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install lodepng as a static library
RUN set -eux; \
    apt-get update; \
    apt-get install -y --no-install-recommends ca-certificates make bash file; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src; \
    \
    # Compile lodepng.cpp into an object file using the required compilers
    stitch_libafl_cxx -c lodepng.cpp -O2 -fno-exceptions -fno-rtti -Wall -Wextra -o /fuzz/build/lodepng.o; \
    \
    # Create a static library
    ar rcs /fuzz/build/liblodepng.a /fuzz/build/lodepng.o; \
    \
    # Install the library and header
    install -m 0644 lodepng.h /fuzz/install/include/lodepng.h; \
    install -m 0644 /fuzz/build/liblodepng.a /fuzz/install/lib/liblodepng.a; \
    echo 'Installed lodepng to /fuzz/install'
