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
    void AddPlayer();
    void AddPlayer(Joueur*);
    void AddPlayers(int);
    void AddPierre();
    bool IsFull();
    bool IsVictory();
    void KillLoosers();
    void KillPlayer(int); // fonction de test
    void MoveFwd(Joueur*);
    void MoveBack(Joueur*);
    void MoveJump(Joueur*);
    int FindPosition(Joueur*);
    void ExecuteAction(Joueur*,Action);
    void ExecuteActions(Joueur*);
    void ConsumeObject(Joueur*,Pierre*);
    void run();
    Joueur* GetPlayerById(int);
    int GetPlayerNumber();


    private:
    const int _WIDTH;
    const int _HEIGHT;
    char **_plateau;
    
    std::map<int,Joueur*> pos_players;
    std::map<int,Pierre*> pos_objects;
    std::vector<int> freePositions;

    int GetRandomFreePosition();
    void removeFreePosition(int);



    





};

#endif