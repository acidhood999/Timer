#include "Timer.h"
#include <QSharedMemory>
#include <QMessageBox>

using namespace std;

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);

    QSharedMemory sharedMemory("acidhood999_TimerQT_UniqueKey");

    if (sharedMemory.attach())
    {
        QMessageBox::warning(nullptr, "Warning", "The application is already launched!");
        return 0;
    }

    if (!sharedMemory.create(1)) return 0;

    Timer w;
    w.show();
    return a.exec();
}

