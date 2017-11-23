#ifndef UNIT_H
#define UNIT_H

#include <stdio.h>
#include "boolean.h"
#include "globalconst.h"
#include "point.h"

/***************************** Definisi tipe UNIT ********************/
/* Definisi */
typedef struct {
	POINT Location;
	char Type;
	int Owner;
	int Max_Health;
	int Health;
	int Attack;
	int Movement;
	int Attack_Type;
	int Price;
	boolean Attack_Chance;
	boolean Controlled;
} UNIT;

/* Macro Unit */
#define LocationX(U) (U).Location.X
#define LocationY(U) (U).Location.Y
#define Type(U) (U).Type
#define Owner(U) (U).Owner
#define MaxHealth(U) (U).Max_Health
#define Health(U) (U).Health
#define Attack(U) (U).Attack
#define Movement(U) (U).Movement
#define AttackType(U) (U).Attack_Type
#define Price(U) (U).Price
#define AttackChance(U) (U).Attack_Chance
#define Controlled(U) (U).Controlled

#define PLocationX(U) (U)->Location.X
#define PLocationY(U) (U)->Location.Y
#define PType(U) (U)->Type
#define POwner(U) (U)->Owner
#define PMaxHealth(U) (U)->Max_Health
#define PHealth(U) (U)->Health
#define PAttack(U) (U)->Attack
#define PMovement(U) (U)->Movement
#define PAttackType(U) (U)->Attack_Type
#define PPrice(U) (U)->Price
#define PAttackChance(U) (U)->Attack_Chance
#define PControlled(U) (U)->Controlled

/***************************** Fungsi & Prosedur ********************/
UNIT Unit_CreateEmpty(POINT P);
/* Membuat Unit kosong */

UNIT Unit_Init(char type, POINT P, int owner);
/* Mengirimkan stat awal untuk unit yang diinginkan berdasarkan parameter type */
/* Unit : King(K), Swordsman(S), Archer(A), WhiteMage(W) */ 

void Unit_Heal(UNIT *U);
/* Meningkatkan Health untuk unit-unit yang berada adjacent dengan White Mage */
/* Unit W = White Mage, U = Unit yang akan di-heal */ 

void Unit_PrintType(char type);
/* Print unit dalam string berdasarkan type */

#endif