#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/version.h>
#include <iostream>

int main() {
    std::cout << "Assimp version: "
              << aiGetVersionMajor() << "." << aiGetVersionMinor() << "." << aiGetVersionRevision()
              << std::endl;
    Assimp::Importer importer;
    // Create a tiny in-memory OBJ to exercise the API
    const char* obj = "v 0 0 0\n" "v 1 0 0\n" "v 0 1 0\n" "f 1 2 3\n";
    const aiScene* scene = importer.ReadFileFromMemory(
        obj, strlen(obj), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices, "obj");
    if (!scene) {
        std::cout << "Import failed (expected on minimal input is either ok or null): "
                  << importer.GetErrorString() << std::endl;
    } else {
        std::cout << "Imported meshes: " << scene->mNumMeshes << std::endl;
    }
    return 0;
}
