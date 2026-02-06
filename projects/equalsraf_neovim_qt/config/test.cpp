#include <iostream>
#include "neovimconnector.h"

int main(){
    using namespace NeovimQt;
    NeovimConnector::NeovimError e = NeovimConnector::NoError;
    std::cout << "Neovim-Qt enum value: " << static_cast<int>(e) << std::endl;
    return 0;
}
