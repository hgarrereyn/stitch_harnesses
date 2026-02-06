#include <iostream>
#include <string>
#include <limits>
#include <double-conversion/double-conversion.h>

int main() {
    using namespace double_conversion;

    StringToDoubleConverter conv(StringToDoubleConverter::NO_FLAGS,
                                 0.0,
                                 std::numeric_limits<double>::quiet_NaN(),
                                 "infinity",
                                 "nan");
    const char* s = "12345.678";
    int processed = 0;
    double d = conv.StringToDouble(s, (int)std::char_traits<char>::length(s), &processed);

    char buffer[64];
    StringBuilder builder(buffer, sizeof(buffer));
    DoubleToStringConverter::EcmaScriptConverter().ToShortest(d, &builder);
    std::string out(builder.Finalize());

    std::cout << "Parsed: " << d << ", processed: " << processed << " -> back: " << out << "\n";
    return 0;
}
