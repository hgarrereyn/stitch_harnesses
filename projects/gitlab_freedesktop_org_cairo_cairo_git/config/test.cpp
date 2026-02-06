#include <cairo/cairo.h>
#include <stdio.h>

int main() {
    int width = 64, height = 64;
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    // Fill background white
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    // Draw a simple diagonal line
    cairo_set_source_rgb(cr, 0.2, 0.4, 0.8);
    cairo_set_line_width(cr, 4.0);
    cairo_move_to(cr, 8, 8);
    cairo_line_to(cr, width - 8, height - 8);
    cairo_stroke(cr);

    // Clean up
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    // Print something so the test runner sees output
    printf("cairo basic draw OK\n");
    return 0;
}
