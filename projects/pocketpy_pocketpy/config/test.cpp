#include <iostream>
extern "C" {
#include "pocketpy.h"
}

int main(){
    py_initialize();
    bool ok = py_exec("x = 1 + 2\nprint('pkpy sum:', x)", "<string>", EXEC_MODE, NULL);
    if(!ok){
        py_printexc();
        py_finalize();
        return 1;
    }
    py_finalize();
    std::cout << "pocketpy basic run ok" << std::endl;
    return 0;
}
