//shippingLabel.cpp

#include "shippingLabel.h"

ShippingLabel::ShippingLabel(const Entity& mit, const Entity& dest): mittente(mit),destinatario(dest){}

Entity ShippingLabel::getMittente() const{
    return mittente;
}

Entity ShippingLabel::getDestinatario() const{
    return destinatario;
}

void ShippingLabel::setMittente(const Entity& mit){
    mittente=mit;
}

void ShippingLabel::setDestinatario(const Entity& dest){
    destinatario=dest;
}

bool ShippingLabel::operator==(const ShippingLabel& label) const{
    return mittente==label.getMittente() && destinatario==label.getDestinatario();
}

bool ShippingLabel::operator!=(const ShippingLabel& label) const{
    return mittente!=label.getMittente() || destinatario!=label.getDestinatario();
}

ostream& operator<<(ostream& os, const ShippingLabel& l){
    return os << "Mittente: " << l.getMittente() << "Destinatario: " << l.getDestinatario() << std::endl;
}
