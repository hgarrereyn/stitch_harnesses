#include <iostream>
#include <vector>
#include <string>
#include <gflags/gflags.h>

DEFINE_bool(verbose, true, "Whether to print a greeting");
DEFINE_int32(times, 2, "How many times to print");

int main() {
    // Build a fake argv with program name only (no flags)
    const char* prog = "test_gflags";
    int argc = 1;
    char* argv_c[1];
    argv_c[0] = const_cast<char*>(prog);
    char** argv = argv_c;

    // Parse (will keep defaults)
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    int printed = 0;
    if (FLAGS_verbose) {
        for (int i = 0; i < FLAGS_times; ++i) {
            std::cout << "Hello from gflags!\n";
            ++printed;
        }
    }

    // Cleanup
    gflags::ShutDownCommandLineFlags();

    // Return number of lines printed to make use of flags
    return (printed == FLAGS_times) ? 0 : 1;
}
