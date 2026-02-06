#include <iostream>
extern "C" {
#include <char_lib.h>
}

int main() {
    char buf1[] = "HelloFuzzingWorld"; // has some lowercase letters
    int lower = count_lowercase_letters(buf1);
    std::cout << "Lowercase count: " << lower << std::endl;

    char fmt1[] = "Fuzz example input that is definitely longer than forty characters XXXXX";
    int r1 = parse_complex_format(fmt1);
    int r2 = parse_complex_format_second(fmt1);
    std::cout << "parse1: " << r1 << ", parse2: " << r2 << std::endl;
    return 0;
}
