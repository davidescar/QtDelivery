/*
La classe Table rappresenta in forma tabellare su di un
widget, l'intero contenuto del magazzino dell'azienda.
*/

#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include "stock.h"

class Table: public QTableWidget{
    private:
        Stock* val;
    public:
        Table(QWidget* =0, Stock* =0);
};

#endif // TABLE_H
