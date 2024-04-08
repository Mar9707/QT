#include "mainwindow.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Your PlayList");
    w.setWindowIcon(QIcon(":/icon.png"));
    w.show();
    return a.exec();
}
