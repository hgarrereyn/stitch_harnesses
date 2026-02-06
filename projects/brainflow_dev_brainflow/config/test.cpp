#include <iostream>
#include "data_filter.h"
#include "board_shim.h"

int main() {
    int val = 15;
    int p2 = DataFilter::get_nearest_power_of_two(val);
    std::cout << "Nearest power of two to " << val << " is " << p2 << "\n";

    int synthetic_board_id = (int)BoardIds::SYNTHETIC_BOARD;
    int sr = BoardShim::get_sampling_rate(synthetic_board_id);
    std::cout << "Synthetic board sampling rate: " << sr << "\n";
    return 0;
}
