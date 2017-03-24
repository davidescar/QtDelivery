//address.cpp

#include "address.h"

Address::Address(string v, unsigned int nciv, string c): via(v),numeroCivico(nciv),CAP(c){}

string Address::getVia() const{
    return via;
}

unsigned int Address::getNumeroCivico() const{
    return numeroCivico;
}

string Address::getCAP() const{
    return CAP;
}

void Address::setVia(string v){
    via=v;
}

void Address::setNumeroCivico(unsigned int nciv){
    numeroCivico=nciv;
}

void Address::setCAP(string c){
    CAP=c;
}

bool Address::operator==(const Address& a) const{
    return via==a.getVia() && numeroCivico==a.getNumeroCivico() && CAP==a.getCAP();
}

bool Address::operator!=(const Address& a) const{
    return CAP!=a.getCAP() || via!=a.getVia() || numeroCivico!=a.getNumeroCivico();
}

ostream& operator<<(ostream& os, const Address& a){
    return os << a.getVia() << " " << a.getNumeroCivico() << ", " << a.getCAP() << std::endl;
}
