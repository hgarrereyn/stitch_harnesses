#include <iostream>
#include <string>
#include <cstring>

#include "tiny_gltf.h"

int main() {
  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err, warn;

  const char* src = "{\n"
                    "  \"asset\": { \"version\": \"2.0\" },\n"
                    "  \"scenes\": [ { \"nodes\": [] } ],\n"
                    "  \"scene\": 0\n"
                    "}";

  bool ok = loader.LoadASCIIFromString(&model, &err, &warn, src, strlen(src),
                                       /*base_dir*/ "", /*check_sections*/ 0);

  std::cout << "warn: " << warn << "\n";
  std::cout << "err: " << err << "\n";
  std::cout << "ok: " << (ok ? "true" : "false") << "\n";
  std::cout << "scenes: " << model.scenes.size() << "\n";
  return 0;
}
