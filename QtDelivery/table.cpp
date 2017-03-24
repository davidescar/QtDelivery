//table.cpp

#include "table.h"
#include "parcel.h"
#include <QStringList>
#include <QLabel>
#include <QHeaderView>
#include <QHBoxLayout>

Table::Table(QWidget* parent, Stock* v): QTableWidget(parent),val(v){
    setMaximumWidth(1080);
    setRowCount(val->size());
    setColumnCount(6);
    QStringList header=QStringList() << "Peso (kg)" << "Dimensioni (cm)" << "Mittente" << "Destinatario" << "Tipologia" << "Costo ("+trUtf8("€")+")";
    setHorizontalHeaderLabels(header);
    horizontalHeader()->setStyleSheet("QHeaderView::section{ padding: 5px; font-weight: bold; font-size: 12pt; background-color: rgb(185,185,185);}");
    verticalHeader()->setStyleSheet("QHeaderView::section{background-color: rgb(210,210,210);}");
    verticalHeader()->setDefaultSectionSize(50);
    setColumnWidth(0,90);
    setColumnWidth(1,151);
    setColumnWidth(2,290);
    setColumnWidth(3,290);
    setColumnWidth(4,132);
    setColumnWidth(5,107);
    setStyleSheet("QLabel{qproperty-alignment: AlignCenter; border: none; background-color: none; color: #000000; font-style: normal; min-width: 100px; max-width: 300px; font-size: 10pt;}");
    for(int i=0; i<rowCount(); ++i){
        Parcel* pacco=val->getParcel(i); //puntatore all'i-esimo pacco presente nel magazzino
        string tipo=pacco->typology();
        double costo=pacco->shippingCost();
        double p=pacco->getPeso();
        double alt=(pacco->getDimensione()).getAltezza();
        double larg=(pacco->getDimensione()).getLarghezza();
        double prof=(pacco->getDimensione()).getProfondita();
        string nomeMitt=((pacco->getEtichetta()).getMittente()).getNome();
        string cognomeMitt=((pacco->getEtichetta()).getMittente()).getCognome();
        string indMitt=(((pacco->getEtichetta()).getMittente()).getIndirizzo()).getVia();
        int nCivMitt=(((pacco->getEtichetta()).getMittente()).getIndirizzo()).getNumeroCivico();
        string CAPMitt=(((pacco->getEtichetta()).getMittente()).getIndirizzo()).getCAP();
        string nomeDest=((pacco->getEtichetta()).getDestinatario()).getNome();
        string cognomeDest=((pacco->getEtichetta()).getDestinatario()).getCognome();
        string indDest=(((pacco->getEtichetta()).getDestinatario()).getIndirizzo()).getVia();
        int nCivDest=(((pacco->getEtichetta()).getDestinatario()).getIndirizzo()).getNumeroCivico();
        string CAPDest=(((pacco->getEtichetta()).getDestinatario()).getIndirizzo()).getCAP();

        QWidget* w0=new QWidget();
        QHBoxLayout* lay0=new QHBoxLayout(w0);
        lay0->addWidget(new QLabel(QString::number(p)));
        lay0->setAlignment(Qt::AlignCenter);
        lay0->setContentsMargins(0,0,0,0);
        w0->setLayout(lay0);

        QWidget* w1=new QWidget();
        QHBoxLayout* lay1=new QHBoxLayout(w1);
        lay1->addWidget(new QLabel(QString::number(alt)+" x "+QString::number(larg)+" x "+QString::number(prof)));
        lay1->setAlignment(Qt::AlignCenter);
        lay1->setContentsMargins(0,0,0,0);
        w1->setLayout(lay1);

        QWidget* w2=new QWidget();
        QHBoxLayout* lay2=new QHBoxLayout(w2);
        lay2->addWidget(new QLabel(QString::fromStdString(nomeMitt)+" "+QString::fromStdString(cognomeMitt)+", "+QString::fromStdString(indMitt)+" "+QString::number(nCivMitt)+", "+QString::fromStdString(CAPMitt)));
        lay2->setAlignment(Qt::AlignCenter);
        lay2->setContentsMargins(0,0,0,0);
        w2->setLayout(lay2);

        QWidget* w3=new QWidget();
        QHBoxLayout* lay3=new QHBoxLayout(w3);
        lay3->addWidget(new QLabel(QString::fromStdString(nomeDest)+" "+QString::fromStdString(cognomeDest)+", "+QString::fromStdString(indDest)+" "+QString::number(nCivDest)+", "+QString::fromStdString(CAPDest)));
        lay3->setAlignment(Qt::AlignCenter);
        lay3->setContentsMargins(0,0,0,0);
        w3->setLayout(lay3);

        QWidget* w4=new QWidget();
        QHBoxLayout* lay4=new QHBoxLayout(w4);
        lay4->addWidget(new QLabel(QString::fromStdString(tipo)));
        lay4->setAlignment(Qt::AlignCenter);
        lay4->setContentsMargins(0,0,0,0);
        w4->setLayout(lay4);

        QWidget* w5=new QWidget();
        QHBoxLayout* lay5=new QHBoxLayout(w5);
        lay5->addWidget(new QLabel(QString::number(costo,'f',2)));
        lay5->setAlignment(Qt::AlignCenter);
        lay5->setContentsMargins(0,0,0,0);
        w5->setLayout(lay5);

        setCellWidget(i,0,w0);
        setCellWidget(i,1,w1);
        setCellWidget(i,2,w2);
        setCellWidget(i,3,w3);
        setCellWidget(i,4,w4);
        setCellWidget(i,5,w5);
    }
}
