/*
internationalParcel.h
La classe InternationalParcel deriva dalla classa base astratta Parcel, e rappresenta
un pacco di spedizione internazionale.
Ciò significa che è presente un campo dati statico indicante la tassa
per le spedizioni verso l'estero.
*/

#ifndef INTERNATIONALPARCEL_H
#define INTERNATIONALPARCEL_H

#include "parcel.h"

class InternationalParcel: public Parcel{
    private:
        static double tassaEstero;
    public:
        InternationalParcel(double, const Measures&, const ShippingLabel&);
        virtual ~InternationalParcel();
        virtual double shippingCost() const;
        virtual string typology() const;
};

#endif // INTERNATIONALPARCEL_H
