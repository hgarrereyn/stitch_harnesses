#include <cstdio>
#include <cstdint>
#include "scintilla/Sci_Position.h"
#include "scintilla/ScintillaTypes.h"

int main() {
    // Use an inline function from the library (header-only)
    int a = 5;
    int b = 10;
    int c = 20;
    int clamped = sci::clamp(c, a, b); // should clamp 20 to 10

    // Also exercise a couple of enums/typedefs from ScintillaTypes
    Scintilla::EndOfLine eol = Scintilla::EndOfLine::Lf;
    Sci_Position pos = 123;

    std::printf("clamped=%d, eol=%d, pos=%td\n", clamped, static_cast<int>(eol), pos);
    return 0;
}
