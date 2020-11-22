#ifndef ACTION_H
#define ACTION_H

#include "ActionNames.hh"
#include <string>

class Action {
    private:
    const ActionNames _action;
    const int _cost;

    public:
    Action(ActionNames action);
    ~Action();

    ActionNames GetAction();
    int GetCost();
    std::string toString();
    static ActionNames ActionFromChar(char*);

};

#endif