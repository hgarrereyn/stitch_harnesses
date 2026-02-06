ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git \
    python3-dev \
    build-essential \
    cmake \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/C++

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN bash -lc "./install.sh"

RUN mkdir -p /fuzz/build/mpcc && \
    INCS="-I. -IExternal/Eigen -IExternal/Json/include -IExternal/matplotlib -IExternal/hpipm/lib/include -IExternal/blasfeo/lib/include" && \
    CXXFLAGS="-O2 -fPIC -ffunction-sections -fdata-sections" && \
    SRCs="types.cpp \
          Params/params.cpp Params/track.cpp \
          Spline/cubic_spline.cpp Spline/arc_length_spline.cpp \
          Constraints/constraints.cpp Constraints/bounds.cpp \
          Cost/cost.cpp \
          Model/model.cpp Model/integrator.cpp \
          Interfaces/solver_interface.cpp \
          MPC/mpc.cpp" && \
    for f in $SRCs; do \
      echo Compiling $f; \
      stitch_libafl_cxx $CXXFLAGS $INCS -c $f -o /fuzz/build/mpcc/$(basename $f).o; \
    done && \
    echo '#include "MPC/mpc.h"\n#include "Interfaces/hpipm_interface.h"\n#include <array>\nnamespace mpcc {\nstd::array<OptVariables,N+1> HpipmInterface::solveMPC(std::array<Stage,N+1>&, const State&, int *status) { if(status) *status = -1; return std::array<OptVariables,N+1>(); }\n}' > /fuzz/build/mpcc/hpipm_interface_stub.cpp && \
    stitch_libafl_cxx $CXXFLAGS $INCS -c /fuzz/build/mpcc/hpipm_interface_stub.cpp -o /fuzz/build/mpcc/hpipm_interface_stub.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/mpcc && \
    ar rcs /fuzz/install/lib/libmpcc.a /fuzz/build/mpcc/*.o && \
    cp -r MPC Model Cost Constraints Params Spline Plotting Interfaces config.h types.h /fuzz/install/include/mpcc/ && \
    sed -i '/Interfaces\/hpipm_interface.h/d' /fuzz/install/include/mpcc/MPC/mpc.h
