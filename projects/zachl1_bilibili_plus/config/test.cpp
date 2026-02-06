#include <iostream>
#include <houjie/complex.h>
#include <houjie/string.h>

int main() {
    complex a(1.0, 2.0), b(3.0, -4.0);
    complex c = a + b;
    complex d = a * b;
    std::cout << "c.real=" << c.real() << ", c.imag=" << c.imag() << "\n";
    std::cout << "d.real=" << d.real() << ", d.imag=" << d.imag() << "\n";

    String s1("Hello"), s2(" World");
    String s3 = s1; // copy
    s3 = s2;        // assign
    std::cout << "s1=" << s1 << ", s2=" << s2 << ", s3=" << s3 << "\n";
    return 0;
}
