#include <iostream>
#include <QtCore/QCoreApplication>
#include "path.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Path::initialize(true);
    std::cout << "LogDir: " << Path::getLogDir().toStdString() << std::endl;
    auto info = Path::getCacheFileInfo("test.cache");
    std::cout << "Cache path: " << info.absoluteFilePath().toStdString() << std::endl;
    return 0;
}
