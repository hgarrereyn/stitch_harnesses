#include <iostream>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include "SeerUtl.h"

int main() {
    // Exercise a couple of Seer utility functions
    QString v = Seer::version();
    QString s = "Line1\\nLine2\\tTab";
    QString filtered = Seer::filterEscapes(s);

    std::cout << "Seer version: " << v.toStdString() << "\n";
    std::cout << "Filtered: " << filtered.toStdString() << "\n";
    return 0;
}
