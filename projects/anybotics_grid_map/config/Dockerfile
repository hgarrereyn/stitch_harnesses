ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: Eigen and basic build tools for ar/ranlib
RUN apt-get update && apt-get install -y --no-install-recommends \
    libeigen3-dev \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build a static libgrid_map_core.a manually (avoid ROS/catkin dependency)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz

RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib && \
    cd /fuzz/build && \
    INCLUDES="-I/fuzz/src/grid_map_core/include -I/usr/include/eigen3" && \
    DEFINES="-DEIGEN_FUNCTORS_PLUGIN=<grid_map_core/eigen_plugins/FunctorsPlugin.hpp> -DEIGEN_DENSEBASE_PLUGIN=<grid_map_core/eigen_plugins/DenseBasePlugin.hpp>" && \
    SRCS="/fuzz/src/grid_map_core/src/GridMap.cpp \
          /fuzz/src/grid_map_core/src/GridMapMath.cpp \
          /fuzz/src/grid_map_core/src/SubmapGeometry.cpp \
          /fuzz/src/grid_map_core/src/BufferRegion.cpp \
          /fuzz/src/grid_map_core/src/Polygon.cpp \
          /fuzz/src/grid_map_core/src/CubicInterpolation.cpp \
          /fuzz/src/grid_map_core/src/iterators/GridMapIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/SubmapIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/CircleIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/EllipseIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/SpiralIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/PolygonIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/LineIterator.cpp \
          /fuzz/src/grid_map_core/src/iterators/SlidingWindowIterator.cpp" && \
    for f in $SRCS; do \
      echo "Compiling $f"; \
      ${CXX} -O2 -fPIC $INCLUDES $DEFINES -c $f -o $(basename $f).o; \
    done && \
    ar rcs libgrid_map_core.a *.o && \
    install -Dm644 libgrid_map_core.a /fuzz/install/lib/libgrid_map_core.a && \
    # Install public headers
    mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/grid_map_core/include/grid_map_core /fuzz/install/include/
