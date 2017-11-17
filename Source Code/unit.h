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


/***************************** Fungsi & Prosedur ********************/
UNIT Unit_CreateEmpty(POINT P);
/* Membuat Unit kosong */

UNIT Unit_Init(char type, POINT P, int owner);
/* Mengirimkan stat awal untuk unit yang diinginkan berdasarkan parameter type */
/* Unit : King(K), Swordsman(S), Archer(A), WhiteMage(W) */


void Unit_Battle(UNIT *U1, UNIT *U2);
/* Melakukan serangan antara Unit 1 dan Unit 2 */
/* U1 menyerang U2 */
/* Rumus serangan : U2.Health = U2.Health - U1.Attack */
/* Setelah U1 menyerang : */
/* Movement U1 -> 0 */
/* Attack chance U1 -> false */
/* Kalau tipe serangan sama, U2 akan melakukan counter */ 

void Unit_Heal(UNIT *U);
/* Meningkatkan Health untuk unit-unit yang berada adjacent dengan White Mage */
/* Unit W = White Mage, U = Unit yang akan di-heal */ 

#endif