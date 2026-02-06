#include <vsg/all.h>
#include <iostream>

int main() {
    auto group = vsg::Group::create();
    auto child = vsg::Node::create();
    group->addChild(child);

    vsg::vec3 a(1.0f, 2.0f, 3.0f);
    vsg::vec3 b(4.0f, 5.0f, 6.0f);
    vsg::vec3 c = a + b;

    std::cout << "VSG test OK. Children: " << group->children.size() << ", vec3 sum: ("
              << c.x << ", " << c.y << ", " << c.z << ")\n";
    return 0;
}
