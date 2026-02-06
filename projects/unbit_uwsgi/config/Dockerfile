ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends python3 ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    UWSGI_PROFILE_OVERRIDE="as_shared_library=static;bin_name=/fuzz/install/lib/libuwsgi.a;embedded_plugins=None;json=false;xml=false;ssl=false;pcre=false;routing=false" \
    python3 uwsgiconfig.py --build && \
    cp uwsgi.h /fuzz/install/include/
