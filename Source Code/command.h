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

void Command_Move(MATRIKS *M, PLAYER P[], int idx, UNIT *U, Stack *S);

void Command_Recruit(MATRIKS *M, PLAYER *P, int idx, UNIT U);

void Command_Attack(MATRIKS *M, PLAYER P[], int idx, UNIT *U, boolean *finalstate);

void Command_Battle(MATRIKS *M, PLAYER P[], int idx, UNIT *U1, UNIT *U2, boolean *finalstate);

void Command_Info(MATRIKS M);

void Command_ReleaseUnit(MATRIKS *M, PLAYER *P, UNIT *U);

void Command_ChangeUnit(MATRIKS *M, PLAYER *P, int idx, UNIT *U);

void Command_ControlUnit(MATRIKS *M, UNIT *U);

void Command_ReplenishUnitMovement(MATRIKS *M, PLAYER *P, int idx);

void Command_UpdateUnitPosition(PLAYER *P, UNIT *U, int X, int Y);

void Command_EndTurn(MATRIKS *M, PLAYER *P, UNIT *U);

void Command_Input(MATRIKS *M, PLAYER P[], int idx, boolean *finalstate);

#endif