#ifndef COMMAND_H
#define COMMAND_H

#include "boolean.h"
#include "globalconst.h"
#include "unit.h"
#include "listu.h"
#include "matriks.h"
#include "player.h"


/*************** ADT Command *************/

void Command_Recruit(MATRIKS *M, PLAYER *P);

void Command_Info(MATRIKS M);

void Command_Input(MATRIKS *M, PLAYER *P, boolean *finalstate);



#endif