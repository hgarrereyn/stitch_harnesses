ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Install the module's public API header
RUN cp /fuzz/src/src/api/ngx_http_lua_api.h ${PREFIX}/include/

# Provide minimal stub nginx headers required by ngx_http_lua_api.h
RUN bash -lc 'printf "#ifndef NGINX_H\n#define NGINX_H\n#define nginx_version 1024000\n#define NGINX_VERSION \"1.24.0\"\n#endif\n" > ${PREFIX}/include/nginx.h'
RUN bash -lc 'printf "#ifndef NGX_CORE_H\n#define NGX_CORE_H\n#include <stdint.h>\n#include <stddef.h>\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\ntypedef unsigned char u_char;\n\ntypedef intptr_t ngx_int_t;\ntypedef uintptr_t ngx_uint_t;\ntypedef ptrdiff_t ngx_flag_t;\n\ntypedef struct { size_t len; unsigned char *data; } ngx_str_t;\n\ntypedef struct ngx_pool_s ngx_pool_t;\ntypedef struct ngx_log_s ngx_log_t;\n\ntypedef struct { ngx_pool_t *pool; ngx_log_t *log; } ngx_cycle_t;\n\ntypedef struct { void *dummy; } ngx_conf_t;\n\ntypedef struct ngx_shm_zone_s ngx_shm_zone_t;\n\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${PREFIX}/include/ngx_core.h'
RUN bash -lc 'printf "#ifndef NGX_HTTP_H\n#define NGX_HTTP_H\n#include \"ngx_core.h\"\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\ntypedef struct ngx_http_request_s ngx_http_request_t;\ntypedef void (*ngx_http_cleanup_pt)(void *data);\n\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${PREFIX}/include/ngx_http.h'

# Provide minimal stub Lua header required by ngx_http_lua_api.h
RUN bash -lc 'printf "#ifndef LUA_H\n#define LUA_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\ntypedef struct lua_State lua_State;\ntypedef double lua_Number;\ntypedef int (*lua_CFunction)(lua_State *L);\n\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ${PREFIX}/include/lua.h'

# Create a tiny dummy static library
RUN bash -lc "printf '' | ar rcs ${PREFIX}/lib/libngx_http_lua_stub.a"

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
