#include "Action.hh"
#include "Globals.hh"




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
        return "left";
        break;
    case ActionNames::right:
        return "right";
        break;
    case ActionNames::fwd:
        return "fwd";
        break;
    case ActionNames::leftfwd:
        return "leftfwd";
        break;
    case ActionNames::rightfwd:
        return "rightfwd";
        break;
    case ActionNames::jump:
        return "jump";
        break;
    case ActionNames::back:
        return "back";
        break;
    case ActionNames::inspect:
        return "rightfwd";
        break;
    case ActionNames::me:
        return "rightfwd";
        break;
    default:
    return "error";
        break;
    }
}