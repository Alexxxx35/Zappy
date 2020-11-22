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
void Plateau::removeFreePosition(int pos){
    std::vector<int>::iterator index = std::find(freePositions.begin(), freePositions.end(), pos);
    if (index != freePositions.end())
    freePositions.erase(index);
}

void Plateau::ClearPlateau(){
    int i,j;
    char count = ' '; 
    for (i = 0; i <  _HEIGHT; i++) 
        for (j = 0; j < _WIDTH; j++) 
        _plateau[i][j] = count;
}

void Plateau::ConsumeObject(Joueur* j, Pierre* p){
    std::cout << "CONSUMING OBJECT :" << p->ToChar() << std::endl;
    switch (p->GetType())
    {
    case PierreNames::Deraumere:
        j->ReduirePointDeVie();
        break;
    case PierreNames::Linemate:
        j->AugmenterPointDeVie();
        break;
    case PierreNames::Mendiane:
        j->AugmenterPointDeVictoire();
        break;
    case PierreNames::Sibur:
        for (auto it=pos_players.begin(); it!=pos_players.end(); ++it){
            if(it->second->GetId() != j->GetId())
                it->second->ReduirePointDeVie();
        }
        break;
    default:
        break;
    }
}

Plateau::Plateau(): _WIDTH(5),_HEIGHT(5){
    _plateau = (char **)malloc(_HEIGHT * sizeof(char *)); 
    for (int i=0; i<_HEIGHT; i++) 
        _plateau[i] = (char*)malloc(_WIDTH * sizeof(char));
    ClearPlateau();
    for(int i =0;i<_HEIGHT*_WIDTH;i++)
        freePositions.push_back(i);
    
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
    //std::cout << "Destruction du plateau ..." << std::endl;
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
void Plateau::AddPlayer(Joueur* j){
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
                this->freePositions.push_back(it->first);
                delete it->second;
                it = pos_players.erase(it);
            }
            else {
                ++it;
            }
        } 
}



int Plateau::FindPosition(Joueur* j){
    for (auto it= pos_players.begin();it!=pos_players.end();++it){
        if(it->second->GetId() == j->GetId()){
            return it->first;
        }
    }
    return -1;
}

void Plateau::MoveFwd(Joueur* j){
    int position = FindPosition(j);
    int ligne = position/_WIDTH;
    int colonne = position%_WIDTH;
    //std::cout << " (old position :"<<position<<")"<<std::endl;
    int v;
    switch (j->GetOrientation())
    {
    case Orientation::North:
        //std::cout<< "Orientation Nord" << std::endl;
        v = std::max(0,--ligne);
        ligne = v;
        break;
    case Orientation::West:
        //std::cout<< "Orientation West" << std::endl;
        v=std::max(0,--colonne);
        colonne=v;
        break;
    case Orientation::East:
        //std::cout<< "Orientation East" << std::endl;
        v=std::min(_WIDTH-1,++colonne);
        colonne=v;
        break;
    case Orientation::South:
        //std::cout<< "Orientation South" << std::endl;
        v=std::min(_HEIGHT-1,++ligne);
        ligne= v;
        break;
    default:
        break;
    }

    int newPosition = ligne*_WIDTH+colonne;
    //std::cout << " new position :" << newPosition << std::endl;
    if(pos_players.find(newPosition) == pos_players.end()){
        //move player & consume object if possible
        pos_players.insert(std::pair<int,Joueur*>(newPosition,j));
        pos_players.erase(position);
        this->removeFreePosition(newPosition);
        this->freePositions.push_back(position);
        this->_plateau[ligne][colonne]= '0' + j->GetId();
        this->_plateau[position/_WIDTH][position%_WIDTH]=' ';
        if(pos_objects.find(newPosition) != pos_objects.end()){
            this->ConsumeObject(j,pos_objects[newPosition]);
            delete pos_objects[newPosition];
            pos_objects.erase(newPosition);
        }
        
    }
    else{
        //damage player in newPosition
        pos_players.find(newPosition)->second->ReduirePointDeVie();

    }

}

