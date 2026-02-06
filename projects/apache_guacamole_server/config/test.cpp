extern "C" {
#include <guacamole/hash.h>
}
#include <stdio.h>
#include <cairo/cairo.h>

int main() {
    int width = 16, height = 16;
    cairo_surface_t* a = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_surface_t* b = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    cairo_t* cr = cairo_create(a);
    cairo_set_source_rgb(cr, 0.2, 0.4, 0.6);
    cairo_paint(cr);
    cairo_destroy(cr);

    cr = cairo_create(b);
    cairo_set_source_rgb(cr, 0.2, 0.4, 0.6);
    cairo_paint(cr);
    cairo_destroy(cr);

    unsigned int hash_a = guac_hash_surface(a);
    unsigned int hash_b = guac_hash_surface(b);
    int cmp = guac_surface_cmp(a, b);

    printf("hash_a=%u hash_b=%u cmp=%d\n", hash_a, hash_b, cmp);

    cairo_surface_destroy(a);
    cairo_surface_destroy(b);

    return 0;
}
