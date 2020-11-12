#ifndef JOUEUR_H
#define JOUEUR_H
#include "Orientation.hh"
#include <algorithm>
#include <string>

class Joueur {
    private:
    static int nextID;
    int _energie;
    int _pdvie;
    int _pdvictoire;
    Orientation _orientation;

    public :
    Joueur();
    ~Joueur();
    int id;
    int GetEnergie();
    int GetVie();
    int GetVictoire();
    Orientation GetOrientation();

    void ResetEnergie();
    void AugmenterPointDeVie();
    void AugmenterPointDeVictoire();
    void ReduirePointDeVie();
    
};

#endif