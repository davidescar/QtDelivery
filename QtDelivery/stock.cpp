//stock.cpp

#include "stock.h"
#include <QFile>
#include <QDomDocument>

Stock::Stock(): magazzino(){}

Stock::Stock(const QString& nomeFile): magazzino(){
    QFile file(nomeFile);
    QDomDocument doc;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        doc.setContent(&file);
        file.close();
        QDomElement root=doc.documentElement(); //nodo radice "Magazzino"
        QDomNodeList list=root.childNodes();
        if(list.length()>0){
            QDomElement component=root.firstChild().toElement(); //primo nodo
            string tipo="";
            while(!component.isNull()){
                if(component.tagName()=="Regular"){
                    tipo="Regular";
                }if(component.tagName()=="Fast"){
                    tipo="Fast";
                }if(component.tagName()=="International"){
                    tipo="International";
                }
                QDomElement child=component.firstChild().toElement();
                double peso=0.0;
                double altezza=0.0;
                double larghezza=0.0;
                double profondita=0.0;
                string nomeMitt="";
                string cognomeMitt="";
                string indirizzoMitt="";
                int nCivMitt=0;
                string CAPMitt="";
                string nomeDest="";
                string cognomeDest="";
                string indirizzoDest="";
                int nCivDest=0;
                string CAPDest="";
                while(!child.isNull()){
                    if(child.tagName()=="Peso")
                        peso=child.firstChild().toText().data().toDouble();
                    if(child.tagName()=="Altezza")
                        altezza=child.firstChild().toText().data().toDouble();
                    if(child.tagName()=="Larghezza")
                        larghezza=child.firstChild().toText().data().toDouble();
                    if(child.tagName()=="Profondita")
                        profondita=child.firstChild().toText().data().toDouble();
                    if(child.tagName()=="nomeMittente")
                        nomeMitt=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="cognomeMittente")
                        cognomeMitt=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="indirizzoMittente")
                        indirizzoMitt=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="nCivMittente")
                        nCivMitt=child.firstChild().toText().data().toInt();
                    if(child.tagName()=="CAPMittente")
                        CAPMitt=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="nomeDestinatario")
                        nomeDest=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="cognomeDestinatario")
                        cognomeDest=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="indirizzoDestinatario")
                        indirizzoDest=child.firstChild().toText().data().toStdString();
                    if(child.tagName()=="nCivDestinatario")
                        nCivDest=child.firstChild().toText().data().toInt();
                    if(child.tagName()=="CAPDestinatario")
                        CAPDest=child.firstChild().toText().data().toStdString();
                    child=child.nextSibling().toElement();
                }
                Parcel* pacco;
                if(tipo=="Regular"){
                    pacco=new RegularNP(peso,Measures(altezza,larghezza,profondita),ShippingLabel(Entity(nomeMitt,cognomeMitt,Address(indirizzoMitt,nCivMitt,CAPMitt)),Entity(nomeDest,cognomeDest,Address(indirizzoDest,nCivDest,CAPDest))));
                }
                if(tipo=="Fast"){
                    pacco=new FastNP(peso,Measures(altezza,larghezza,profondita),ShippingLabel(Entity(nomeMitt,cognomeMitt,Address(indirizzoMitt,nCivMitt,CAPMitt)),Entity(nomeDest,cognomeDest,Address(indirizzoDest,nCivDest,CAPDest))));
                }
                if(tipo=="International"){
                    pacco=new InternationalParcel(peso,Measures(altezza,larghezza,profondita),ShippingLabel(Entity(nomeMitt,cognomeMitt,Address(indirizzoMitt,nCivMitt,CAPMitt)),Entity(nomeDest,cognomeDest,Address(indirizzoDest,nCivDest,CAPDest))));
                }
                this->aggiungi(*pacco);
                component=component.nextSibling().toElement();
            }
        }
    }
}

void Stock::aggiungi(const Parcel& p){
    Parcel* pp=const_cast<Parcel*>(&p);
    magazzino.push_back(pp);
}

Parcel* Stock::getParcel(int i) const{
    if(i<(int)magazzino.size()){
        Iterator<Parcel*> it=magazzino.begin();
        for(int j=0; j<i; ++j){
            ++it;
        }
        return magazzino[it];
    }else{
        return 0;
    }
}

int Stock::size() const{
    return magazzino.size();
}

bool Stock::vuoto() const{
    return magazzino.isEmpty();
}

int Stock::svuotaTutto(){
    int n=magazzino.size();
    magazzino.clear();
    return n;
}

Parcel* Stock::removeFirst(){
    return magazzino.pop_front();
}

Parcel* Stock::removeLast(){
    return magazzino.pop_back();
}

int Stock::contaNational() const{
    int n=0;
    if(!magazzino.isEmpty()){
        Iterator<Parcel*> it=magazzino.begin();
        while(it!=magazzino.end()){
            if(dynamic_cast<NationalParcel*>(*it))
                n++;
            ++it;
        }
    }
    return n;
}

int Stock::contaInternational() const{
    int n=0;
    if(!magazzino.isEmpty()){
        Iterator<Parcel*> it=magazzino.begin();
        while(it!=magazzino.end()){
            if(dynamic_cast<InternationalParcel*>(*it))
                n++;
            ++it;
        }
    }
    return n;
}

int Stock::removeParcelType(const QString& t, double& tot){
    int n=0;
    Iterator<Parcel*> it=magazzino.begin();
    while(magazzino.size()>0 && it!=magazzino.end()){
        if(dynamic_cast<RegularNP*>(*it) && t=="Regular"){
            tot+=(*it)->shippingCost();
            magazzino.erase(it);
            n++;
        }
        else if(dynamic_cast<FastNP*>(*it) && t=="Fast"){
            tot+=(*it)->shippingCost();
            magazzino.erase(it);
            n++;
        }
        else if(dynamic_cast<InternationalParcel*>(*it) && t=="International"){
            tot+=(*it)->shippingCost();
            magazzino.erase(it);
            n++;
        }
        else
            ++it;
    }
    return n;
}

Parcel* Stock::searchCostMax(int& ind) const{
    Iterator<Parcel*> it=magazzino.begin();
    Parcel* p=*it;
    ++it;
    while(it!=magazzino.end()){
        if((*it)->shippingCost()>p->shippingCost()){
            p=*it;
        }
        ++it;
        ++ind;
    }
    return p;
}

void Stock::searchCateg(const QString& cat, Stock& mag) const{
    Iterator<Parcel*> it=magazzino.begin();
    while(it!=magazzino.end()){
        if((*it)->categoryParcel()==cat.toStdString()){
            mag.aggiungi(**it);
        }
        ++it;
    }
}

Parcel* Stock::removeInd(int i){
    Parcel* p=getParcel(i);
    magazzino.remove(p);
    return p;
}
