ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed by CGAL headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libboost-dev \
    libgmp-dev \
    libmpfr-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Install CGAL headers into /fuzz/install/include by copying from source tree (header-only library)
RUN mkdir -p /fuzz/install/include/CGAL \
 && cp -r /fuzz/src/Installation/include/CGAL/* /fuzz/install/include/CGAL/ \
 && for d in /fuzz/src/*/include/CGAL; do \
      if [ -d "$d" ]; then \
        cp -r "$d"/* /fuzz/install/include/CGAL/; \
      fi; \
    done
