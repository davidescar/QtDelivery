/*
parcel.h
La classe Parcel rappresenta un generico pacco di spedizione, caratterizzato
dalle seguenti informazioni: peso, dimensioni ed etichetta.
N.B.: per qualsiasi pacco è prevista una tassa base.
*/

#ifndef PARCEL_H
#define PARCEL_H

#include "measures.h"
#include "shippingLabel.h"
#include <string>

class Parcel{
    private:
        double peso; //peso espresso in kg
        Measures dimensione;
        ShippingLabel etichetta;
        static double tariffaKg; //tariffa per kg
        static double coefficientePV; //coefficiente peso volumetrico
    public:
        Parcel(double =0.0, const Measures& =Measures(), const ShippingLabel& =ShippingLabel());
        double getPeso() const;
        Measures getDimensione() const;
        ShippingLabel getEtichetta() const;
        void setPeso(double);
        void setDimensione(const Measures&);
        void setEtichetta(const ShippingLabel&);
        virtual ~Parcel(); //distruttore virtuale
        double pesoVolumetrico() const;
        virtual double shippingCost() const; //metodo virtuale
        virtual string typology() const; //metodo virtuale per sapere il tipo di pacco
        string categoryParcel() const;
        bool operator==(const Parcel&) const;
        bool operator!=(const Parcel&) const;
};

ostream& operator<<(ostream&, const Parcel&);

#endif // PARCEL_H