void Plateau::MoveBack(Joueur* j){
    int position = FindPosition(j);
    int ligne = position/_WIDTH;
    int colonne = position%_WIDTH;
    int v;
    switch (j->GetOrientation())
    {
    case Orientation::North:
        v = std::min(_HEIGHT-1,++ligne);
        ligne = v;
        break;
    case Orientation::West:
        v=std::min(_WIDTH,++colonne);
        colonne=v;
        break;
    case Orientation::East:
        v=std::max(0,--colonne);
        colonne=v;
        break;
    case Orientation::South:
        v=std::max(0,--ligne);
        ligne= v;
        break;
    default:
        break;
    }

    int newPosition = ligne*_WIDTH+colonne;
    if(pos_players.find(newPosition) == pos_players.end()){
        //move player & consume object if possible
        pos_players.insert(std::pair<int,Joueur*>(newPosition,j));
        pos_players.erase(position);
        this->removeFreePosition(newPosition);
        this->freePositions.push_back(position);
        this->_plateau[ligne][colonne]= '0'+j->GetId();
        this->_plateau[position/_WIDTH][position%_WIDTH]=' ';
        if(pos_objects.find(newPosition) != pos_objects.end()){
            this->ConsumeObject(j,pos_objects[newPosition]);
            delete pos_objects[newPosition];
            pos_objects.erase(newPosition);
        }

        
    }
    else{
        //damage player in newPosition
        //std::cout << "found another player : KILL HIM !"<<std::endl;
        pos_players.find(newPosition)->second->ReduirePointDeVie();

    }
}

void Plateau::MoveJump(Joueur* j){
    int position = FindPosition(j);
    int ligne = position/_WIDTH;
    int colonne = position%_WIDTH;
    int v;
    switch (j->GetOrientation())
    {
    case Orientation::North:
        ligne-=3;
        v = std::max(0,ligne);
        ligne = v;
        break;
    case Orientation::West:
        colonne-=3;
        v=std::max(0,colonne);
        colonne=v;
        break;
    case Orientation::East:
        colonne+=3;
        v=std::min(_WIDTH-1,colonne);
        colonne=v;
        break;
    case Orientation::South:
        ligne+=3;
        v=std::min(_HEIGHT-1,ligne);
        ligne= v;
        break;
    default:
        break;
    }

    int newPosition = ligne*_WIDTH+colonne;
    if(pos_players.find(newPosition) == pos_players.end()){
        //move player & consume object if possible
        pos_players.insert(std::pair<int,Joueur*>(newPosition,j));
        pos_players.erase(position);
        this->removeFreePosition(newPosition);
        this->freePositions.push_back(position);
        this->_plateau[ligne][colonne]= '0' + j->GetId();
        this->_plateau[position/_WIDTH][position%_WIDTH]=' ';
        if(pos_objects.find(newPosition) != pos_objects.end()){
            this->ConsumeObject(j,pos_objects[newPosition]);
            delete pos_objects[newPosition];
            pos_objects.erase(newPosition);
        }

        
    }
    else{
        //damage player in newPosition
        pos_players.find(newPosition)->second->ReduirePointDeVie();

    }
}

void Plateau::ExecuteAction(Joueur* j,Action action){
    j->ConsumeEnergie(action.GetCost()); // débite l'energie
    if(j->GetEnergie()>=0) //vérifie si le joueur n'a pas dépassé sa capacité en energie
    switch (action.GetAction())
    {
    case ActionNames::fwd:
        this->MoveFwd(j);
        break;
    case ActionNames::left:
        j->TurnLeft();
        break;
    case ActionNames::right:
        j->TurnRight();
        break;
    case ActionNames::leftfwd:
        j->TurnLeft();
        this->MoveFwd(j);
        break;
    case ActionNames::rightfwd:
        j->TurnRight();
        this->MoveFwd(j);
        break;
    case ActionNames::back:
        this->MoveBack(j);
        break;
    case ActionNames::jump:
        this->MoveJump(j);
        break;
    default:
        break;
    }
}

void Plateau::ExecuteActions(Joueur* j){
    std::cout << "executing actions for player id "<< j->GetId()<<std::endl; 
    j->QueueRandomActions();
    std::cout << "generated random actions..." << std::endl;
    std::queue<Action> actions = j->GetQueue();
    while(!actions.empty()){
        std::cout << "executing action ..." << std::endl;
        ExecuteAction(j,actions.front());
        actions.pop();
    }
}

void Plateau::run(){
    //Action action(ActionNames::fwd);
    std::vector<Joueur*> vect;
    for (auto it =pos_players.begin();it!=pos_players.end();++it){
        vect.push_back(it->second);
    }
    for(auto it = vect.begin();it!=vect.end();++it)
    //this->ExecuteAction(*it,action);
    this->ExecuteActions(*it);
}



Joueur* Plateau::GetPlayerById(int id){
    for (auto it = pos_players.begin(); it != pos_players.end(); ++it){
        if (it->second->GetId() == id){
            return it->second;
        }
    }
    return nullptr;
}

int Plateau::GetPlayerNumber(){
    return this->pos_players.size();
}

///////////////////////////////