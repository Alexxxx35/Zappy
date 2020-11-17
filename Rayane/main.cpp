#include <iostream>
#include <string>
#include <experimental/random>
#include "Joueur.hh"
#include "Action.hh"
#include "Plateau.hh"
#include "Pierre.hh"
#include "PierreNames.hh"




int main(){
    Plateau plateau;
    plateau.AddPlayers(4);
    plateau.AddPierre();
    plateau.AddPierre();
    plateau.DisplayPlateau();

    plateau.KillPlayer(4);
    std::cout << "killed someone ..." << std::endl;
    plateau.KillLoosers();
    plateau.DisplayPlateau();


}