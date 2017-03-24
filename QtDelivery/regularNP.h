/*
regularNP.h
La classe regularNP deriva direttamente dalla classe NationaParcel, e rappresenta
un pacco di spedizione nazionale regolare.
*/

#ifndef REGULARNP_H
#define REGULARNP_H

#include "nationalParcel.h"

class RegularNP: public NationalParcel{
    private:
        static double tariffaRegular;
    public:
        RegularNP(double, const Measures&, const ShippingLabel&);
        virtual ~RegularNP();
        virtual double shippingCost() const;
        virtual string typology() const;
};

#endif // REGULARNP_H
