#include <iostream>
#include <stdint.h>
#include "binary.h"
#include "pgmspace.h"
#include "Printable.h"

extern "C" int arduino_esp32_subset_placeholder();

// Simple class to satisfy Printable without needing Arduino Print implementation
class DummyPrint;

class DummyPrintable : public Printable {
public:
    size_t printTo(::Print &p) const override { (void)p; return 0; }
};

int main() {
    int v1 = B1010;      // 10
    int v2 = B11001100;  // 204

    const char *p = PSTR("hello");
    volatile unsigned char b = pgm_read_byte(p);

    std::cout << "v1=" << v1 << ", v2=" << v2 << ", b0='" << (char)b << "'" << std::endl;

    return arduino_esp32_subset_placeholder() == 42 ? 0 : 1;
}
