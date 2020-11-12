#include "Plateau.hh"
#include <iostream>


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
    
}

Plateau::Plateau(int width, int height): _WIDTH(width), _HEIGHT(height){
    _plateau = (char **)malloc(_HEIGHT * sizeof(char *)); 
    for (int i=0; i<_HEIGHT; i++) 
        _plateau[i] = (char*)malloc(_WIDTH * sizeof(char));
}

Plateau::~Plateau(){
    std::cout << "Destruction du plateau ..." << std::endl;
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