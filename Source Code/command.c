#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

void Command_Recruit(MATRIKS *M, PLAYER *P) {
	int baris,kolom;
	UNIT K = Unit(First(PListUnit(P)));
	POINT Po;
	int unit;
	char cont;
	boolean KinginTower = true;

	if(Type(K) == 'K'){
		if (LocationX(K) != PTower(P).X || LocationY(K) != PTower(P).Y) {
			printf("You can't recruit. Your king is not in the Tower.\n");
			KinginTower = false;
		} else {
			for(;;){
				printf("Enter Coordinate of empty castle : "); scanf("%d %d", &kolom, &baris);

				/* Cek kondisi Map pada koordinat yang dipilih */
				if(PElmt(M,baris,kolom).Terrain.Type != 'C') { /* Koordinat Input bukan castle */
					printf("That is not a castle!\n");
				} else { /* Koordinat input adalah castle */
					if(PElmt(M,baris,kolom).Terrain.Owner != PNumber(P)){ /* Castle punya pemain lain */
						printf("That is not your castle!\n");
					} else { /* Castle punya pemain */
						if( (PElmt(M,baris,kolom).Unit.Type == 'A') || (PElmt(M,baris,kolom).Unit.Type == 'W') || (PElmt(M,baris,kolom).Unit.Type == 'S') ) { /* ada unit di castle */
							printf("The Castle is occupied!\n");
						} else {
							break;
						}
					}
				}
			}
		}
	} else {
		printf("You are not a king.\n");
		KinginTower = false;
	}

	Po.X = baris;
	Po.Y = kolom;

	/* Menampilkan list recruit yang bisa direkrut */
	
	if(KinginTower == true){
		printf("=== List Of Recruits ===\n");
		printf("1. Archer | Health 20 | ATK 4 | 5G\n");
		printf("2. Swordsman | Health 20 | ATK 3 | 4G\n");
		printf("3. White Mage | Health 20 | ATK 2 | 20G\n");
		
		if (PGold(P) >= 4){
			printf("Enter No. of unit you want to recruit : "); scanf("%d", &unit);
			if(unit == 1){
				printf("You have recruited an archer!\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('A',Po, PNumber(P));
				PElmt(M,baris,kolom).Unit.Owner = PNumber(P);
				PGold(P) = PGold(P)-5;
				ListU_InsULast(&P->Unit, PElmt(M,baris,kolom).Unit);

			} else if(unit == 2){
				printf("You have recruited a Swordsman!\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('S',Po, PNumber(P));
				PElmt(M,baris,kolom).Unit.Owner = PNumber(P);
				PGold(P) = PGold(P)-5;
				ListU_InsULast(&P->Unit, PElmt(M,baris,kolom).Unit);
			
			} else if(unit == 3){
				printf("You have recruited a White Mage!\n");
				printf("Seems that you are a big spender heh?\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('W',Po,PNumber(P));
				PElmt(M,baris,kolom).Unit.Owner = PNumber(P);
				PGold(P) = PGold(P)-10;
				ListU_InsULast(&P->Unit, PElmt(M,baris,kolom).Unit);
			}
		} else {
			printf("Your Gold is not enough to recruit any new member.\n");
		}
	}
	printf("\n");
}

void Command_Info(MATRIKS M)
{
	int baris, kolom;
	printf("Enter map's coordinate : "); scanf("%d %d", &kolom, &baris);
	TERRAIN terrain = Elmt(M,baris,kolom).Terrain;
	UNIT unit = Elmt(M,baris,kolom).Unit;

	printf("\n");
	printf("-- Terrain --\n");
	if(Elmt(M,baris,kolom).Terrain.Owner != NotOwned ) {
		printf("Owner : Player %d\n", Owner(terrain));
	} else {
		printf("Owner : None\n");
	}
	if(terrain.Type == 'T') {
		printf("Type  : Tower\n");
	} else if(terrain.Type == 'C') {
		printf("Type  : Castle\n");
	} else {
		printf("Type  : None\n");
	}

	printf("-- Unit --\n");
	if( (Type(unit) != 'A') && (Type(unit) != 'S') && (Type(unit) != 'W') && (Type(unit) != 'K') ) {
		printf("There is no unit here.\n");
		printf("\n");
	} else {
		if(Type(unit) == 'A'){
			printf("Type        : Archer\n");
		} else if(Type(unit) == 'S') {
			printf("Type        : Swordsman\n");
		} else if(Type(unit) == 'W') {
			printf("Type        : White Mage\n");
		} else if(Type(unit) == 'K') {
			printf("Type        : King\n");
		}
		
		printf("Owner       : Player %d\n", Owner(unit));
		printf("Max. Health : %d\n", MaxHealth(unit));
		printf("Health      : %d\n", Health(unit));
		printf("Attack      : %d\n", Attack(unit));
		printf("Movement    : %d\n", Movement(unit));
		
		if(AttackType(unit) == Melee){
			printf("Attack Type : Melee\n");
		} else if(AttackType(unit) == Ranged) {
			printf("Attack Type : Ranged\n");
		}
		printf("Price       : %d\n", Price(unit));
		if(AttackChance(unit) == true) {
			printf("Can Attack  : Yes\n");
		} else {
			printf("Can Attack  : No\n");
		}
		printf("\n");
	}
	printf("-----------------------\n\n");
}

void Command_ChangeUnit(MATRIKS *M, PLAYER *P)
{
	UNIT U;

	ListU_DelUFirst(&PListUnit(P), &U);
	
	int X = LocationX(U);
	int Y = LocationY(U);	

	PElmt(M,X,Y).Unit.Owner = PNumber(P);
	U.Owner = PNumber(P);
	ListU_InsULast(&PListUnit(P), U);
}

void Command_ControlUnit(MATRIKS *M, ListU *L)
{
	int X = Unit(First(*L)).Location.X;
	int Y = Unit(First(*L)).Location.Y;

	PElmt(M,X,Y).Unit.Owner = Controlled;
	Unit(First(*L)).Owner = Controlled;
}

void Command_Input(MATRIKS *M, PLAYER *P, boolean *finalstate)
{
	char command[50];

	for(;;){
		Command_ControlUnit(M, &PListUnit(P));
		Player_PrintTurn(*P);
		printf("Your Input : ");
		scanf("%s", &command);

		if(strcmp("RECRUIT",command) == 0) {
			Command_Recruit(M, P);
		} else if(strcmp("INFO", command) == 0) {
			Command_Info(*M);
		} else if(strcmp("MAP", command) == 0) {
			Map_Print(*M);
		} else if(strcmp("CHANGE_UNIT", command) == 0) {
			Command_ChangeUnit(M, P);
		} else if(strcmp("END_TURN", command) == 0) {
			printf("\n");
			break;
		} else if(strcmp("EXIT", command) == 0) {
			exit(0);
		}
	}
}

	/*
	if(command == "MOVE") {
		Command_Move();
	} else if(command == "UNDO") {
		Command_Undo();
	} else if(command == "ATTACK") {
		Command_Attack();
	*/
