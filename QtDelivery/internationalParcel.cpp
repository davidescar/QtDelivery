//internationalParcel.cpp

#include "internationalParcel.h"

double InternationalParcel::tassaEstero=25.0;

InternationalParcel::InternationalParcel(double p, const Measures& dim, const ShippingLabel& e): Parcel(p,dim,e){}

InternationalParcel::~InternationalParcel(){};

double InternationalParcel::shippingCost() const{
    return Parcel::shippingCost()+tassaEstero;
}

string InternationalParcel::typology() const{
    return "International";
}
