#include "arkanoid.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Arkanoid w;
    w.show();

    return a.exec();
}
