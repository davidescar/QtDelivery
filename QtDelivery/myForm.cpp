//myForm.cpp

#include "myForm.h"
#include <QLabel>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFile>
#include <QDomDocument>

MyForm::MyForm(QWidget* parent, const QString& type, Stock* v): QDialog(parent,Qt::WindowTitleHint | Qt::WindowCloseButtonHint),tipo(type),valori(v){
    setGeometry(500,200,600,500);
    setWindowTitle("Pacco "+type);
    setModal(true);

    ok=new QPushButton("OK");
    annulla=new QPushButton("Annulla");
    connect(ok,SIGNAL(clicked()),this,SLOT(checkDatiForm()));
    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));

    datiForm=new Input();

    QDialogButtonBox* buttons=new QDialogButtonBox(Qt::Horizontal);
    buttons->addButton(ok,QDialogButtonBox::ActionRole);
    buttons->addButton(annulla,QDialogButtonBox::ActionRole);
    buttons->setStyleSheet("font-size: 10pt;");

    QVBoxLayout* container=new QVBoxLayout();
    container->addWidget(datiForm);
    container->addWidget(buttons);
    setLayout(container);
}

bool MyForm::isValidMeasure(double a, double l, double p) const{
    if(!datiForm->isZero(a) && !datiForm->isZero(l) && !datiForm->isZero(p))
        return true;
    return false;
}

bool MyForm::isValidEntity(const QString& nM, const QString& cM, const QString& iM, int ncm, const QString& CAPm) const{
    if(datiForm->isValidNominativo(nM) && datiForm->isValidNominativo(cM) &&
       datiForm->isValidIndirizzo(iM) && !datiForm->isZero(ncm) &&
       datiForm->isValidCAP(CAPm))
        return true;
    return false;
}

