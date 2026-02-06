#include <QCoreApplication>
#include <QDateTime>
#include <iostream>
#include "/fuzz/install/include/zeal/util/humanizer.h"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    QDateTime dt = QDateTime::currentDateTime().addSecs(-90);
    QString human = Zeal::Util::Humanizer::fromNow(dt);
    std::cout << human.toStdString() << std::endl;
    return 0;
}
