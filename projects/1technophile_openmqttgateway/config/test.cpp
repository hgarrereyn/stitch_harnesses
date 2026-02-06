#include <RFReceiver.h>
#include <iostream>

class DummyReceiver : public RFReceiver {
public:
    DummyReceiver() : enabled(false), id(42) {}
    void enable() override { enabled = true; }
    void disable() override { enabled = false; }
    int getReceiverID() const override { return id; }
    bool isEnabled() const { return enabled; }
private:
    bool enabled;
    int id;
};

int main() {
    DummyReceiver rx;
    rx.enable();
    std::cout << "Receiver ID: " << rx.getReceiverID() << ", enabled=" << (rx.isEnabled() ? "true" : "false") << std::endl;
    rx.disable();
    std::cout << "After disable, enabled=" << (rx.isEnabled() ? "true" : "false") << std::endl;
    return 0;
}
