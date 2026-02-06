ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 python3-pip python3-jinja2 pkg-config gperf \
    ninja-build \
    libcap-dev libmount-dev libselinux1-dev libseccomp-dev \
    liblz4-dev libzstd-dev libgcrypt20-dev liblzma-dev zlib1g-dev \
    libacl1-dev libapparmor-dev libkmod-dev libblkid-dev libcryptsetup-dev \
    && pip3 install --no-cache-dir 'meson>=1.2' \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

# Configure with many features disabled to minimize dependencies, while enabling static libs
RUN meson setup build \
    --prefix=/fuzz/install \
    -Dstatic-libsystemd=true \
    -Dstatic-libudev=true \
    -Dman=disabled -Dhtml=disabled \
    -Dresolve=false \
    -Dnss-myhostname=false -Dnss-mymachines=disabled -Dnss-resolve=disabled -Dnss-systemd=false \
    -Dsysvinit-path='' -Dsysvrcnd-path='' \
    -Dlogind=false -Dhostnamed=false -Dlocaled=false -Dmachined=false -Dportabled=false -Dsysext=false \
    -Dmountfsd=false -Duserdb=false -Dhomed=disabled -Dnetworkd=false -Dtimedated=false -Dtimesyncd=false \
    -Dremote=disabled -Dcreate-log-dirs=false -Dnsresourced=false -Dfirstboot=false -Drandomseed=false \
    -Dbacklight=false -Dvconsole=false -Doomd=false -Dcoredump=false -Dpstore=false -Drfkill=false \
    -Dstandalone-binaries=false \
    || (cat build/meson-logs/meson-log.txt; false)

RUN meson compile -C build -j"$(nproc)"
RUN meson install -C build
