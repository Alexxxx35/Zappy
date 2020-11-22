#include "Action.hh"
#include "Globals.hh"
#include <cstring>



Action::Action(ActionNames action) : _action(action),_cost(Globals::ACTION_COSTS[action]){
    
}
Action::~Action(){}

ActionNames Action::GetAction(){
    return this->_action;
}

int Action::GetCost(){
    return _cost;
}

std::string Action::toString(){
    switch (this->_action)
    {
    case ActionNames::left:
        return "left\n";
        break;
    case ActionNames::right:
        return "right\n";
        break;
    case ActionNames::fwd:
        return "fwd\n";
        break;
    case ActionNames::leftfwd:
        return "leftfwd\n";
        break;
    case ActionNames::rightfwd:
        return "rightfwd\n";
        break;
    case ActionNames::jump:
        return "jump\n";
        break;
    case ActionNames::back:
        return "back\n";
        break;
    case ActionNames::inspect:
        return "inspect\n";
        break;
    case ActionNames::me:
        return "me\n";
        break;
    default:
    return "error";
        break;
    }
}


ActionNames Action::ActionFromChar(char* str){
    if(strcmp(str, "left\n") == 0){
        return ActionNames::left;
    }

    if(strcmp(str, "right\n") == 0){
        return ActionNames::right;
    }

    if(strcmp(str, "fwd\n") == 0){
        return ActionNames::fwd;
    }

    if(strcmp(str, "leftfwd\n") == 0){
        return ActionNames::leftfwd;
    }

    if(strcmp(str, "rightfwd\n") == 0){
        return ActionNames::rightfwd;
    }

    if(strcmp(str, "jump\n") == 0){
        return ActionNames::jump;
    }

    if(strcmp(str, "back\n") == 0){
        return ActionNames::back;
    }

    if(strcmp(str, "inspect\n") == 0){
        return ActionNames::inspect;
    }

    else{
        return ActionNames::me;
    }
}