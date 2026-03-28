#include <QtWidgets/QApplication>
#include <iostream>
#include "Timer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Timer w;
    w.show();
    return a.exec();
}

