#include <iostream>
#include <opensubdiv/version.h>
#include <opensubdiv/sdc/types.h>
#include <opensubdiv/sdc/options.h>
#include <opensubdiv/far/topologyDescriptor.h>
#include <opensubdiv/far/topologyRefinerFactory.h>
#include <opensubdiv/far/topologyRefiner.h>

int main() {
    typedef OpenSubdiv::Far::TopologyDescriptor Descriptor;

    static int numVertsPerFace[] = {4};
    static OpenSubdiv::Far::Index vertIndicesPerFace[] = {0, 1, 2, 3};

    Descriptor desc;
    desc.numVertices = 4;
    desc.numFaces = 1;
    desc.numVertsPerFace = numVertsPerFace;
    desc.vertIndicesPerFace = vertIndicesPerFace;

    OpenSubdiv::Sdc::SchemeType type = OpenSubdiv::Sdc::SCHEME_CATMARK;
    OpenSubdiv::Sdc::Options options;

    OpenSubdiv::Far::TopologyRefiner *refiner =
        OpenSubdiv::Far::TopologyRefinerFactory<Descriptor>::Create(
            desc,
            OpenSubdiv::Far::TopologyRefinerFactory<Descriptor>::Options(type, options));

    if (!refiner) {
        std::cout << "Failed to create TopologyRefiner" << std::endl;
        return 1;
    }

    refiner->RefineUniform(OpenSubdiv::Far::TopologyRefiner::UniformOptions(1));

    int maxLevel = refiner->GetMaxLevel();
    int numVerts = refiner->GetLevel(maxLevel).GetNumVertices();
    std::cout << "OpenSubdiv version number: " << OPENSUBDIV_VERSION_NUMBER << "\n";
    std::cout << "Refined to level " << maxLevel << ", vertex count: " << numVerts << "\n";

    delete refiner;
    return 0;
}
