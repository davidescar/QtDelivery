/*
input.h
La classe Input rappresenta i valori inseriti dall'utente nel MyForm.
*/

#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>

class Input: public QWidget
{Q_OBJECT
private:
    QDoubleSpinBox* peso;
    QDoubleSpinBox* alt;
    QDoubleSpinBox* larg;
    QDoubleSpinBox* prof;
    QLineEdit* nomeMitt;
    QLineEdit* cognomeMitt;
    QLineEdit* indirizzoMitt;
    QSpinBox* nCivMitt;
    QLineEdit* CAPMitt;
    QLineEdit* nomeDest;
    QLineEdit* cognomeDest;
    QLineEdit* indirizzoDest;
    QSpinBox* nCivDest;
    QLineEdit* CAPDest;
public:
     Input(QWidget* =0);
     double getPeso() const;
     double getAlt() const;
     double getLarg() const;
     double getProf() const;
     QString getNomeMitt() const;
     QString getCognomeMitt() const;
     QString getIndirizzoMitt() const;
     int getNCivMitt() const;
     QString getCAPMitt() const;
     QString getNomeDest() const;
     QString getCognomeDest() const;
     QString getIndirizzoDest() const;
     int getNCivDest() const;
     QString getCAPDest() const;
     bool isZero(double) const;
     bool isValidNominativo(const QString&) const;
     bool isValidIndirizzo(const QString&) const;
     bool isValidCAP(const QString&) const;
};

#endif // INPUT_H
