/*
shippingLabel.h
La classe ShippingLabel rappresenta una etichetta di spedizione, caratterizzata
da un mittente e un destinatario.
*/

#ifndef SHIPPINGLABEL_H
#define SHIPPINGLABEL_H

#include "entity.h"

class ShippingLabel{
    private:
        Entity mittente;
        Entity destinatario;
    public:
        ShippingLabel(const Entity& =Entity(), const Entity& =Entity());
        Entity getMittente() const;
        Entity getDestinatario() const;
        void setMittente(const Entity&);
        void setDestinatario(const Entity&);
        bool operator==(const ShippingLabel&) const;
        bool operator!=(const ShippingLabel&) const;
};

ostream& operator<<(ostream&, const ShippingLabel&);

#endif // SHIPPINGLABEL_H
