#include <cstdio>
extern "C" {
#include <fiobj/fiobj_str.h>
#include <fiobj/fiobj_numbers.h>
#include <fiobj/fiobject.h>
}

int main() {
    // Create and manipulate a facil.io FIOBJ string
    FIOBJ s = fiobj_str_new("hello", 5);
    if (!s) return 1;
    fiobj_str_write(s, ", world", 7);
    fiobj_str_write_i(s, 123);

    // Convert to C string info and print length
    fio_str_info_s info = fiobj_obj2cstr(s);
    if (info.data && info.len > 0) {
        // Print a short confirmation message
        std::printf("facil.io fiobj string length: %zu\n", (size_t)info.len);
    }

    // Clean up
    fiobj_free(s);
    return 0;
}
