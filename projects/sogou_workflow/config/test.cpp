#include <iostream>
#include "workflow/WFFacilities.h"
#include "workflow/WFTaskFactory.h"

int main() {
    // Create a simple timer task that fires immediately and finishes.
    WFFacilities::WaitGroup wg(1);
    auto task = WFTaskFactory::create_timer_task(1, [&wg](WFTimerTask *) {
        std::cout << "Timer task executed" << std::endl;
        wg.done();
    });
    task->start();
    wg.wait();
    return 0;
}
