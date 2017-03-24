//mainWindow.cpp

#include "mainWindow.h"
#include "mainWidget.h"
#include <QMenuBar>
#include <QIcon>
#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QComboBox>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent){
    setGeometry(180,80,1100,700);
    setWindowTitle(tr("QtDelivery"));
    setWindowIcon(QIcon(":/images/logo.png"));

    widget=new MainWidget(this);

    home=new QAction(QIcon(":/images/home.png"),tr("Home"),this);
    creaPacco=new QAction(QIcon(":/images/new.png"),tr("Nuovo pacco"),this);
    visualizza=new QAction(QIcon(":/images/box.png"),tr("Contenuto deposito"),this);
    svuota=new QAction(QIcon(":/images/clear.png"),tr("Svuota deposito"),this);
    cercaCostoso=new QAction(QIcon(":/images/euro.png"),tr("Costo spedizione maggiore"),this);
    cercaCategoria=new QAction(QIcon(":/images/size.png"),tr("Per categoria"),this);
    spedisciPrimo=new QAction(QIcon(":/images/first.png"),tr("Primo pacco"),this);
    spedisciUltimo=new QAction(QIcon(":/images/last.png"),tr("Ultimo pacco"),this);
    spedisciIndice=new QAction(QIcon(":/images/number.png"),tr("Per indice"),this);
    spedisciTipologia=new QAction(QIcon(":/images/send.png"),tr("Per tipologia"),this);

    info=new QAction(QIcon(":/images/info.png"),tr("Informazioni"),this);
    chiudi=new QAction(QIcon(":/images/quit.png"),tr("Esci"),this);
    chiudi->setShortcuts(QKeySequence::Quit);

    paccoMenu=new QMenu(tr("Pacco"),this);
    paccoMenu->addAction(creaPacco);

    spedisciMenu=new QMenu(tr("Spedisci"),this);
    spedisciMenu->addAction(spedisciPrimo);
    spedisciMenu->addAction(spedisciUltimo);
    spedisciMenu->addAction(spedisciIndice);
    spedisciMenu->addAction(spedisciTipologia);

    cercaMenu=new QMenu(tr("Cerca"),this);
    cercaMenu->addAction(cercaCostoso);
    cercaMenu->addAction(cercaCategoria);

    magazzinoMenu=new QMenu(tr("Magazzino"),this);
    magazzinoMenu->addAction(visualizza);
    magazzinoMenu->addMenu(spedisciMenu);
    magazzinoMenu->addMenu(cercaMenu);
    magazzinoMenu->addAction(svuota);

    infoMenu=new QMenu(tr("Help"),this);
    infoMenu->addAction(info);
    infoMenu->addAction(chiudi);

    menuBar()->addAction(home);
    menuBar()->addMenu(paccoMenu);
    menuBar()->addMenu(magazzinoMenu);
    menuBar()->addMenu(infoMenu);
    menuBar()->addSeparator();
    menuBar()->setStyleSheet("font-family: Helvetica; font-size: 18pt; border: 1px solid gray; background: qlineargradient(x1:0 y1:0, x2:1 y2:0, stop:0 yellow, stop:1 red);");

    menuBar()->setCursor(Qt::PointingHandCursor);

    setStyleSheet("QMenuBar::item:selected{background: #DBDBDB; color: #C70D00;} QMenu{ font-size: 13pt;} MainWindow {border-image: url(:/images/background.jpeg) 0 0 0 0 stretch stretch;}");
    setCentralWidget(widget);

    connect(home,SIGNAL(triggered()),this,SLOT(goHome()));
    connect(chiudi,SIGNAL(triggered()),this,SLOT(close()));
    connect(info,SIGNAL(triggered()),this,SLOT(showInfo()));
    connect(creaPacco,SIGNAL(triggered()),this,SLOT(newParcel()));
    connect(visualizza,SIGNAL(triggered()),this,SLOT(viewStock()));
    connect(svuota,SIGNAL(triggered()),this,SLOT(clearDepot()));
    connect(cercaCostoso,SIGNAL(triggered()),this,SLOT(searchExpensive()));
    connect(cercaCategoria,SIGNAL(triggered()),this,SLOT(chooseCategory()));
    connect(spedisciPrimo,SIGNAL(triggered()),this,SLOT(removeFirst()));
    connect(spedisciUltimo,SIGNAL(triggered()),this,SLOT(removeLast()));
    connect(spedisciIndice,SIGNAL(triggered()),this,SLOT(selectIndex()));
    connect(spedisciTipologia,SIGNAL(triggered()),this,SLOT(selectType()));
}

void MainWindow::goHome(){
    widget->clearWidget();
    widget->home();
}

void MainWindow::showInfo(){
    widget->clearWidget();
    widget->setInfo();
}

void MainWindow::newParcel(){
    widget->clearWidget();
    widget->chooseParcel();
}

void MainWindow::viewStock(){
    widget->showContent();
}

void MainWindow::clearDepot(){
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"Svuota magazzino","Sei sicuro di voler procedere alla rimozione di tutti i pacchi attualmente presenti nel deposito?",QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes){
        widget->deleteAllParcels();
    }
}

void MainWindow::removeFirst(){
    widget->deleteFirstParcel();
}

void MainWindow::removeLast(){
    widget->deleteLastParcel();
}

void MainWindow::selectIndex(){
    widget->clearWidget();
    this->viewStock();
    bool ok;
    int i=QInputDialog::getInt(this,tr("Spedisci per indice"),tr("Selezionare l'indice del pacco che si vuole spedire:"),1,0,widget->deposito.size(),1,&ok);
    if(ok)
        removeIndex(i-1);
}

void MainWindow::selectType(){
    widget->clearWidget();
    this->viewStock();
    QInputDialog* quest=new QInputDialog(this,Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    quest->setModal(true);
    quest->setWindowTitle("Spedisci per tipologia");
    QStringList type=QStringList() << "Regular" << "Fast" << "International";
    quest->setComboBoxItems(type);
    quest->setStyleSheet("font-size: 10pt;");
    quest->setLabelText("Selezionare la tipologia di pacchi:");
    quest->setCancelButtonText("Annulla");
    connect(quest,SIGNAL(textValueSelected(const QString&)),this,SLOT(removeType(const QString&)));
    quest->exec();
}

void MainWindow::removeType(const QString& t){
    widget->clearWidget();
    widget->deleteTypology(t);
}

void MainWindow::removeIndex(int i){
    widget->clearWidget();
    widget->deleteIndex(i);
}

void MainWindow::searchExpensive(){
    widget->clearWidget();
    widget->searchParcelCostMax();
}

void MainWindow::chooseCategory(){
    widget->clearWidget();
    this->viewStock();
    QInputDialog* quest=new QInputDialog(this,Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    quest->setModal(true);
    quest->setWindowTitle("Ricerca per categoria");
    QStringList type=QStringList() << "Small" << "Medium" << "Large";
    quest->setComboBoxItems(type);
    quest->setStyleSheet("font-size: 10pt;");
    quest->setLabelText("Selezionare la categoria di pacchi:");
    quest->setCancelButtonText("Annulla");
    connect(quest,SIGNAL(textValueSelected(const QString&)),this,SLOT(searchCategory(const QString&)));
    quest->exec();
}

void MainWindow::searchCategory(const QString& c){
    widget->clearWidget();
    widget->searchForCategory(c);
}
