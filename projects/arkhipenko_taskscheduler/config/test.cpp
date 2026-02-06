#include <iostream>
#include <thread>
#include <chrono>

// Use the library
#include <TaskScheduler.h>

// Simple global state for demonstration
static int g_count = 0;

void tick() {
    ++g_count;
}

int main() {
    // Create scheduler and a task that runs 5 times every 10ms
    Scheduler runner;
    Task t1(10 /*ms*/, 5, tick, &runner, false);

    t1.enable();

    // Run the scheduler for a short while
    for (int i = 0; i < 200; ++i) {
        runner.execute();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "count=" << g_count << "\n";
    // Expect at least 5 invocations
    if (g_count < 5) return 1;
    return 0;
}
