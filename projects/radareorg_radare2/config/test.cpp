#include <iostream>
extern "C" {
#include <r_util.h>
}
int main() {
    const unsigned char data[] = {0xde, 0xad, 0xbe, 0xef};
    char out[64] = {0};
    int n = r_hex_bin2str(data, 4, out);
    std::cout << "hex=" << out << ", n=" << n << "\n";
    // A couple of utility calls
    const char *s = "radare2";
    size_t len = r_str_len_utf8(s);
    std::cout << "len=" << len << "\n";
    return 0;
}
