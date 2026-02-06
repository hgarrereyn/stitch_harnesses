#include <iostream>
#include "lldb-eval/api.h"
#include "lldb/API/SBError.h"
#include "lldb/API/SBFrame.h"

int main() {
  using FnType = lldb::SBValue (*)(lldb::SBFrame, const char*, lldb::SBError&);
  FnType fn = &lldb_eval::EvaluateExpression; // select one overload explicitly
  (void)fn;
  std::cout << "lldb-eval API is available" << std::endl;
  return 0;
}
