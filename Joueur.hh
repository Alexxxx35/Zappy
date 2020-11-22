#ifndef JOUEUR_H
#define JOUEUR_H
#include "Orientation.hh"
#include <algorithm>
#include <string>
#include "Action.hh"
#include<bits/stdc++.h>

class Joueur {
    private:
    static int nextID;
    int _energie;
    int _pdvie;
    int _pdvictoire;
    Orientation _orientation;
    int _id;
    std::queue<Action> _actions;
    int _energieConsumed;

    

    public :
    Joueur();
    ~Joueur();
    
    int GetId();
    int GetEnergie();
    int GetVie();
    int GetVictoire();
    Orientation GetOrientation();
    std::string GetOrientationStr();
    std::queue<Action> GetQueue();
    void ResetTour();
    void AugmenterPointDeVie();
    void AugmenterPointDeVictoire();
    void ReduirePointDeVie();
    void TurnLeft();
    void TurnRight();
    void QueueRandomAction();
    void QueueRandomActions();
    void ConsumeEnergie(int);
    
};

#endif