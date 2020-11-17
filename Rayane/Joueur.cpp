#include "Joueur.hh"
#include <experimental/random>
#include <iostream>



int Joueur::nextID = 0;

Joueur::Joueur(): _energie(2),_pdvie(10),_pdvictoire(0){
    _id = ++nextID;
    int v =  std::experimental::randint((int) Orientation::North, (int) Orientation::West);
    this->_orientation = Orientation(v);

}
Joueur::~Joueur(){
    std::cout << "Je meurs ..." << std::endl;
}


int Joueur::GetId(){
    return this->_id;
}

int Joueur::GetEnergie(){
    return this->_energie;
}

int Joueur::GetVictoire(){
    return this->_pdvictoire;
}

int Joueur::GetVie(){
    return this->_pdvie;
}

Orientation Joueur::GetOrientation(){
    return  this->_orientation;
}


void Joueur::AugmenterPointDeVie(){
    this->_pdvie = std::min(10,_pdvie+1);
}

void Joueur::ReduirePointDeVie(){
    this->_pdvie = std::max(0,_pdvie-1);
}

void Joueur::AugmenterPointDeVictoire(){
    this-> _pdvictoire = std::min(10,_pdvictoire+1);
}

void Joueur::ResetEnergie(){
    this->_energie =2;
}

void Joueur::TAMERE(){
    _pdvie =0;
}



