/*
address.h
La classe Address rappresenta un indirizzo nel seguente formato
di esempio: via Roma 10, 35100
N.B.: il CAP (Codice di Avviamento Postale) viene rappresentato
attraverso il tipo string, poichè può iniziare anche per 0, e
quindi non può essere un int (nel caso specifico, un unsigned int
come l'attributo numeroCivico)
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Address{
    private:
        string via;
        unsigned int numeroCivico;
        string CAP;
    public:
        Address(string ="null", unsigned int =0, string ="00000");
        string getVia() const;
        unsigned int getNumeroCivico() const;
        string getCAP() const;
        void setVia(string);
        void setNumeroCivico(unsigned int);
        void setCAP(string);
        bool operator==(const Address&) const;
        bool operator!=(const Address&) const;
};

ostream& operator<<(ostream&, const Address&);

#endif
