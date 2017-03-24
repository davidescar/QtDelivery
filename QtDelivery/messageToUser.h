/*
messageToUser.h
La classe MessageToUser serve per la gestione di tutti i
messaggi (errore e successo) diretti all'utente dell'applicazione.
*/

#ifndef MESSAGETOUSER_H
#define MESSAGETOUSER_H

#include <QMessageBox>
#include <QString>

class MessageToUser: public QMessageBox
{Q_OBJECT
    public:
        MessageToUser(QWidget* parent=0, const QString& title="", const Icon& icon=QMessageBox::NoIcon, const QString& description="", const QString& info="", const QString& hint="");
};

#endif // MESSAGETOUSER_H
