#include <iostream>
#include <plugin_interface/SC_Constants.h>
#include <plugin_interface/SC_Rate.h>
#include <plugin_interface/SC_InterfaceTable.h>

int main() {
    int rates[4] = { calc_ScalarRate, calc_BufRate, calc_FullRate, calc_DemandRate };
    long sum = 0;
    for (int i = 0; i < 4; ++i) sum += rates[i];
    std::cout << "pi: " << pi << ", sc_api_version: " << sc_api_version << ", sum: " << sum << "\n";
    return 0;
}
