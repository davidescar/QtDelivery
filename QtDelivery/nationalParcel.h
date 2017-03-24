/*
nationalParcel.h
La classe NationalParcel deriva dalla classa base Parcel, e rappresenta
un pacco di spedizione nazionale.
Ciò significa che è presente un campo dati statico indicante la tassa
per le spedizioni all'interno del Paese.
*/

#ifndef NATIONALPARCEL_H
#define NATIONALPARCEL_H

#include "parcel.h"

class NationalParcel: public Parcel{
    private:
        static double tassaNazionale;
    public:
        NationalParcel(double, const Measures&, const ShippingLabel&);
        virtual ~NationalParcel();
        virtual double shippingCost() const;
        virtual string typology() const;
};

#endif // NATIONALPARCEL_H
