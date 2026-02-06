#include <cstdio>
#include <tbox/tbox.h>

int main() {
    if (!tb_init(tb_null, tb_null)) {
        std::printf("tb_init failed\n");
        return 0;
    }

    tb_vector_ref_t vec = tb_vector_init(0, tb_element_str(tb_true));
    if (vec) {
        tb_vector_insert_tail(vec, (tb_cpointer_t)"hello");
        tb_vector_insert_tail(vec, (tb_cpointer_t)"tbox");
        tb_for_all (tb_char_t const*, cstr, vec) {
            if (cstr) std::printf("%s\n", cstr);
        }
        tb_vector_exit(vec);
    }

    tb_exit();
    return 0;
}
