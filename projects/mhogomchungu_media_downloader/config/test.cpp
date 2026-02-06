#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <iostream>

#include "media-downloader/threads.hpp"

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);

    struct Task {
        int bg() { return 7 * 6; }
        void fg(int v) {
            std::cout << "utils::qthread::run result: " << v << std::endl;
            QTimer::singleShot(0, &QCoreApplication::quit);
        }
    };

    utils::qthread::run(Task{});

    return app.exec();
}
