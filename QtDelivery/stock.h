/*
La classe Stock rappresenta il contenuto del magazzino dell'azienda,
il quale contiene tutti i pacchi attualmente in giacenza,
elaborati e pronti per la spedizione.
*/

#ifndef STOCK_H
#define STOCK_H

#include "depot.h"
#include "regularNP.h"
#include "fastNP.h"
#include "internationalParcel.h"
#include <QString>

class Stock{
    friend class MainWidget;
    private:
        Depot<Parcel*> magazzino;
    protected:
        int contaNational() const;
        int contaInternational() const;
    public:
        Stock();
        Stock(const QString&);
        void aggiungi(const Parcel&);
        Parcel* getParcel(int) const;
        int size() const;
        bool vuoto() const;
        int svuotaTutto();
        Parcel* removeFirst();
        Parcel* removeLast();
        Parcel* removeInd(int);
        int removeParcelType(const QString&, double&);
        Parcel* searchCostMax(int&) const;
        void searchCateg(const QString&, Stock&) const;
};

#endif // STOCK_H
