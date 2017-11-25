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
	boolean Controlled = false;
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
		U.Max_Health = 30;
		U.Health = 30;
		U.Attack = 5;
		U.Movement = 2;
		U.Attack_Type = Ranged;
		U.Price = 5;
		boolean Attack_Chance = false;
		boolean Controlled = false;
	}
	else if(type == 'S') { /*type unit = Swordsman */
		U.Location.X = P.X;
		U.Location.Y = P.Y;
		U.Type = 'S';
		U.Owner = owner;
		U.Max_Health = 25;
		U.Health = 25;
		U.Attack = 10;
		U.Movement = 4;
		U.Attack_Type = Melee;
		U.Price = 4;
		boolean Attack_Chance = false;
		boolean Controlled = false;
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
		boolean Controlled = false;
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
		boolean Controlled = false;
	}

	return U;
}

void Unit_PrintType(char type)
/* Print unit dalam string berdasarkan type */
{
	if(type == 'K') {
		printf("King");
	} else if(type == 'A') {
		printf("Archer");
	} else if(type == 'S') {
		printf("Swordsman");
	} else if(type == 'W') {
		printf("Whitemage");
	}
}