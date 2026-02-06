#include <vtkReservedRemoteObjectIds.h>
#include <iostream>

int main() {
    int maxId = vtkReservedRemoteObjectIds::ReservedGlobalIds::RESERVED_MAX_IDS;
    std::cout << "Max reserved ID: " << maxId << "\n";
    return 0;
}