void MyForm::checkDatiForm(){
    //controllo la consistenza dei dati inseriti nel form dall'utente
    QString message="Sono stati trovati i seguenti errori: \n\n";
    int i=1;
    if(datiForm->isZero(datiForm->getPeso())){
        message+=QString::number(i)+") Peso non valido!\n";
        i++;
    }
    if(!isValidMeasure(datiForm->getAlt(),datiForm->getLarg(),datiForm->getProf())){
        message+=QString::number(i)+") Dimensioni non valide!\n";
        i++;
    }
    if(!isValidEntity(datiForm->getNomeMitt(),datiForm->getCognomeMitt(),datiForm->getIndirizzoMitt(),datiForm->getNCivMitt(),datiForm->getCAPMitt())){
        message+=QString::number(i)+") Mittente non valido!\n";
        i++;
    }
    if(!isValidEntity(datiForm->getNomeDest(),datiForm->getCognomeDest(),datiForm->getIndirizzoDest(),datiForm->getNCivDest(),datiForm->getCAPDest())){
        message+=QString::number(i)+") Destinatario non valido!\n";
        i++;
    }
    if(i>1){
        QString description="Impossibile effettuare la registrazione del pacco!";
        QString details="Suggerimenti:\na) il peso e le dimensioni del pacco non possono essere 0.00\nb) nome e cognome possono contenere solo caratteri alfabetici\nc) per l'indirizzo occorre specificare 'via' o 'piazza'\nd) il numero civico non pu"+trUtf8("ó")+" essere 0\ne) il CAP deve essere composto di 5 cifre";
        MessageToUser* error=new MessageToUser(this,"Errore",QMessageBox::Critical,description,message,details);
        error->show();
    }else{
        Parcel* pacco;
        if(tipo=="Regular"){
            pacco=new RegularNP(datiForm->getPeso(),Measures(datiForm->getAlt(),datiForm->getLarg(),datiForm->getProf()),ShippingLabel(Entity((datiForm->getNomeMitt()).toStdString(),(datiForm->getCognomeMitt()).toStdString(),Address((datiForm->getIndirizzoMitt()).toStdString(),datiForm->getNCivMitt(),(datiForm->getCAPMitt()).toStdString())),Entity((datiForm->getNomeDest()).toStdString(),(datiForm->getCognomeDest()).toStdString(),Address((datiForm->getIndirizzoDest()).toStdString(),datiForm->getNCivDest(),(datiForm->getCAPDest()).toStdString()))));
        }
        if(tipo=="Fast"){
            pacco=new FastNP(datiForm->getPeso(),Measures(datiForm->getAlt(),datiForm->getLarg(),datiForm->getProf()),ShippingLabel(Entity((datiForm->getNomeMitt()).toStdString(),(datiForm->getCognomeMitt()).toStdString(),Address((datiForm->getIndirizzoMitt()).toStdString(),datiForm->getNCivMitt(),(datiForm->getCAPMitt()).toStdString())),Entity((datiForm->getNomeDest()).toStdString(),(datiForm->getCognomeDest()).toStdString(),Address((datiForm->getIndirizzoDest()).toStdString(),datiForm->getNCivDest(),(datiForm->getCAPDest()).toStdString()))));
        }
        if(tipo=="International"){
            pacco=new InternationalParcel(datiForm->getPeso(),Measures(datiForm->getAlt(),datiForm->getLarg(),datiForm->getProf()),ShippingLabel(Entity((datiForm->getNomeMitt()).toStdString(),(datiForm->getCognomeMitt()).toStdString(),Address((datiForm->getIndirizzoMitt()).toStdString(),datiForm->getNCivMitt(),(datiForm->getCAPMitt()).toStdString())),Entity((datiForm->getNomeDest()).toStdString(),(datiForm->getCognomeDest()).toStdString(),Address((datiForm->getIndirizzoDest()).toStdString(),datiForm->getNCivDest(),(datiForm->getCAPDest()).toStdString()))));
        }
        valori->aggiungi(*pacco);
        this->close();

        //scrittura su file xml del nuovo pacco inserito
        QDomDocument doc;
        QFile file("stock.xml");
        if(file.open(QIODevice::ReadWrite)){
            if(doc.setContent(&file)){
                QDomElement root=doc.documentElement();
                QDomElement nodo=doc.createElement(tipo);

                QDomElement tag_peso=doc.createElement("Peso");
                QDomText text_peso=doc.createTextNode(QString::number(datiForm->getPeso()));
                tag_peso.appendChild(text_peso);

                QDomElement tag_alt=doc.createElement("Altezza");
                QDomText text_alt=doc.createTextNode(QString::number(datiForm->getAlt()));
                tag_alt.appendChild(text_alt);

                QDomElement tag_larg=doc.createElement("Larghezza");
                QDomText text_larg=doc.createTextNode(QString::number(datiForm->getLarg()));
                tag_larg.appendChild(text_larg);

                QDomElement tag_prof=doc.createElement("Profondita");
                QDomText text_prof=doc.createTextNode(QString::number(datiForm->getProf()));
                tag_prof.appendChild(text_prof);

                QDomElement tag_nomeMitt=doc.createElement("nomeMittente");
                QDomText text_nomeMitt=doc.createTextNode(datiForm->getNomeMitt());
                tag_nomeMitt.appendChild(text_nomeMitt);

                QDomElement tag_cognomeMitt=doc.createElement("cognomeMittente");
                QDomText text_cognomeMitt=doc.createTextNode(datiForm->getCognomeMitt());
                tag_cognomeMitt.appendChild(text_cognomeMitt);

                QDomElement tag_indMitt=doc.createElement("indirizzoMittente");
                QDomText text_indMitt=doc.createTextNode(datiForm->getIndirizzoMitt());
                tag_indMitt.appendChild(text_indMitt);

                QDomElement tag_nCivMitt=doc.createElement("nCivMittente");
                QDomText text_nCivMitt=doc.createTextNode(QString::number(datiForm->getNCivMitt()));
                tag_nCivMitt.appendChild(text_nCivMitt);

                QDomElement tag_CAPMitt=doc.createElement("CAPMittente");
                QDomText text_CAPMitt=doc.createTextNode(datiForm->getCAPMitt());
                tag_CAPMitt.appendChild(text_CAPMitt);

                QDomElement tag_nomeDest=doc.createElement("nomeDestinatario");
                QDomText text_nomeDest=doc.createTextNode(datiForm->getNomeDest());
                tag_nomeDest.appendChild(text_nomeDest);

                QDomElement tag_cognomeDest=doc.createElement("cognomeDestinatario");
                QDomText text_cognomeDest=doc.createTextNode(datiForm->getCognomeDest());
                tag_cognomeDest.appendChild(text_cognomeDest);

                QDomElement tag_indDest=doc.createElement("indirizzoDestinatario");
                QDomText text_indDest=doc.createTextNode(datiForm->getIndirizzoDest());
                tag_indDest.appendChild(text_indDest);

                QDomElement tag_nCivDest=doc.createElement("nCivDestinatario");
                QDomText text_nCivDest=doc.createTextNode(QString::number(datiForm->getNCivDest()));
                tag_nCivDest.appendChild(text_nCivDest);

                QDomElement tag_CAPDest=doc.createElement("CAPDestinatario");
                QDomText text_CAPDest=doc.createTextNode(datiForm->getCAPDest());
                tag_CAPDest.appendChild(text_CAPDest);

                nodo.appendChild(tag_peso);
                nodo.appendChild(tag_alt);
                nodo.appendChild(tag_larg);
                nodo.appendChild(tag_prof);
                nodo.appendChild(tag_nomeMitt);
                nodo.appendChild(tag_cognomeMitt);
                nodo.appendChild(tag_indMitt);
                nodo.appendChild(tag_nCivMitt);
                nodo.appendChild(tag_CAPMitt);
                nodo.appendChild(tag_nomeDest);
                nodo.appendChild(tag_cognomeDest);
                nodo.appendChild(tag_indDest);
                nodo.appendChild(tag_nCivDest);
                nodo.appendChild(tag_CAPDest);
                root.appendChild(nodo);
                file.close();
                if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                    QByteArray xml=doc.toByteArray();
                    file.write(xml);
                    file.close();
                    MessageToUser* success=new MessageToUser(this,"Congratulazioni",QMessageBox::Information,"Il pacco "+trUtf8("è")+" stato aggiunto con successo!","","");
                    success->show();
                }
            }
        }else{
            MessageToUser* error=new MessageToUser(this,"Errore",QMessageBox::Critical,"Operazione di scrittura su file XML fallita!","","");
            error->show();
        }
    }
}
