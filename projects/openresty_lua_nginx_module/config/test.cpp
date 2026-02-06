#include <stdio.h>
#include <stdint.h>
#include <ngx_http_lua_api.h>

int main() {
    printf("ngx_http_lua_version=%d\n", ngx_http_lua_version);

    ngx_http_lua_value_t v;
    v.type = 0;
    v.value.b = 1;

    ngx_http_lua_ffi_str_t s;
    s.len = 3;
    s.data = (unsigned char*)"abc";

    printf("len=%d first=%c\n", s.len, s.data[0]);
    return 0;
}
