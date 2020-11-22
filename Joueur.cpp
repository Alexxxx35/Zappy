#include "Joueur.hh"
#include <experimental/random>
#include <iostream>



int Joueur::nextID = 0;

Joueur::Joueur(): _energie(2),_pdvie(10),_pdvictoire(0),_energieConsumed(0){
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

std::string Joueur::GetOrientationStr(){
    switch (this->_orientation)
    {
    case Orientation::North:
        return "North";
        break;
    case Orientation::West:
        return "West";
        break;
    case Orientation::East:
        return "East";
        break;
    case Orientation::South:
        return "South";
        break;
    default:
        return "error";
        break;
    }
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

void Joueur::ResetTour(){
    this->_energie =2;
    this->_energieConsumed=0;
    while(!_actions.empty()){
        _actions.pop();
    }
}

void Joueur::QueueRandomAction(){
    Action randomAction (ActionNames(std::experimental::randint(0,8)));
    if(randomAction.GetCost()+_energieConsumed <= _energie){
        _actions.push(randomAction);
        _energieConsumed += randomAction.GetCost();
    }
}

void Joueur::QueueRandomActions(){
    while(_energieConsumed <2){
        QueueRandomAction();
    }
}

std::queue<Action> Joueur::GetQueue(){
    return this->_actions;
}

void Joueur::TurnLeft(){
    if(this->_orientation==Orientation::North){
        this->_orientation = Orientation::West;
    }
    else{
        int v = (int) this->_orientation;
        this->_orientation = Orientation(--v);
    }
}

void Joueur::TurnRight(){
    int v = (int) this ->_orientation;
    this -> _orientation = Orientation(++v%4);
}

void Joueur::ConsumeEnergie(int cost){
    this->_energie-=cost;
}





