#include <gtk/gtkversion.h>
#include <stdio.h>

int main() {
    unsigned major = gtk_get_major_version();
    unsigned minor = gtk_get_minor_version();
    unsigned micro = gtk_get_micro_version();
    const char* vercheck = gtk_check_version(major, minor, micro);
    printf("GTK version runtime: %u.%u.%u (check=%s)\n", major, minor, micro, vercheck ? vercheck : "OK");
    return 0;
}
