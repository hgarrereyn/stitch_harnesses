#include <iostream>
#include <string>
#include "tiny_obj_loader.h"

int main() {
  // Minimal OBJ and MTL content
  const std::string obj =
      "mtllib test.mtl\n"
      "v 0 0 0\n"
      "v 1 0 0\n"
      "v 0 1 0\n"
      "usemtl material0\n"
      "f 1 2 3\n";
  const std::string mtl =
      "newmtl material0\n"
      "Kd 1.0 0.5 0.25\n";

  tinyobj::ObjReaderConfig cfg; // defaults are fine
  tinyobj::ObjReader reader;

  if (!reader.ParseFromString(obj, mtl, cfg)) {
    std::cerr << "Parse error: " << reader.Error() << "\n";
    return 1;
  }

  const auto &attrib = reader.GetAttrib();
  const auto &shapes = reader.GetShapes();
  const auto &materials = reader.GetMaterials();

  std::cout << "vtx=" << (attrib.vertices.size() / 3)
            << ", shapes=" << shapes.size()
            << ", materials=" << materials.size() << "\n";

  // Ensure we accessed something to force ODR usage
  if (!shapes.empty() && !shapes[0].mesh.indices.empty()) {
    auto idx = shapes[0].mesh.indices[0];
    (void)idx.vertex_index;
  }

  return 0;
}
