#include <common/showmsg.hpp>
#include <cstdio>

int main() {
    ShowInfo("rAthena common library test: %d + %d = %d\n", 2, 3, 5);
    ShowStatus("Status message example.\n");
    ShowWarning("Warning example.\n");
    return 0;
}
