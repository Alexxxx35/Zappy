#ifndef GLOBALS_H
#define GLOBALS_H

#include <map>
#include <string>
#include "ActionNames.hh"

namespace Globals{
std::map<ActionNames,int> ACTION_COSTS = {
    {ActionNames::left,1},
    {ActionNames::right,1},
    {ActionNames::fwd, 1},
    {ActionNames::leftfwd,1},
    {ActionNames::rightfwd,1},
    {ActionNames::jump,2},
    {ActionNames::back,1},
    {ActionNames::inspect,1},
    {ActionNames::me,0}
};
}

#endif
