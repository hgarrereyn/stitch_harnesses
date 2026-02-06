#include <glib.h>
#include <stdio.h>
extern "C" {
#include <irssi/src/lib-config/iconfig.h>
}

int main() {
    CONFIG_REC *rec = config_open(NULL, -1);
    if (!rec) {
        printf("failed to open config\n");
        return 0;
    }
    const char *data = "a = { x = 42; y = ( 1, 2, 3 ); };";
    if (config_parse_data(rec, data, "memory") != 0) {
        printf("parse error: %s\n", config_last_error(rec));
        config_close(rec);
        return 0;
    }
    int x = config_get_int(rec, "a", "x", -1);
    printf("x=%d\n", x);
    CONFIG_NODE *a = config_node_traverse(rec, "a", 0);
    if (a) {
        CONFIG_NODE *yn = config_node_find(a, "y");
        if (yn) {
            char **lst = config_node_get_list(yn);
            if (lst) {
                for (int i = 0; lst[i]; i++) {
                    printf("y[%d]=%s\n", i, lst[i]);
                }
                g_strfreev(lst);
            }
        }
    }
    config_close(rec);
    return 0;
}
