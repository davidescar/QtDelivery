/*
depot.h
Il template di classe Depot rappresenta un contenitore per oggetti polimorfi,
nel nostro caso servirà come deposito/magazzino per i pacchi dell'azienda.
Permette le tipiche operazioni per un contenitore: aggiunta, rimozione,
modifica, ricerca, dimensione, etc...
N.B.: il contenitore viene implementato con una lista doppiamente linkata.
*/

#ifndef DEPOT_H
#define DEPOT_H

#include <iostream>
using namespace std;

template<class T> class Depot; //dichiarazione incompleta del template di classe Depot
template<class T> ostream& operator<<(ostream&, const Depot<T>&);

template<class T>
class Link{
    public:
        Link(const T& =T(), Link<T>* =0, Link<T>* =0);
        ~Link(); //distruttore profondo
        T info;
        Link<T>* next;
        Link<T>* prev;
};

template<class T>
class Iterator{
    friend class Depot<T>;
    private:
        Link<T>* punt; //nodo puntato dall'iteratore
    public:
        Iterator(Link<T>* =0);
        Iterator(const Iterator<T>&); //costruttore di copia
        Iterator<T>& operator=(const Iterator<T>&); //assegnazione
        bool operator==(const Iterator<T>&) const; //operatore di uguaglianza
        bool operator!=(const Iterator<T>&) const; //operatore di disuguaglianza
        Iterator<T>& operator++(); //operator++ prefisso
        Iterator<T> operator++(int); //operatore++ postfisso
        Iterator<T>& operator--(); //operator-- prefisso
        Iterator<T> operator--(int); //operatore-- postfisso
        T& operator*(); //operatore di dereferenziazione
};

template<class T>
class Depot{
    friend class Iterator<T>; //dichiarazione di amicizia
    private:
        Link<T>* first; //puntatore al primo nodo della lista
        Link<T>* last; //puntatore all'ultimo nodo della lista
        unsigned int dimensione; //dimensione della lista
        static Link<T>* copy(Link<T>*);
        static Link<T>* getLast(Link<T>*);
    public:
        Depot(); //costruttore default
        ~Depot(); //distruttore profondo
        Depot(const Depot<T>&); //costruttore di copia profonda
        Depot<T>& operator=(const Depot<T>&); //assegnazione profonda
        bool isEmpty() const;
        unsigned int size() const;
        void push_front(const T&);
        void push_back(const T&);
        T pop_front();
        T pop_back();
        void remove(const T&);
        void remove_last();
        void erase(Iterator<T>&);
        void clear();
        bool search(const T&) const;
        Iterator<T> begin() const;
        Iterator<T> end() const;
        T& operator[](const Iterator<T>&) const;
        friend ostream& operator<< <T>(ostream&, const Depot<T>&);
};

#endif // DEPOT_H
