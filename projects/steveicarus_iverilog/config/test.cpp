#include <iostream>
#include <stdint.h>

extern "C" {
#include <iverilog/vpi_user.h>
#include <iverilog/_pli_types.h>
#include <iverilog/acc_user.h>
#include <iverilog/veriuser.h>
#include <iverilog/sv_vpi_user.h>
}

// Include the target API header as C++
#include <iverilog/ivl_target.h>

int main() {
    vpiHandle h = 0; (void)h;
    s_vpi_time tm; tm.type = vpiSimTime; tm.high = 0; tm.low = 0;
    const bool support_bool = true;
    std::cout << "Headers OK. vpiSimTime=" << vpiSimTime
              << ", bool=" << (support_bool ? "true" : "false") << "\n";
    return 0;
}
