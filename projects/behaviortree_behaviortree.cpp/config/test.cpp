#include <behaviortree_cpp/bt_factory.h>
#include <iostream>

int main() {
    using namespace BT;
    BehaviorTreeFactory factory;

    factory.registerSimpleAction("Hello", [](TreeNode& self) {
        (void)self;
        std::cout << "Hello from BehaviorTree.CPP!" << std::endl;
        return NodeStatus::SUCCESS;
    });

    static const char* xml_text = R"(
    <root BTCPP_format="4">
      <BehaviorTree ID="MainTree">
        <Sequence name="root">
          <Hello/>
        </Sequence>
      </BehaviorTree>
    </root>
    )";

    auto tree = factory.createTreeFromText(xml_text);
    // Tick until the root completes
    NodeStatus status = NodeStatus::RUNNING;
    int iters = 0;
    while(status == NodeStatus::RUNNING && iters++ < 10){
        status = tree.tickOnce();
    }
    std::cout << "Tree finished with status: " << toStr(status) << std::endl;
    return 0;
}
