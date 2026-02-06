#include <stdio.h>

extern "C" {
#include <ngx_core.h>
#include <ngx_http.h>
#include <nginx.h>
#include "ngx_http_headers_more_filter_module.h"
}

int main() {
    ngx_http_headers_more_main_conf_t mcf;
    mcf.postponed_to_phase_end = 0;
    mcf.requires_filter = 0;
    mcf.requires_handler = 0;
    printf("headers-more main conf initialized: %d %d %d\n", (int)mcf.postponed_to_phase_end, (int)mcf.requires_filter, (int)mcf.requires_handler);
    return 0;
}
