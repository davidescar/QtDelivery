/*
mainWidget.h
La classe MainWidget rappresenta il widget principale della MainWindow.
*/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "myForm.h"
#include "stock.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QTextEdit>

class MainWidget: public QWidget
{Q_OBJECT
    friend class MainWindow;
    private:
        QVBoxLayout* grid;
        Stock deposito;
    protected:
        int removeParcelTypology(const QString&, double&);
        void messageError() const;
    public:
        MainWidget(QWidget* =0);
        int countItem() const;
        void setStyleTextBlock(QTextEdit*) const;
        void setStyleButtonParcel(QPushButton*, const QString&) const;
        void setInfo();
        void showParcelRemoved(const Parcel*) const;
        void setHome();
    public slots:
        void clearWidget();
        void home();
        void showContent();
        void chooseParcel();
        void newParcel(const QString&);
        void deleteAllParcels();
        void deleteFirstParcel();
        void deleteLastParcel();
        void deleteIndex(int);
        void deleteTypology(const QString&);
        void searchParcelCostMax();
        void searchForCategory(const QString&);
};

#endif // MAINWIDGET_H
