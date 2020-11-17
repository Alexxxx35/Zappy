#include "Plateau.hh"
#include <iostream>
#include <experimental/random>



////////////////////////////////////
void displayVector(std::vector<int> myvector){
    for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
    std::cout << std::endl;
}
template <typename T, typename S>
void displayMap(std::map<T,S> mymap){
    for (auto it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

void interline(int W){
    std::cout << "+||";
    for (int i=0 ; i < 3*W+(W-1) ; i++) std::cout << "-";
    std::cout << "||+";
    std::cout << std::endl;
}

void upperLine(int W){
    for(int i =0 ; i < 3*W+6+(W-1); i++) std::cout << "+"; // la ligne du haut
    std::cout << std::endl;
}




/////////////////////////////////////
void Plateau::ClearPlateau(){
    int i,j;
    char count = ' '; 
    for (i = 0; i <  _HEIGHT; i++) 
        for (j = 0; j < _WIDTH; j++) 
        _plateau[i][j] = count;
}



Plateau::Plateau(): _WIDTH(5),_HEIGHT(5){
    _plateau = (char **)malloc(_HEIGHT * sizeof(char *)); 
    for (int i=0; i<_HEIGHT; i++) 
        _plateau[i] = (char*)malloc(_WIDTH * sizeof(char));
    ClearPlateau();
    for(int i =0;i<_HEIGHT*_WIDTH;i++)
        freePositions.push_back(i);
    displayVector(freePositions);
    
}

Plateau::Plateau(int width, int height): _WIDTH(width), _HEIGHT(height){
    _plateau = (char **)malloc(_HEIGHT * sizeof(char *)); 
    for (int i=0; i<_HEIGHT; i++) 
        _plateau[i] = (char*)malloc(_WIDTH * sizeof(char));
    ClearPlateau();
    for(int i =0;i<_HEIGHT*_WIDTH;i++)
        freePositions.push_back(i);

}

Plateau::~Plateau(){
    std::cout << "Destruction du plateau ..." << std::endl;
}

void Plateau::DisplayPlateau(){
    upperLine(_WIDTH);
    int i,j;
    for (i = 0; i <  _HEIGHT; i++){
        for (j = 0; j < _WIDTH; j++){
            if (j==0) std::cout << "+||";
            std::cout << " " << _plateau[i][j] << " |";
        }
        //std::cout << "|" << std::endl << std::endl;
        std::cout << "|+" << std::endl;
        if (i != _HEIGHT-1) interline(_WIDTH);
    }
    upperLine(_WIDTH);
}




int Plateau::GetRandomFreePosition(){

    int index = std::experimental::randint(0,(int)freePositions.size()-1);
    int value = freePositions.at(index);
    this->freePositions.erase(freePositions.cbegin()+index);
    return value;
}
void Plateau::AddPierre(){
    if(freePositions.size()>0){
    int tirage = std::experimental::randint(0,3);
    PierreNames type = PierreNames(tirage);
    int pos = this->GetRandomFreePosition();
    Pierre* pierre = new Pierre(type,pos);
    this -> pos_objects.insert(std::pair<int,Pierre*>(pos,pierre));
    this-> _plateau[pos/_WIDTH][pos%_WIDTH]= pierre->ToChar();
    }
}


void Plateau::AddPlayer(){
    Joueur *j = new Joueur();
    int pos = this->GetRandomFreePosition(); //met à jour freePositions automatiquement
    this->pos_players.insert(std::pair<int,Joueur*>(pos,j)); // ajoute la paire position-joueur
    std::cout << "ADDED PLAYER: "<<j->GetId() << std::endl;
    this->_plateau[pos/_WIDTH][pos%_WIDTH]= '0'+j->GetId();
}
void Plateau::AddPlayers(int nbPlayers){
    for(int i =0; i< nbPlayers;i++){
        this->AddPlayer();
    }
}

bool Plateau::IsFull(){
    return this->freePositions.size()==0;
}

bool Plateau::IsVictory(){
    if (pos_players.size()==1) return true;
    for (auto it=pos_players.begin(); it!=pos_players.end(); ++it){
        if (it->second->GetVictoire() >=10) return true;
    }
    return false;
}

void Plateau::KillLoosers(){
    auto it = pos_players.cbegin();
    while (it!=pos_players.cend()){
            if (it->second->GetVie() ==0){
                this->_plateau[it->first/_WIDTH][it->first%_WIDTH]=' ';
                delete it->second;
                it = pos_players.erase(it);
            }
            else {
                ++it;
            }
        } 
}



void Plateau::KillPlayer(int id){
    for(auto it = pos_players.begin();it!=pos_players.end();++it){
        if(it->second->GetId()==id){
            it->second->TAMERE();
        }
    }
}





///////////////////////////////