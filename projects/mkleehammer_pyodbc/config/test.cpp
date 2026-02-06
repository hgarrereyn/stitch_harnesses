#include <iostream>
#include <pyodbc.h>

int main() {
    const char* name = CTypeName(0);
    std::cout << "pyodbc CTypeName(0): " << (name ? name : "(null)") << std::endl;
    return 0;
}
