/*
entity.h
La classe Entity rappresenta un generico ente/individuo/persona, avente
le seguenti caratteristiche: nome, cognome e indirizzo.
N.B.: indirizzo è di tipo definito da utente (Address)
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include "address.h"

class Entity{
    private:
        string nome;
        string cognome;
        Address indirizzo;
    public:
        Entity(string ="null", string ="null", const Address& =Address());
        string getNome() const;
        string getCognome() const;
        Address getIndirizzo() const;
        void setNome(string);
        void setCognome(string);
        void setIndirizzo(const Address&);
        bool operator==(const Entity&) const;
        bool operator!=(const Entity&) const;
};

ostream& operator<<(ostream&, const Entity&);

#endif // ENTITY_H
