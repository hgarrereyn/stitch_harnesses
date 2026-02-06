#include <iostream>
#include <FGFDMExec.h>
#include <FGJSBBase.h>

int main() {
    std::cout << "JSBSim version: " << JSBSim::FGJSBBase::GetVersion() << "\n";
    JSBSim::FGFDMExec exec;
    exec.Unbind();
    std::cout << "JSBSim FGFDMExec instantiated successfully" << std::endl;
    return 0;
}
