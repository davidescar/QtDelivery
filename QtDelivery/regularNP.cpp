//regularNP.cpp

#include "regularNP.h"

double RegularNP::tariffaRegular=1.2;

RegularNP::RegularNP(double p, const Measures& dim, const ShippingLabel& e): NationalParcel(p,dim,e){}

RegularNP::~RegularNP(){}

double RegularNP::shippingCost() const{
    return NationalParcel::shippingCost()*tariffaRegular;
}

string RegularNP::typology() const{
    return "Regular";
}
