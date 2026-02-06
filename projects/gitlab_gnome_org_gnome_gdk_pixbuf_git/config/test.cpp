#include <iostream>
#include <gdk-pixbuf/gdk-pixbuf.h>

int main() {
    GdkPixbuf *pb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, true, 8, 10, 10);
    if (!pb) {
        std::cout << "Failed to create GdkPixbuf" << std::endl;
        return 0;
    }
    gdk_pixbuf_fill(pb, 0xFF0000FF);
    int w = gdk_pixbuf_get_width(pb);
    int h = gdk_pixbuf_get_height(pb);
    int n = gdk_pixbuf_get_n_channels(pb);
    std::cout << "Created pixbuf: " << w << "x" << h << ", channels=" << n << std::endl;
    g_object_unref(pb);
    return 0;
}
