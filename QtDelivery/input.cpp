//input.cpp

#include "input.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

Input::Input(QWidget* parent): QWidget(parent){
    setStyleSheet("QLineEdit{font-size: 11pt; max-width: 400px;} QDoubleSpinBox::up-button,QDoubleSpinBox::down-button {height: 10px; width: 15px;} QSpinBox::up-button,QSpinBox::down-button{height: 10px; width: 15px;} QDoubleSpinBox{border: 1px solid gray; max-width: 80px; height: 30px; font-size: 11pt;} QSpinBox{border:1px solid gray; max-width: 80px; height: 20px; font-size: 11pt;} QGroupBox{margin-bottom: 10px; border: 2px solid #FF4900; border-radius: 5px; color: #D40E00; font-size: 8pt;} QGroupBox::title{border-bottom: 1px solid #FF4900;} QLabel{padding-left: 10px; font-size: 11pt;}");
    QGroupBox* infoPeso=new QGroupBox();
    QHBoxLayout* c0=new QHBoxLayout();
    QLabel* lab0=new QLabel("Peso (kg)");
    peso=new QDoubleSpinBox();
    peso->setAccelerated(true);
    peso->setSingleStep(0.1);
    c0->addWidget(lab0);
    c0->addWidget(peso);
    infoPeso->setLayout(c0);

    QGroupBox* dimensioni=new QGroupBox(tr("Dimensioni"));
    QHBoxLayout* c1=new QHBoxLayout();
    QLabel* lab1=new QLabel("Altezza (cm)");
    alt=new QDoubleSpinBox();
    alt->setAccelerated(true);
    alt->setSingleStep(0.1);
    c1->addWidget(lab1);
    c1->addWidget(alt);

    QHBoxLayout* c2=new QHBoxLayout();
    QLabel* lab2=new QLabel("Larghezza (cm)");
    larg=new QDoubleSpinBox();
    larg->setAccelerated(true);
    larg->setSingleStep(0.1);
    c2->addWidget(lab2);
    c2->addWidget(larg);

    QHBoxLayout* c3=new QHBoxLayout();
    QLabel* lab3=new QLabel("Profondit"+trUtf8("à")+" (cm)");
    prof=new QDoubleSpinBox();
    prof->setAccelerated(true);
    prof->setSingleStep(0.1);
    c3->addWidget(lab3);
    c3->addWidget(prof);

    QVBoxLayout* infoDim=new QVBoxLayout();
    infoDim->addLayout(c1);
    infoDim->addLayout(c2);
    infoDim->addLayout(c3);

    dimensioni->setLayout(infoDim);

    QGroupBox* mittente=new QGroupBox(tr("Mittente"));
    QHBoxLayout* c4=new QHBoxLayout();
    QLabel* lab4=new QLabel("Nome");
    nomeMitt=new QLineEdit();
    c4->addWidget(lab4);
    c4->addWidget(nomeMitt);

    QHBoxLayout* c5=new QHBoxLayout();
    QLabel* lab5=new QLabel("Cognome");
    cognomeMitt=new QLineEdit();
    c5->addWidget(lab5);
    c5->addWidget(cognomeMitt);

    QHBoxLayout* c6=new QHBoxLayout();
    QLabel* lab6=new QLabel("Indirizzo");
    indirizzoMitt=new QLineEdit();
    indirizzoMitt->setPlaceholderText("es: via Roma");
    nCivMitt=new QSpinBox();
    CAPMitt=new QLineEdit();
    CAPMitt->setPlaceholderText("es: 35100");
    c6->addWidget(lab6);
    c6->addWidget(indirizzoMitt);
    c6->addWidget(nCivMitt);
    c6->addWidget(CAPMitt);

    QVBoxLayout* infoMittente=new QVBoxLayout();
    infoMittente->addLayout(c4);
    infoMittente->addLayout(c5);
    infoMittente->addLayout(c6);

    mittente->setLayout(infoMittente);

    QGroupBox* destinatario=new QGroupBox(tr("Destinatario"));
    QHBoxLayout* c7=new QHBoxLayout();
    QLabel* lab7=new QLabel("Nome");
    nomeDest=new QLineEdit();
    c7->addWidget(lab7);
    c7->addWidget(nomeDest);

    QHBoxLayout* c8=new QHBoxLayout();
    QLabel* lab8=new QLabel("Cognome");
    cognomeDest=new QLineEdit();
    c8->addWidget(lab8);
    c8->addWidget(cognomeDest);

    QHBoxLayout* c9=new QHBoxLayout();
    QLabel* lab9=new QLabel("Indirizzo");
    indirizzoDest=new QLineEdit();
    indirizzoDest->setPlaceholderText("es: piazza Napoli");
    nCivDest=new QSpinBox();
    CAPDest=new QLineEdit();
    CAPDest->setPlaceholderText("es: 38582");
    c9->addWidget(lab9);
    c9->addWidget(indirizzoDest);
    c9->addWidget(nCivDest);
    c9->addWidget(CAPDest);

    QVBoxLayout* infoDestinatario=new QVBoxLayout();
    infoDestinatario->addLayout(c7);
    infoDestinatario->addLayout(c8);
    infoDestinatario->addLayout(c9);

    destinatario->setLayout(infoDestinatario);

    QVBoxLayout* form=new QVBoxLayout();
    form->addWidget(infoPeso);
    form->addWidget(dimensioni);
    form->addWidget(mittente);
    form->addWidget(destinatario);
    setLayout(form);
}

double Input::getPeso() const{
    return peso->value();
}

double Input::getAlt() const{
    return alt->value();
}

double Input::getLarg() const{
    return larg->value();
}

double Input::getProf() const{
    return prof->value();
}

QString Input::getNomeMitt() const{
    return nomeMitt->text();
}

QString Input::getCognomeMitt() const{
    return cognomeMitt->text();
}

QString Input::getIndirizzoMitt() const{
    return indirizzoMitt->text();
}

int Input::getNCivMitt() const{
    return nCivMitt->value();
}

QString Input::getCAPMitt() const{
    return CAPMitt->text();
}

QString Input::getNomeDest() const{
    return nomeDest->text();
}

QString Input::getCognomeDest() const{
    return cognomeDest->text();
}

QString Input::getIndirizzoDest() const{
    return indirizzoDest->text();
}

int Input::getNCivDest() const{
    return nCivDest->value();
}

QString Input::getCAPDest() const{
    return CAPDest->text();
}

bool Input::isZero(double x) const{
    return x==0.00;
}

bool Input::isValidNominativo(const QString& s) const{
    QRegExp re("[a-zA-Z]+");
    if(re.exactMatch(s))
       return true;
    return false;
}

bool Input::isValidIndirizzo(const QString& s) const{
    QString firstWord=s.split(" ").at(0);
    if(firstWord=="via" || firstWord=="piazza")
        return isValidNominativo(s.split(" ").at(1));
    return false;
}

bool Input::isValidCAP(const QString& s) const{
    QRegExp re("\\d{5}");
    if(re.exactMatch(s))
       return true;
    return false;
}
