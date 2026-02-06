#include <bcc/BPF.h>
#include <iostream>

int main() {
  ebpf::BPF b; // default-constructed, no kernel interaction
  std::string sc = b.get_syscall_fnname("open");
  std::cout << "bcc loaded, syscall name: " << sc << "\n";
  return 0;
}
