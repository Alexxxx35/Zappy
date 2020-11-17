#ifndef JOUEUR_H
#define JOUEUR_H
#include "Orientation.hh"
#include <algorithm>
#include <string>
#include "Action.hh"

class Joueur {
    private:
    static int nextID;
    int _energie;
    int _pdvie;
    int _pdvictoire;
    Orientation _orientation;
    int _id;
    std::vector<Action> _actions;

    public :
    Joueur();
    ~Joueur();
    
    int GetId();
    int GetEnergie();
    int GetVie();
    int GetVictoire();
    Orientation GetOrientation();

    void ResetEnergie();
    void AugmenterPointDeVie();
    void AugmenterPointDeVictoire();
    void ReduirePointDeVie();
    void TAMERE (); // fonction pour tester des trucs
    
};

#endif