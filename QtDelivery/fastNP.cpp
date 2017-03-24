//fastNP.cpp

#include "fastNP.h"

double FastNP::tariffaFast=1.5;

FastNP::FastNP(double p, const Measures& dim, const ShippingLabel& e): NationalParcel(p,dim,e){}

FastNP::~FastNP(){}

double FastNP::shippingCost() const{
    return NationalParcel::shippingCost()*tariffaFast;
}

string FastNP::typology() const{
    return "Fast";
}
