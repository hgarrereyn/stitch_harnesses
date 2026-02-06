#include <OGRE/Ogre.h>
#include <iostream>
int main(){
    Ogre::Vector3 a(1.0f, 2.0f, 3.0f);
    Ogre::Vector3 b = a.normalisedCopy();
    std::cout << "len(a)=" << a.length() << ", b=(" << b.x << "," << b.y << "," << b.z << ")\n";
    return 0;
}
