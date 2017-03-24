//nationalParcel.cpp

#include "nationalParcel.h"

double NationalParcel::tassaNazionale=12.0;

NationalParcel::NationalParcel(double p, const Measures& dim, const ShippingLabel& e): Parcel(p,dim,e){}

NationalParcel::~NationalParcel(){};

double NationalParcel::shippingCost() const{
    return Parcel::shippingCost()+tassaNazionale;
}

string NationalParcel::typology() const{
    return "National";
}
