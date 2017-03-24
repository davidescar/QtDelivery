//mainWidget.cpp

#include "mainWidget.h"
#include "table.h"
#include <QLayoutItem>
#include <QPalette>
#include <QFile>
#include <QTextStream>
#include <QSignalMapper>
#include <QDomDocument>
#include <QLCDNumber>
#include <QLabel>
#include "math.h"

MainWidget::MainWidget(QWidget* parent): QWidget(parent),deposito("stock.xml"){
    grid=new QVBoxLayout(this);
    setHome();
    setLayout(grid);
}

int MainWidget::countItem() const{
    return grid->count();
}

void MainWidget::setStyleTextBlock(QTextEdit* t) const{
    QPalette pal=t->palette();
    pal.setColor(QPalette::Base, QColor(167,167,167,230));
    t->setPalette(pal);
    QTextCursor c=t->textCursor();
    c.movePosition(QTextCursor::Start);
    t->setTextCursor(c);
    t->setStyleSheet("QTextEdit{margin-left: 150px; max-width: 800px; font-size: 11pt; color: #000000; border: 1px solid white;}");
}

void MainWidget::setStyleButtonParcel(QPushButton* b, const QString& i) const{
    b->setStyleSheet("background-image: url("+i+"); background-repeat: no-repeat;");
    b->setFlat(true);
    b->setAutoFillBackground(true);
    b->setMaximumHeight(120);
    b->setMaximumWidth(120);
    b->setCursor(Qt::PointingHandCursor);
}

void MainWidget::setInfo(){
    QTextEdit* infoApp=new QTextEdit(this);
    infoApp->setReadOnly(true);
    QFile file(":/info.html");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        infoApp->insertHtml(stream.readAll());
        this->setStyleTextBlock(infoApp);
        grid->addWidget(infoApp);
        file.close();
    }
    setLayout(grid);
}

void MainWidget::messageError() const{
    MessageToUser* error=new MessageToUser(0,"Errore",QMessageBox::Critical,"Impossibile eseguire l'operazione!","Il magazzino non contiene alcun pacco","");
    error->show();
}

void MainWidget::showParcelRemoved(const Parcel* pacco) const{
    MessageToUser* showParcel=new MessageToUser(0,"Operazione completata",QMessageBox::Information,"Il seguente pacco "+trUtf8("è")+" stato rimosso dal magazzino!","Costo: "+QString::number(pacco->shippingCost(),'f',2)+" "+trUtf8("€")+"\nTipologia: "+QString::fromStdString(pacco->typology())+"\nPeso: "+QString::number(pacco->getPeso())+" kg\nDimensioni: "+QString::number(pacco->getDimensione().getAltezza())+" x "+QString::number(pacco->getDimensione().getLarghezza())+" x "+QString::number(pacco->getDimensione().getProfondita())+" cm\nMittente: "+QString::fromStdString(pacco->getEtichetta().getMittente().getNome())+" "+QString::fromStdString(pacco->getEtichetta().getMittente().getCognome())+", "+QString::fromStdString(pacco->getEtichetta().getMittente().getIndirizzo().getVia())+" "+QString::number(pacco->getEtichetta().getMittente().getIndirizzo().getNumeroCivico())+", "+QString::fromStdString(pacco->getEtichetta().getMittente().getIndirizzo().getCAP())+"\nDestinatario: "+QString::fromStdString(pacco->getEtichetta().getDestinatario().getNome())+" "+QString::fromStdString(pacco->getEtichetta().getDestinatario().getCognome())+", "+QString::fromStdString(pacco->getEtichetta().getDestinatario().getIndirizzo().getVia())+" "+QString::number(pacco->getEtichetta().getDestinatario().getIndirizzo().getNumeroCivico())+", "+QString::fromStdString(pacco->getEtichetta().getDestinatario().getIndirizzo().getCAP()),"");
    showParcel->show();
}

