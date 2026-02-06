#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreOgawa/All.h>
#include <iostream>

int main() {
    using namespace Alembic::AbcGeom;
    // Write a simple archive using the Ogawa backend in its own scope
    {
        Alembic::Abc::OArchive oarch(Alembic::AbcCoreOgawa::WriteArchive(), "/tmp/test.abc");
        OObject top = oarch.getTop();
        OXform xform(top, "rootXform");
        XformSample xs;
        xs.addOp(kTranslateOperation, Imath::V3d(1.0, 2.0, 3.0));
        xform.getSchema().set(xs);
    } // ensure archive is closed before reading

    // Read it back and print the translation from the matrix
    Alembic::Abc::IArchive iarch(Alembic::AbcCoreOgawa::ReadArchive(), "/tmp/test.abc");
    auto itop = iarch.getTop();
    IXform ix(itop, "rootXform");
    auto ischema = ix.getSchema();
    auto sample = ischema.getValue();
    Imath::M44d m = sample.getMatrix();
    std::cout << m[3][0] << "," << m[3][1] << "," << m[3][2] << std::endl;

    return 0;
}
