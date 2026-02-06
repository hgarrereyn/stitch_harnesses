#include <iostream>
#include <nav2_voxel_grid/voxel_grid.hpp>

int main(){
  nav2_voxel_grid::VoxelGrid grid(10, 10, 4);
  grid.markVoxel(2, 3, 1);
  auto s = grid.getVoxel(2,3,1);
  std::cout << "Voxel(2,3,1) status: " << (int)s << "\n";
  grid.markVoxelLine(0,0,0, 9,9,0, 100);
  grid.printColumnGrid();
  return 0;
}
