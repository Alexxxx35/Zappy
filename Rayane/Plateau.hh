#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include <map>
#include <string>
#include "Joueur.hh"
#include "Pierre.hh"



class Plateau{
    public:
    Plateau(); // constructor with default 5:5 size
    Plateau(int,int); // constructor with defined size
    ~Plateau();
    void ClearPlateau();
    void DisplayPlateau();
    private:
    const int _WIDTH;
    const int _HEIGHT;
    char **_plateau;
    

    std::map<int,Joueur&> id_players;
    std::map<int,Joueur&> pos_players;
    std::map<int,Pierre&> pos_objects;
    std::map<int,bool> freePositions;


    void addPlayer();
    void addPlayer(Joueur&);
    void addPlayers(std::vector<Joueur&>vect);
    void killPlayer(int);
    void addPierre();
    void addPierre(Pierre);
    void addPierres(std::vector<Joueur&> vect);


    





};

#endif