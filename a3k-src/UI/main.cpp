#include "a3k.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a3k w;
    w.show();

    return a.exec();
}
