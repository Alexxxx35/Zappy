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