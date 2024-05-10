#include "mainwindow.h"
#include "storage.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    try {
        Q_UNUSED(Storage::_());
    } catch (std::runtime_error& err) {
        qCritical() << err.what();
        return -1;
    }

    // ***

    QApplication a(argc, argv);
    MainWindow w; w.show();
    return a.exec();
}
