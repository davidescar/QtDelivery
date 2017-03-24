/*
fastNP.h
La classe FastNP deriva direttamente dalla classe NationaParcel, e rappresenta
un pacco di spedizione nazionale veloce.
*/

#ifndef FASTNP_H
#define FASTNP_H

#include "nationalParcel.h"

class FastNP: public NationalParcel{
    private:
        static double tariffaFast;
    public:
        FastNP(double, const Measures&, const ShippingLabel&);
        virtual ~FastNP();
        virtual double shippingCost() const;
        virtual string typology() const;
};
#endif // FASTNP_H
