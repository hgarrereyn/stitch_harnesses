#include <yoga/Yoga.h>
#include <iostream>

int main() {
    // Create root and child nodes
    YGNodeRef root = YGNodeNew();
    YGNodeRef child = YGNodeNew();

    // Set some simple styles
    YGNodeStyleSetWidth(root, 100);
    YGNodeStyleSetHeight(root, 100);

    YGNodeStyleSetWidth(child, 50);
    YGNodeStyleSetHeight(child, 20);

    // Add child to root
    YGNodeInsertChild(root, child, 0);

    // Calculate layout with undefined available size (use YGUndefined)
    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    // Read and print layout results for sanity
    float rootW = YGNodeLayoutGetWidth(root);
    float rootH = YGNodeLayoutGetHeight(root);
    float childW = YGNodeLayoutGetWidth(child);
    float childH = YGNodeLayoutGetHeight(child);

    std::cout << "Root: " << rootW << "x" << rootH << "\n";
    std::cout << "Child: " << childW << "x" << childH << "\n";

    // Cleanup
    YGNodeFreeRecursive(root);
    return 0;
}
