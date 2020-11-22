#ifndef PIERRE_H
#define PIERRE_H
#include "PierreNames.hh"


class Pierre{

private:
const PierreNames _pierreType;
const int _pos;


public:
Pierre(PierreNames,int);
~Pierre();
PierreNames GetType();
int GetPos();
char ToChar();

};
#endif

