#include <cassert>
#include <iostream>
#include <vector>
#include "MouseTrajectories.hpp"

int main() {
    // Generate a simple human-like mouse trajectory
    HumanizeMouseTrajectory traj({0.0, 0.0}, {100.0, 50.0});
    std::vector<int> pts = traj.getPoints();
    // Should be pairs of x,y
    assert(pts.size() % 2 == 0);
    std::cout << "Generated points: " << pts.size()/2 << "\n";
    if (!pts.empty()) {
        std::cout << "First point: (" << pts[0] << ", " << pts[1] << ")\n";
    }
    return 0;
}
