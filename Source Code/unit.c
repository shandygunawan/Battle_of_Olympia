#include "unit.h"


/************ UNIT *********************/
UNIT Unit_CreateEmpty(POINT P)
{
	UNIT U;

	U.Location = P;
	U.Type = ' ';
	U.Owner = 0;
	U.Max_Health = 50;
	U.Health = 50;
	U.Attack = 10;
	U.Movement = 1;
	U.Attack_Type = Melee;
	U.Price = 0;
	boolean Attack_Chance = false;
    return U;
}

UNIT Unit_Init(char type, POINT P, int owner)
/* Mengirimkan stat awal untuk unit yang diinginkan berdasarkan parameter type */
/* Unit : King(K), Swordsman(S), Archer(A), WhiteMage(W) */
{
	UNIT U;

	if(type == 'A') { /*type unit = Archer */
		U.Location.X = P.X;
		U.Location.Y = P.Y;
		U.Type = 'A';
		U.Owner = owner;
		U.Max_Health = 25;
		U.Health = 25;
		U.Attack = 10;
		U.Movement = 2;
		U.Attack_Type = Ranged;
		U.Price = 5;
		boolean Attack_Chance = false;
	}
	else if(type == 'S') { /*type unit = Swordsman */
		U.Location.X = P.X;
		U.Location.Y = P.Y;
		U.Type = 'S';
		U.Owner = owner;
		U.Max_Health = 30;
		U.Health = 30;
		U.Attack = 12;
		U.Movement = 4;
		U.Attack_Type = Melee;
		U.Price = 4;
		boolean Attack_Chance = false;
	}
	else if(type == 'W') { /* type unit = WhiteMage */
		U.Location.X = P.X;
		U.Location.Y = P.Y;
		U.Type = 'W';
		U.Owner = owner;
		U.Max_Health = 40;
		U.Health = 40;
		U.Attack = 5;
		U.Movement = 2;
		U.Attack_Type = Ranged;
		U.Price = 10;
		boolean Attack_Chance = false;
	}
	else if(type == 'K') { /* type unit = King */
		U.Location.X = P.X;
		U.Location.Y = P.Y;
		U.Type = 'K';
		U.Owner = owner;
		U.Max_Health = 50;
		U.Health = 50;
		U.Attack = 10;
		U.Movement = 1;
		U.Attack_Type = Melee;
		U.Price = 0;
		boolean Attack_Chance = false;
	}

	return U;
}

void Unit_Battle(UNIT *U1, UNIT *U2)
/* Melakukan serangan antara Unit 1 dan Unit 2 */
/* U1 menyerang U2 */
/* Rumus serangan : U2.Health = U2.Health - U1.Attack */
/* Setelah U1 menyerang : */
/* Movement U1 -> 0 */
/* Attack chance U1 -> false */
/* Kalau tipe serangan sama, U2 akan melakukan counter */ 
{
	U2->Health = U2->Health - U1->Attack;
	U1->Movement = 0;
	U1->Attack_Chance = false;

	if(U2->Type != 'K') {
	/* U2 adalah king */
		
		if( (U1->Attack_Type == U2->Attack_Type) && (U2->Health > 0) ) {
		/* Tipe attack sama & Health H2 > 0 */
		/* U1 mendapat counter sebesar attack U2 */
			U1->Health = U1->Health - U2->Attack;		
		}
		/* Tipe attack tidak sama tidak ada counter */
	}
	else {
	/* U2 adalah King */
		
		if(U2->Health > 0){
		/* King selalu bisa counter */
			U2->Health = U2->Health - U1->Attack;			
		}
	}
}