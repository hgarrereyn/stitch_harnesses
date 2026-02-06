ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Tools needed to build a static library manually
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build ReShadeFX static library manually (excluding DXBC and SPIR-V backends that require external SDKs)
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include \
 && cd /fuzz/build \
 && SRC=/fuzz/src/source \
 && CXXFLAGS="-O2 -fPIC -D_UNICODE -I$SRC" \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_codegen_glsl.cpp -o effect_codegen_glsl.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_codegen_hlsl.cpp -o effect_codegen_hlsl.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_expression.cpp -o effect_expression.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_lexer.cpp -o effect_lexer.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_parser_exp.cpp -o effect_parser_exp.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_parser_stmt.cpp -o effect_parser_stmt.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_preprocessor.cpp -o effect_preprocessor.o \
 && gf_libafl_cxx $CXXFLAGS -c $SRC/effect_symbol_table.cpp -o effect_symbol_table.o \
 && ar rcs libReShadeFX.a *.o \
 && cp libReShadeFX.a /fuzz/install/lib/

# Install public headers
RUN cp /fuzz/src/source/effect_codegen.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_expression.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_lexer.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_module.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_parser.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_preprocessor.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_symbol_table.hpp /fuzz/install/include/ \
 && cp /fuzz/src/source/effect_token.hpp /fuzz/install/include/
