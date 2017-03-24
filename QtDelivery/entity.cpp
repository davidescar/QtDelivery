//entity.cpp

#include "entity.h"

Entity::Entity(string n, string c, const Address& i): nome(n),cognome(c),indirizzo(i){}

string Entity::getNome() const{
    return nome;
}

string Entity::getCognome() const{
    return cognome;
}

Address Entity::getIndirizzo() const{
    return indirizzo;
}

void Entity::setNome(string n){
    nome=n;
}

void Entity::setCognome(string c){
    cognome=c;
}

void Entity::setIndirizzo(const Address& i){
    indirizzo=i;
}

bool Entity::operator==(const Entity& e) const{
    return nome==e.getNome() && cognome==e.getCognome() && indirizzo==e.getIndirizzo();
}

bool Entity::operator!=(const Entity& e) const{
    return indirizzo!=e.getIndirizzo() || nome!=e.getNome() || cognome!=e.getCognome();
}

ostream& operator<<(ostream& os, const Entity& e){
    return os << e.getNome() << " " << e.getCognome() << std::endl << e.getIndirizzo();
}
