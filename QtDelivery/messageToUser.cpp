//messageToUser.cpp

#include "messageToUser.h"
#include <QIcon>

MessageToUser::MessageToUser(QWidget* parent, const QString& title, const Icon& icon, const QString& description, const QString& info, const QString& hint): QMessageBox(parent){
    setModal(true);
    setWindowTitle(title);
    setWindowIcon(QIcon(":/images/logo.png"));
    setIcon(icon);
    setText(description);
    setInformativeText(info);
    if(!hint.isEmpty())
        setDetailedText(hint);
    setStyleSheet("QMessageBox > QLabel{background-color: none; color: #000000; font-style: normal; font-size: 10pt;}");
}
