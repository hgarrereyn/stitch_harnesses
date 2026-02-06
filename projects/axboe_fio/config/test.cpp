#include <cstdio>
extern "C" {
    const char* runstate_to_name(int);
    const char* fio_get_os_string(int);
    int yywrap(void) { return 1; }
}
int main() {
    const char* name0 = runstate_to_name(0);
    const char* os1 = fio_get_os_string(1);
    std::printf("runstate=%s os=%s\n", name0 ? name0 : "null", os1 ? os1 : "null");
    return 0;
}
