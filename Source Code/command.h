#ifndef COMMAND_H
#define COMMAND_H

#include "boolean.h"
#include "globalconst.h"
#include "stackt.h"
#include "unit.h"
#include "listu.h"
#include "matriks.h"
#include "listt.h"
#include "player.h"


/*************** ADT Command *************/

void Command_Move(MATRIKS *M, PLAYER *P, UNIT *U, Stack *S, TERRAIN *T);

void Command_Recruit(MATRIKS *M, PLAYER *P, UNIT U);

void Command_Info(MATRIKS M);

void Command_ReleaseUnit(MATRIKS *M, PLAYER *P, UNIT *U);

void Command_ChangeUnit(MATRIKS *M, PLAYER *P, UNIT *U);

void Command_ControlUnit(MATRIKS *M, UNIT *U);

void Command_ReplenishUnitMovement(MATRIKS *M, PLAYER *P);

void Command_UpdateUnitPosition(PLAYER *P, UNIT *U, int X, int Y);

void Command_EndTurn(MATRIKS *M, PLAYER *P, UNIT *U);

void Command_Input(MATRIKS *M, PLAYER *P, TERRAIN *T, boolean *finalstate);

#endif