/*
mainWindow.h
La classe MainWindow rappresenta la finestra principale dell'applicazione.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainWidget.h"

class MainWindow : public QMainWindow
{Q_OBJECT
    private:
        MainWidget* widget;
        QAction* home;
        QAction* creaPacco;
        QAction* visualizza;
        QAction* svuota;
        QAction* cercaCostoso;
        QAction* cercaCategoria;
        QAction* spedisciPrimo;
        QAction* spedisciUltimo;
        QAction* spedisciIndice;
        QAction* spedisciTipologia;
        QAction* info;
        QAction* chiudi;
        QMenu* paccoMenu;
        QMenu* magazzinoMenu;
        QMenu* cercaMenu;
        QMenu* spedisciMenu;
        QMenu* infoMenu;
    public:
        MainWindow(QWidget* =0);
    public slots:
        void goHome();
        void showInfo();
        void newParcel();
        void viewStock();
        void clearDepot();
        void removeFirst();
        void removeLast();
        void selectIndex();
        void selectType();
        void removeIndex(int);
        void removeType(const QString&);
        void searchExpensive();
        void chooseCategory();
        void searchCategory(const QString&);
};

#endif // MAINWINDOW_H
