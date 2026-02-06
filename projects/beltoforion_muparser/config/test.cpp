#include <iostream>
#include <muParser.h>

int main() {
    try {
        mu::Parser p;
        p.SetExpr("2 + 3*sin(1.57079632679)");
        double val = p.Eval();
        std::cout << "Result: " << val << std::endl;
    } catch (const mu::Parser::exception_type &e) {
        std::cerr << "muparser error: " << e.GetMsg() << std::endl;
        return 1;
    }
    return 0;
}
