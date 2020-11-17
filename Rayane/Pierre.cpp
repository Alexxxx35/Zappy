#include "Pierre.hh"


Pierre::Pierre(PierreNames type, int pos) : _pierreType(type), _pos(pos){
    
}
Pierre::~Pierre(){

}


PierreNames Pierre::GetType(){
    return this->_pierreType;
}

int Pierre::GetPos(){
    return this->_pos;
}

char Pierre::ToChar(){
    switch (this->_pierreType)
    {
    case PierreNames::Linemate:
        return ('L');
        break;
    case PierreNames::Deraumere:
        return ('D');
        break;
    case PierreNames::Mendiane:
        return('M');
        break;
    case PierreNames::Sibur:
        return ('S');
        break;
    default:
        return('N');
        break;
    }
}