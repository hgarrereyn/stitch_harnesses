#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>

int main() {
    // Minimal OBJ content: one triangle
    const std::string obj =
        "v 0 0 0\n"
        "v 1 0 0\n"
        "v 0 1 0\n"
        "f 1 2 3\n";

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(
        obj.data(), obj.size(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices,
        "obj");

    if (!scene || !scene->mRootNode) {
        std::cerr << "Import failed: " << importer.GetErrorString() << "\n";
        return 1;
    }

    unsigned meshes = scene->mNumMeshes;
    unsigned vertices = 0;
    for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
        vertices += scene->mMeshes[i]->mNumVertices;
    }
    std::cout << "Meshes: " << meshes << ", Vertices: " << vertices << "\n";
    return 0;
}
