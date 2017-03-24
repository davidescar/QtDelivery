/*
measures.h
La classe Measures rappresenta le informazioni relative alle dimensioni
tridimensionali di un generico oggetto (altezza, larghezza, profondità).
N.B.: le misure sono espresse in cm nella forma
    altezza x larghezza x profondita
*/

#ifndef MEASURES_H
#define MEASURES_H

#include <iostream>
using std::ostream;

class Measures{
    private:
        double altezza;
        double larghezza;
        double profondita;
    public:
        Measures(double =0.0, double=0.0, double =0.0);
        double getAltezza() const;
        double getLarghezza() const;
        double getProfondita() const;
        void setAltezza(double);
        void setLarghezza(double);
        void setProfondita(double);
        bool operator==(const Measures&) const;
        bool operator!=(const Measures&) const;
        bool operator>(const Measures&) const;
        bool operator>=(const Measures&) const;
        bool operator<(const Measures&) const;
        bool operator<=(const Measures&) const;
        double volume() const;
};

ostream& operator<<(ostream&, const Measures&);

#endif // MEASURES_H
