/*
myForm.h
La classe MyForm rappresenta il form per l'inserimento dei dati
relativi ad un nuovo pacco.
*/


#ifndef MYFORM_H
#define MYFORM_H

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include "stock.h"
#include "input.h"
#include "messageToUser.h"

class MyForm: public QDialog
{Q_OBJECT
    private:
        QString tipo;
        Input* datiForm;
        Stock* valori;
        QPushButton* ok;
        QPushButton* annulla;
    public:
        MyForm(QWidget* =0, const QString& ="", Stock* =0);
        bool isValidMeasure(double, double, double) const;
        bool isValidEntity(const QString&, const QString&, const QString&, int, const QString&) const;
    public slots:
        void checkDatiForm();
};

#endif // MYFORM_H
