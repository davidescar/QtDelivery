//main.cpp

#include "mainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/logo.jpg"));
    MainWindow m;
    QObject::connect(qApp,SIGNAL(lastWindowClosed()),qApp,SLOT(quit()));
    m.show();
    return app.exec();
}
