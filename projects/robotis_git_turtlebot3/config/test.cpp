#include <iostream>
#include "turtlebot3_node/control_table.hpp"

int main() {
    robotis::turtlebot3::ControlTable table;
    std::cout << "Model number addr: " << table.model_number.addr << " length: " << table.model_number.length << "\n";
    return 0;
}
