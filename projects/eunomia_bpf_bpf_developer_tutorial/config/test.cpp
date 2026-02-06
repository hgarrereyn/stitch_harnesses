#include <iostream>
#include <cstring>
#include <string>
// The header is C-friendly; in C++ bool is built-in
#include <bootstrap.h>

int main() {
    event ev{}; // zero-initialize
    ev.pid = 123;
    ev.ppid = 1;
    ev.exit_code = 0u;
    ev.duration_ns = 42ull;
    std::strncpy(ev.comm, "demo", sizeof(ev.comm)-1);
    std::strncpy(ev.filename, "/bin/demo", sizeof(ev.filename)-1);
    ev.exit_event = false;

    std::cout << "pid=" << ev.pid
              << ", ppid=" << ev.ppid
              << ", duration_ns=" << ev.duration_ns
              << ", comm=" << ev.comm
              << ", filename=" << ev.filename
              << "\n";
    return 0;
}
