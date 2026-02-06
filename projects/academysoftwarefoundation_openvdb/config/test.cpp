#include <openvdb/openvdb.h>
#include <iostream>

int main() {
    openvdb::initialize();

    // Create a FloatGrid with background value 0.0
    openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(/*background=*/0.0f);
    grid->setName("TestFloatGrid");

    // Set a single voxel to a non-background value
    openvdb::Coord ijk(1, 2, 3);
    grid->tree().setValue(ijk, 1.5f);

    // Access and print some simple info to ensure everything links
    std::cout << "Grid name: " << grid->getName() << "\n";
    std::cout << "Active voxel count: " << grid->activeVoxelCount() << "\n";

    // Fetch the value back and print
    float value = grid->tree().getValue(ijk);
    std::cout << "Value at (1,2,3): " << value << "\n";

    return 0;
}
