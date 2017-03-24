//measures.cpp

#include "measures.h"

Measures::Measures(double alt, double lar, double prof): altezza(alt),larghezza(lar),profondita(prof){}

double Measures::getAltezza() const{
    return altezza;
}

double Measures::getLarghezza() const{
    return larghezza;
}

double Measures::getProfondita() const{
    return profondita;
}

void Measures::setAltezza(double alt){
    altezza=alt;
}

void Measures::setLarghezza(double lar){
    larghezza=lar;
}

void Measures::setProfondita(double prof){
    profondita=prof;
}

bool Measures::operator==(const Measures& dim) const{
    return altezza==dim.getAltezza() && larghezza==dim.getLarghezza() && profondita==dim.getProfondita();
}

bool Measures::operator!=(const Measures& dim) const{
    return altezza!=dim.getAltezza() || larghezza!=dim.getLarghezza() || profondita!=dim.getProfondita();
}

bool Measures::operator>(const Measures& dim) const{
    return volume()>dim.volume();
}

bool Measures::operator>=(const Measures& dim) const{
    return volume()>=dim.volume();
}

bool Measures::operator<(const Measures& dim) const{
    return volume()<dim.volume();
}

bool Measures::operator<=(const Measures& dim) const{
    return volume()<=dim.volume();
}

double Measures::volume() const{
    return altezza*larghezza*profondita;
}

ostream& operator<<(ostream& os, const Measures& dim){
    return os << dim.getAltezza() << "x" << dim.getLarghezza() << "x" << dim.getProfondita() << " cm" << std::endl;
}