void MainWidget::setHome(){
    QLCDNumber* pacchiNazionali=new QLCDNumber(this);
    QLCDNumber* pacchiInternazionali=new QLCDNumber(this);
    int nPN=deposito.contaNational();
    int nPI=deposito.contaInternational();
    pacchiNazionali->setDigitCount(QString("%1").arg(nPN).length());
    pacchiInternazionali->setDigitCount(QString("%1").arg(nPI).length());
    pacchiNazionali->display(nPN);
    pacchiInternazionali->display(nPI);
    pacchiNazionali->setMaximumWidth(100);
    pacchiNazionali->setMaximumHeight(100);
    pacchiInternazionali->setMaximumWidth(100);
    pacchiInternazionali->setMaximumHeight(100);
    pacchiNazionali->setSegmentStyle(QLCDNumber::Flat);
    pacchiInternazionali->setSegmentStyle(QLCDNumber::Flat);
    setStyleSheet("QLCDNumber{color: #C70D00; background-color: rgb(200,200,200);}");
    QLabel* lab_PN=new QLabel("Pacchi Nazionali");
    QLabel* lab_PI=new QLabel("Pacchi Internazionali");
    lab_PN->setStyleSheet("qproperty-alignment: AlignCenter; color: #FFFFFF; background-color: rgba(199,13,0,230); max-height: 60px; max-width: 230px; border: 2px solid #FFFFFF; border-radius: 20px; font-size: 17pt; font-style: italic;");
    lab_PI->setStyleSheet("qproperty-alignment: AlignCenter; color: #FFFFFF; background-color: rgba(199,13,0,230); max-height: 60px; max-width: 230px; border: 2px solid #FFFFFF; border-radius: 20px; font-size: 17pt; font-style: italic;");
    grid->addWidget(lab_PN);
    grid->addWidget(pacchiNazionali);
    grid->addWidget(lab_PI);
    grid->addWidget(pacchiInternazionali);
    setLayout(grid);
}

void MainWidget::chooseParcel(){
    QPushButton* b1=new QPushButton(this);
    this->setStyleButtonParcel(b1,":/images/regular.png");
    QPushButton* b2=new QPushButton(this);
    this->setStyleButtonParcel(b2,":/images/fast.png");
    QPushButton* b3=new QPushButton(this);
    this->setStyleButtonParcel(b3,":/images/international.png");
    grid->addWidget(b1);
    grid->addWidget(b2);
    grid->addWidget(b3);
    setLayout(grid);

    QSignalMapper* signalMapper=new QSignalMapper(this);
    connect(b1,SIGNAL(clicked()),signalMapper,SLOT(map())) ;
    connect(b2,SIGNAL(clicked()),signalMapper,SLOT(map())) ;
    connect(b3,SIGNAL(clicked()),signalMapper,SLOT(map())) ;
    signalMapper->setMapping(b1,"Regular");
    signalMapper->setMapping(b2,"Fast");
    signalMapper->setMapping(b3,"International");
    connect(signalMapper,SIGNAL(mapped(QString)),this,SLOT(newParcel(QString)));
}

void MainWidget::clearWidget(){
    if(countItem()>0){
        QLayoutItem* item;
        while((item=this->layout()->takeAt(0))!=0){
            delete item->widget();
            delete item;
        }
     }
}

void MainWidget::home(){
    this->clearWidget();
    setHome();
}

void MainWidget::showContent(){
    this->clearWidget();
    Table* view=new Table(this,&deposito);
    grid->addWidget(view);
    setLayout(grid);
}

void MainWidget::newParcel(const QString& t){
    MyForm* formPacco=new MyForm(this,t,&deposito);
    formPacco->show();
}

void MainWidget::deleteAllParcels(){
    if(!deposito.vuoto()){
        int nelem=deposito.svuotaTutto();
        //cancello indistintamente tutti i pacchi dal file xml
        QDomDocument doc;
        QFile file("stock.xml");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            if(doc.setContent(&file)){
                QDomElement root=doc.documentElement();
                for(int i=0; i<nelem; i++){
                    QDomNode node=root.firstChild();
                    node.parentNode().removeChild(node);
                }
                file.close();
                if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                    QByteArray xml=doc.toByteArray();
                    file.write(xml);
                    file.close();
                }
            }
        }
        MessageToUser* success=new MessageToUser(this,"Operazione completata",QMessageBox::Information,"Sono stati rimossi con successo "+QString::number(nelem)+" pacchi dal magazzino!","","");
        success->show();
    }else
        messageError();
    this->showContent();
}

void MainWidget::deleteFirstParcel(){
    if(!deposito.vuoto()){
        Parcel* p=deposito.removeFirst();
        //cancello il primo nodo dal file xml
        QDomDocument doc;
        QFile file("stock.xml");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            if(doc.setContent(&file)){
                QDomElement root=doc.documentElement();
                QDomNode node=root.firstChild();
                node.parentNode().removeChild(node);
                file.close();
                if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                    QByteArray xml=doc.toByteArray();
                    file.write(xml);
                    file.close();
                }
            }
        }
        showParcelRemoved(p);
    }else
        messageError();
    this->showContent();
}

