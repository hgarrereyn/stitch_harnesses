#include <libconfig.h++>
#include <iostream>

int main() {
  libconfig::Config cfg;
  const char *text = "root: { answer=42; flag=true; name=\"test\"; list=(1,2,3); }";
  try {
    cfg.readString(text);
  } catch(const libconfig::ParseException &e) {
    std::cout << "parse error: " << e.what() << "\n";
    return 0;
  }
  const libconfig::Setting &root = cfg.getRoot();
  const libconfig::Setting &grp = root["root"];
  int answer = 0; bool flag = false; std::string name;
  grp.lookupValue("answer", answer);
  grp.lookupValue("flag", flag);
  grp.lookupValue("name", name);
  std::cout << "answer=" << answer << ", flag=" << (flag?"true":"false") << ", name=" << name << "\n";
  return 0;
}
