//depot.cpp

#include "depot.h"
#include "parcel.h"

template<class T>
Link<T>::Link(const T& x, Link<T>* n, Link<T>* p): info(x),next(n),prev(p){}

template<class T>
Link<T>::~Link(){
    if(next)
        delete next; //distruzione profonda
}

template<class T>
Link<T>* Depot<T>::copy(Link<T>* f){
    if(!f)
        return 0;
    Link<T>* tempFirst=new Link<T>(f->info,0,0);
    Link<T>* p=tempFirst;
    while(f->next!=0){
        p->next=new Link<T>(f->next->info,p,0);
        p=p->next;
        f=f->next;
    }
    return tempFirst;
}

template<class T>
Link<T>* Depot<T>::getLast(Link<T>* f){
    if(!f)
        return 0;
    while(f->next!=0){
        f=f->next;
    }
    return f;
}

template<class T>
Iterator<T>::Iterator(Link<T>* p): punt(p){}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& it): punt(it.punt){}

template<class T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& it){
    if(punt!=it.punt){
        delete punt;
        punt=it.punt;
    }
    return *this;
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& it) const{
    return punt==it.punt;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& it) const{
    return punt!=it.punt;
}

template<class T>
Iterator<T>& Iterator<T>::operator++(){
    if(punt)
        punt=punt->next;
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int z){
    Iterator<T> aux=*this;
    if(punt)
        punt=punt->next;
    return aux;
}

template<class T>
Iterator<T>& Iterator<T>::operator--(){
    if(punt)
        punt=punt->prev;
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator--(int z){
    Iterator<T> aux=*this;
    if(punt)
        punt=punt->prev;
    return aux;
}

template<class T>
T& Iterator<T>::operator*(){
    return punt->info;
}

template<class T>
Iterator<T> Depot<T>::begin() const{
    Iterator<T> aux;
    aux.punt=first;
    return aux;
}

template<class T>
Iterator<T> Depot<T>::end() const{
    Iterator<T> aux;
    aux.punt=last->next;
    return aux;
}

template<class T>
T& Depot<T>::operator[](const Iterator<T>& it) const{
    return (it.punt)->info;
}

template<class T>
Depot<T>::Depot(): first(0),last(0),dimensione(0){}

template<class T>
Depot<T>::~Depot(){
    if(first)
        delete first; //chiamata ricorsiva al distruttore (profondo) di Link ridefinito
}

template<class T>
Depot<T>::Depot(const Depot<T>& d): first(copy(d.first)),last(getLast(d.first)),dimensione(d.dimensione){}

template<class T>
Depot<T>& Depot<T>::operator=(const Depot<T>& d){
    if(this!=&d){
        if(first){
            delete first;
        }
        first=copy(d.first);
        last=getLast(d.first);
        dimensione=d.dimensione;
    }
    return *this;
}

template<class T>
bool Depot<T>::isEmpty() const{
    return first==0;
}

template<class T>
unsigned int Depot<T>::size() const{
    return dimensione;
}

template<class T>
void Depot<T>::push_front(const T& x){
    if(first){
        first=new Link<T>(x,first,0);
        (first->next)->prev=first;
    }else //contenitore vuoto
        first=last=new Link<T>(x,0,0);
    dimensione++;
}

template<class T>
void Depot<T>::push_back(const T& x){
    if(first){
        last->next=new Link<T>(x,0,last);
        last=last->next;
    }else //contenitore vuoto
        first=last=new Link<T>(x,0,0);
    dimensione++;
}

template<class T>
T Depot<T>::pop_front(){
    if(size()>1){
        Link<T>* temp=first->next;
        temp->prev=0;
        first->next=0; //stacco il nodo da eliminare dal resto della lista
        T p=first->info;
        delete first;
        first=temp;
        dimensione--;
        return p;
    }else if(size()==1){ //first==last
        T p=first->info;
        delete first;
        first=last=0;
        dimensione--;
        return p;
    }else //size()==0 --> contenitore vuoto
        return 0;
}

template<class T>
T Depot<T>::pop_back(){
    if(size()>1){
        Link<T>* temp=last->prev;
        temp->next=0;
        last->prev=0; //stacco il nodo da eliminare dal resto della lista
        T p=last->info;
        delete last;
        last=temp;
        dimensione--;
        return p;
    }else if(size()==1){ //rimuovo ultimo elemento rimasto
        T p=last->info; //first==last
        delete last;
        first=last=0;
        dimensione--;
        return p;
    }else //size()==0 --> contenitore vuoto
        return 0;
}

template<class T>
void Depot<T>::remove(const T& x){
    if(!isEmpty()){
        bool trovato=false;
        Link<T>* aux=first;
        while(aux && !trovato){
            if(aux->info==x){
                trovato=true;
                (aux->prev)->next=aux->next;
                (aux->next)->prev=aux->prev;
                delete aux;
                dimensione--;
            }
            aux=aux->next;
        }
    }
}

template<class T>
void Depot<T>::remove_last(){
    if(!isEmpty()){
        Link<T>* l=last;
        last=l->prev;
        if(last){ //se non ho rimosso l'ultimo nodo rimasto
            last->next=0;
            last->prev=(l->prev)->prev;
        }else{
            first=last; //last=0
        }
        dimensione--;
        delete l;
    }
}

template<class T>
void Depot<T>::erase(Iterator<T>& it){
    if(size()==1){ //devo rimuovere l'ultimo nodo rimasto nella lista
        delete first;
        dimensione--;
        first=last=0;
        it.punt=0;
    }else if(size()>1){
        if(it.punt==first){
            Link<T>* temp=first->next;
            temp->prev=0;
            first->next=0; //stacco il nodo da eliminare dal resto della lista
            delete first;
            dimensione--;
            first=temp;
            it.punt=first; //imposto il nuovo nodo di inizio della lista
        }else if(it.punt==last){
            Link<T>* temp=last->prev;
            temp->next=0;
            last->prev=0; //stacco il nodo da eliminare dal resto della lista
            delete last;
            dimensione--;
            last=temp; //imposto il nuovo nodo di inizio della lista
            it.punt=last;
        }else{
            Link<T>* temp=it.punt;
            (it.punt->prev)->next=(it.punt)->next;
            (it.punt->next)->prev=(it.punt)->prev;
            it.punt=temp->next;
            temp->next=0;
            temp->prev=0;
            delete temp;
            dimensione--;
        }
    }else{
        return;
    }
}

template<class T>
void Depot<T>::clear(){
    while(!isEmpty()){
        remove_last();
    }
}

template<class T>
bool Depot<T>::search(const T& x) const{
    bool trovato=false;
    Iterator<T> it=begin();
    while(it!=end() && !trovato){
        if(*it==x)
            trovato=true;
        ++it;
    }
    return trovato;
}

template<class T>
ostream& operator<<(ostream& os, const Depot<T>& d){
    for(Iterator<T> it=d.begin(); it!=d.end(); ++it){
        os << d[it] << std::endl;
    }
    return os;
}

//istanziazione esplicita dei template di classe utilizzati
template class Depot<Parcel*>;
template class Iterator<Parcel*>;
