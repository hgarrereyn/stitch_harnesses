ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends git ca-certificates ninja-build cmake && rm -rf /var/lib/apt/lists/*

# Fetch Dear ImGui (headers + sources for core library)
RUN git clone --depth 1 https://github.com/ocornut/imgui.git /tmp/imgui

# Prepare CMake project for building static libs
RUN mkdir -p /tmp/build && cd /tmp/build && cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.16)
project(implot_fuzz_build LANGUAGES C CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# imgui static lib
add_library(imgui STATIC
    /tmp/imgui/imgui.cpp
    /tmp/imgui/imgui_draw.cpp
    /tmp/imgui/imgui_tables.cpp
    /tmp/imgui/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC /tmp/imgui)

# implot static lib
add_library(implot STATIC
    /fuzz/src/implot.cpp
    /fuzz/src/implot_items.cpp
)
target_include_directories(implot PUBLIC /fuzz/src /tmp/imgui)
target_link_libraries(implot PUBLIC imgui)

install(TARGETS imgui implot ARCHIVE DESTINATION lib)
install(FILES 
    /fuzz/src/implot.h 
    /fuzz/src/implot_internal.h
    DESTINATION include)
install(FILES 
    /tmp/imgui/imconfig.h 
    /tmp/imgui/imgui.h 
    /tmp/imgui/imgui_internal.h 
    /tmp/imgui/imstb_rectpack.h 
    /tmp/imgui/imstb_textedit.h 
    /tmp/imgui/imstb_truetype.h 
    DESTINATION include)
EOF

# Configure, build, install
RUN cmake -S /tmp/build -B /tmp/build/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install && \
    cmake --build /tmp/build/build -j && \
    cmake --install /tmp/build/build && \
    rm -rf /tmp/build

