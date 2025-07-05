#include "monitordialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MonitorDialog w;
    w.show();
    return a.exec();
}
