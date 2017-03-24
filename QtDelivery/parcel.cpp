//parcel.cpp

#include "parcel.h"

double Parcel::tariffaKg=2.0;
double Parcel::coefficientePV=5000.0; // 1 m^3 = 1000000 cm^3 = 200 kg

Parcel::Parcel(double p, const Measures& dim, const ShippingLabel& e): peso(p),dimensione(dim),etichetta(e){}

Parcel::~Parcel(){}

double Parcel::getPeso() const{
    return peso;
}

Measures Parcel::getDimensione() const{
    return dimensione;
}

ShippingLabel Parcel::getEtichetta() const{
    return etichetta;
}

void Parcel::setPeso(double p){
    peso=p;
}

void Parcel::setDimensione(const Measures& dim){
    dimensione=dim;
}

void Parcel::setEtichetta(const ShippingLabel& e){
    etichetta=e;
}

double Parcel::pesoVolumetrico() const{
    return (getDimensione().volume())/coefficientePV;
}

double Parcel::shippingCost() const{
    return (getPeso()>pesoVolumetrico() ? getPeso() : pesoVolumetrico())*tariffaKg;
}

string Parcel::typology() const{
    return "Base";
}

string Parcel::categoryParcel() const{
    if(dimensione.volume()<9000.0)
        return "Small";
    if(dimensione.volume()<15000.0)
        return "Medium";
    return "Large";
}

bool Parcel::operator==(const Parcel& pacco) const{
    return peso==pacco.getPeso() && dimensione==pacco.getDimensione();
}

bool Parcel::operator!=(const Parcel& pacco) const{
    return peso!=pacco.getPeso() || dimensione!=pacco.getDimensione();
}

ostream& operator<<(ostream& os, const Parcel& pacco){
    return os << "Peso: " << pacco.getPeso() << " kg" << std::endl << "Dimensioni: " << pacco.getDimensione() << pacco.getEtichetta() << std::endl;
}
