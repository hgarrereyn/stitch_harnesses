ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install Dear ImGui as a static library
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p /fuzz/build "$PREFIX/include" "$PREFIX/lib"; \
    cd /fuzz/src; \
    # Compile core Dear ImGui sources (no backends, no demo)
    $CXX -I/fuzz/src -fPIC -c imgui.cpp -o /fuzz/build/imgui.o; \
    $CXX -I/fuzz/src -fPIC -c imgui_draw.cpp -o /fuzz/build/imgui_draw.o; \
    $CXX -I/fuzz/src -fPIC -c imgui_tables.cpp -o /fuzz/build/imgui_tables.o; \
    $CXX -I/fuzz/src -fPIC -c imgui_widgets.cpp -o /fuzz/build/imgui_widgets.o; \
    ar rcs "$PREFIX/lib/libimgui.a" /fuzz/build/imgui.o /fuzz/build/imgui_draw.o /fuzz/build/imgui_tables.o /fuzz/build/imgui_widgets.o; \
    # Install headers
    cp -v imgui.h imconfig.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h "$PREFIX/include/"; \
    # Optionally install internal header for completeness (not part of public API)
    cp -v imgui_internal.h "$PREFIX/include/" || true