void MainWidget::deleteLastParcel(){
    if(!deposito.vuoto()){
        Parcel* p=deposito.removeLast();
        //cancello l'ultimo nodo dal file xml
        QDomDocument doc;
        QFile file("stock.xml");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            if(doc.setContent(&file)){
                QDomElement root=doc.documentElement();
                QDomNode node=root.lastChild();
                node.parentNode().removeChild(node);
                file.close();
                if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                    QByteArray xml=doc.toByteArray();
                    file.write(xml);
                    file.close();
                }
            }
        }
        showParcelRemoved(p);
    }else
        messageError();
    this->showContent();
}

void MainWidget::deleteIndex(int i){
    if(i==0)
        deleteFirstParcel();
    else if(i==deposito.size()-1)
        deleteLastParcel();
    else{ //rimozione pacco nel mezzo della lista
        if(!deposito.vuoto()){
            Parcel* p=deposito.removeInd(i);
            //cancello l'i-esimo nodo dal file xml
            QDomDocument doc;
            QFile file("stock.xml");
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                if(doc.setContent(&file)){
                    QDomElement root=doc.documentElement();
                    QDomNode node=root.firstChild();
                    for(int j=0; j<i; ++j)
                        node=node.nextSibling();
                    node.parentNode().removeChild(node);
                    file.close();
                    if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                        QByteArray xml=doc.toByteArray();
                        file.write(xml);
                        file.close();
                    }
                }
            }
            showParcelRemoved(p);
        }else
            messageError();
        this->showContent();
    }
}

void MainWidget::deleteTypology(const QString& t){
    double costo=0.00;
    int nelem=removeParcelTypology(t,costo);
    if(nelem==0){
        MessageToUser* error=new MessageToUser(this,"Errore",QMessageBox::Critical,"Impossibile eseguire l'operazione!","Il magazzino non contiene pacchi di tipo "+t,"");
        error->show();
    }else{
        MessageToUser* success=new MessageToUser(0,"Operazione completata",QMessageBox::Information,"Pacchi "+t+" mandati in spedizione: "+QString::number(nelem)+"\n\nTotale costi di spedizione: "+QString::number(costo,'f',2)+" "+trUtf8("€"),"","");
        success->show();
    }
    this->showContent();
}

int MainWidget::removeParcelTypology(const QString& type, double& c){
    int n=deposito.removeParcelType(type,c);
    if(n>0){
        QDomDocument doc;
        QFile file("stock.xml");
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            if(doc.setContent(&file)){
                QDomElement root=doc.documentElement();
                QDomNodeList list=root.elementsByTagName(type);
                while(!list.isEmpty()){
                    QDomNode node=list.at(0);
                    node.parentNode().removeChild(node);
                }
                file.close();
                if(file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
                    QByteArray xml=doc.toByteArray();
                    file.write(xml);
                    file.close();
                }
            }
        }
    }
    return n;
}

void MainWidget::searchParcelCostMax(){
    if(!deposito.vuoto()){
        int i=0;
        Parcel* p=deposito.searchCostMax(i);
        MessageToUser* success=new MessageToUser(0,"Ricerca completata",QMessageBox::Information,"Pacco con costo di spedizione maggiore: n."+QString::number(i+1),"Costo di spedizione: "+QString::number(p->shippingCost())+" "+trUtf8("€")+"\nTipologia pacco: "+QString::fromStdString(p->typology()),"");
        success->show();
    }else
        messageError();
    this->showContent();
}

void MainWidget::searchForCategory(const QString& c){
    if(!deposito.vuoto()){
        Stock category;
        deposito.searchCateg(c,category);
        int n=category.size();
        QString s="";
        if(c=="Small")
            s="inferiore a 9000 cm^3";
        if(c=="Medium")
            s="superiore a 9000 cm^3 ed inferiore a 15000 cm^3";
        if(c=="Large")
            s="superiore a 15000 cm^3";
        MessageToUser* success=new MessageToUser(0,"Ricerca completata",QMessageBox::Information,"Pacchi di categoria "+c+" trovati: "+QString::number(n),"Si ricorda che per la categoria "+c+" il pacco deve avere un volume "+s,"");
        success->show();
        clearWidget();
        Table* view=new Table(this,&category);
        grid->addWidget(view);
        setLayout(grid);
    }else{
        messageError();
        this->home();
    }
}
