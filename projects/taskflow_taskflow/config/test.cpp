#include <taskflow/taskflow.hpp>
#include <iostream>

int main() {
  tf::Executor executor;
  tf::Taskflow taskflow;

  auto [A, B, C, D] = taskflow.emplace(
    [](){ /* A */ },
    [](){ /* B */ },
    [](){ /* C */ },
    [](){ /* D */ }
  );

  A.precede(B, C);
  D.succeed(B, C);

  executor.run(taskflow).wait();
  std::cout << "Taskflow ran successfully" << std::endl;
  return 0;
}
