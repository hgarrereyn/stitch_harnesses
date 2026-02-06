#include <iostream>
#include <string>
#include "utf8.hh"

int main() {
  using gd::wstring;
  using gd::wchar;
  // Prepare a small wstring with some non-ASCII characters
  wstring ws; 
  ws.push_back((wchar)'H');
  ws.push_back((wchar)'e');
  ws.push_back((wchar)'l');
  ws.push_back((wchar)'l');
  ws.push_back((wchar)'o');
  ws.push_back((wchar)0x20AC); // Euro sign

  std::string utf8 = Utf8::encode(ws);
  wstring round = Utf8::decode(utf8);

  if (round != ws) {
    std::cerr << "Roundtrip failed" << std::endl;
    return 1;
  }
  std::cout << "OK: size=" << utf8.size() << std::endl;
  return 0;
}
