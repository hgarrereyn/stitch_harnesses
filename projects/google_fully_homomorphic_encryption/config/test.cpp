#include <iostream>
#include "transpiler/data/primitives.h"

// Forward declare the function defined in primitives.cc
void my_package(PrimitiveBool& b, PrimitiveChar& c, PrimitiveSignedChar& sc,
                PrimitiveUnsignedChar& uc, PrimitiveSignedShort& ss,
                PrimitiveUnsignedShort& us, PrimitiveSignedInt& si,
                PrimitiveUnsignedInt& ui, PrimitiveSignedLong& sl,
                PrimitiveUnsignedLong& ul);

int main() {
  PrimitiveBool b{true};
  PrimitiveChar c{'A'};
  PrimitiveSignedChar sc{-1};
  PrimitiveUnsignedChar uc{255};
  PrimitiveSignedShort ss{-123};
  PrimitiveUnsignedShort us{456};
  PrimitiveSignedInt si{-789};
  PrimitiveUnsignedInt ui{1011};
  PrimitiveSignedLong sl{-1213};
  PrimitiveUnsignedLong ul{1415};
  my_package(b, c, sc, uc, ss, us, si, ui, sl, ul);
  std::cout << "Ran my_package with primitive structs.\n";
  return 0;
}
