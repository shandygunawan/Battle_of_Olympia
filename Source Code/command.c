#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

void Command_Move(MATRIKS *M, PLAYER *P, UNIT *U, Stack *S, TERRAIN *T)
{
	addressU addrU;
	int AmountMove; /* menyimpan besar pergerakan unit */
	POINT Po; Po.X = PLocationX(U); Po.Y = PLocationY(U); /* Menyimpan posisi awal unit */
	int baris,kolom; /* Menyimpan posisi target unit */

	/* input posisi target */
	printf("Please enter cell's coordinate x y : ");
	scanf("%d %d", &kolom, &baris);

	/* cek apakah target termasuk daerah movement */
	if(PElmt(M,baris,kolom).Unit.Type != '#') { /* target tidak termasuk daerah movement */
		printf("You can't move there.\n");
	
	} else { /* target termasuk daerah movement */
		addrU = ListU_SearchUnit(PListUnit(P), *U);
		Map_RemoveMovement(M, U); /* Menghapus movement di posisi awal unit */

		PElmt(M,Po.X,Po.Y).Unit = Unit_CreateEmpty(Po); /* Unit di posisi awal unit menjadi unit kosong */
		
		/* Menghitung besar pergerakan pemain */		
		if(kolom > Po.Y) {
			AmountMove = kolom - Po.Y;
		} else if(Po.Y > kolom) {
			AmountMove = Po.Y - kolom;
		} else if(baris > Po.X) {
			AmountMove = baris - Po.X;
		} else if(Po.X > baris) {
			AmountMove = Po.X - baris;
		}
		
		/* Posisi unit baru ada di target */
		Command_UpdateUnitPosition(P, U, baris, kolom);
		PLocationX(U) = baris; 
		PLocationY(U) = kolom;
		PElmt(M,baris,kolom).Unit = *U;
		
		/* Mengurangi jumlah movement unit setelah bergerak */
		PElmt(M,baris,kolom).Unit.Movement -= AmountMove;
		PMovement(U) -= AmountMove;
		Movement(Unit(addrU)) -= AmountMove;

		printf("You have successfully moved to (%d,%d)\n", kolom, baris);

		/* jika unit menduduki villlage, village diakuisisi dan movement unit -> 0 */
		if(PElmt(M,baris,kolom).Terrain.Type == 'V') {
			PElmt(M,baris,kolom).Terrain.Owner = PNumber(P); /* mengubah ownership village */
			ListT_InsVLast(&PListVillage(P), PElmt(M,baris,kolom).Terrain); /* Insert village ke list village pemain */
			printf("You also have successfully acquire the village.\n");
			
			*T = PElmt(M,baris,kolom).Terrain; /* digunakan untuk pemain berikutnya agar T dihapus dari list village pemain tersebut */
			PIncome(P) = PIncome(P)+5; /* menambah income pemain */
			PElmt(M,baris,kolom).Unit.Movement = 0; /* Mengubah movement unit matriks -> 0 */
			PMovement(U) = 0; /* Mengubah movement unit list -> 0 */
		}

	}
	printf("\n");
}

void Command_Recruit(MATRIKS *M, PLAYER *P, UNIT U)
{
	int baris,kolom;
	POINT Po;
	int unit;
	char cont;
	boolean KinginTower = true;

	if(Type(U) == 'K'){
		if (LocationX(U) != PTower(P).X || LocationY(U) != PTower(P).Y) {
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
				PElmt(M,baris,kolom).Unit.Movement = 0;
				PGold(P) = PGold(P)-5;
				PUpkeep(P) = PUpkeep(P)+1;
				ListU_InsULast(&P->Unit, PElmt(M,baris,kolom).Unit);

			} else if(unit == 2){
				printf("You have recruited a Swordsman!\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('S',Po, PNumber(P));
				PElmt(M,baris,kolom).Unit.Owner = PNumber(P);
				PElmt(M,baris,kolom).Unit.Movement = 0;
				PGold(P) = PGold(P)-5;
				PUpkeep(P) = PUpkeep(P)+1;
				ListU_InsULast(&P->Unit, PElmt(M,baris,kolom).Unit);
			
			} else if(unit == 3){
				printf("You have recruited a White Mage!\n");
				printf("Seems that you are a big spender heh?\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('W',Po,PNumber(P));
				PElmt(M,baris,kolom).Unit.Owner = PNumber(P);
				PElmt(M,baris,kolom).Unit.Movement = 0;
				PGold(P) = PGold(P)-10;
				PUpkeep(P) = PUpkeep(P)+1;
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

void Command_ReleaseUnit(MATRIKS *M, PLAYER *P, UNIT *U)
{
	int X = PLocationX(U);
	int Y = PLocationY(U);

	PElmt(M,X,Y).Unit.Controlled = false;
	PControlled(U) = false;
	Map_RemoveMovement(M, U);
}

void Command_ChangeUnit(MATRIKS *M, PLAYER *P, UNIT *U)
{
	Command_ReleaseUnit(M, P, U);
	int N, i=1;
	addressU addr = First(PListUnit(P));

	printf("== List of Unit(s) ==\n");
	while(addr != Nil) {
		printf("%d. ", i);
		Player_PrintUnit(Unit(addr));
		i++;
		addr = Next(addr);
	}
	
	printf("Please enter the no. of unit you want to select : ");
	scanf("%d", &N);

	addr = First(PListUnit(P));
	i = 1;
	while (i < N) {
		addr = Next(addr);
		i++;
	}

	printf("You are now selecting ");
	if(Unit(addr).Type == 'K'){
		printf("King.\n");
	} else if(Unit(addr).Type == 'A') {
		printf("Archer.\n");
	} else if(Unit(addr).Type == 'S') {
		printf("Swordsman.\n");
	} else if(Unit(addr).Type == 'W') {
		printf("White Mage.\n");
	}
	printf("\n");
	*U = Unit(addr);
}

void Command_ControlUnit(MATRIKS *M, UNIT *U)
{
	int X = PLocationX(U);
	int Y = PLocationY(U);

	PElmt(M,X,Y).Unit.Controlled = true;
	PControlled(U) = true;
	
	Map_ShowMovement(M, PElmt(M,X,Y).Unit, POwner(U));
}

void Command_ReplenishUnitMovement(MATRIKS *M, PLAYER *P)
{
	Player_ReplenishMovement(P);
	int X,Y;
	addressU addr = First(PListUnit(P));

	while(addr != Nil){
		X = LocationX(Unit(addr));
		Y = LocationY(Unit(addr));

		PElmt(M,X,Y).Unit.Movement = Movement(Unit(addr));

		addr = Next(addr);
	}
}

void Command_UpdateUnitPosition(PLAYER *P, UNIT *U, int X, int Y)
{
    addressU addr = ListU_SearchUnit(PListUnit(P),*U);

    if(addr == Nil){
        printf("addr nil\n");
    } else {
        LocationX(Unit(addr)) = X;
        LocationY(Unit(addr)) = Y;
    }
}


void Command_EndTurn(MATRIKS *M, PLAYER *P, UNIT *U)
{
	Map_RemoveMovement(M,U);
	Command_ReleaseUnit(M,P,U);
	printf("\n");
}

void Command_Input(MATRIKS *M, PLAYER *P, TERRAIN *T, boolean *finalstate)
{
	ListT_CheckandDelete(&PListVillage(P), *T);
	Player_IncreaseMoney(P);
	Player_DecreaseMoney(P);
	Command_ReplenishUnitMovement(M,P);

	Stack S;
	char command[50];
	int clrscr;
	UNIT U = Unit(First(PListUnit(P)));

	for(;;){
		printf("-------------------------------------\n\n");
		Command_ControlUnit(M, &U);
		Player_PrintTurn(*P, U);
		printf("Your Input : ");
		scanf("%s", &command);

		if(strcmp("MOVE",command) == 0) {
			Command_Move(M,P,&U,&S,T);
		} else if(strcmp("RECRUIT",command) == 0) {
			Command_Recruit(M, P, U);
		} else if(strcmp("INFO", command) == 0) {
			Command_Info(*M);
		} else if(strcmp("MAP", command) == 0) {
			Map_Print(*M);
		} else if(strcmp("CHANGE_UNIT", command) == 0) {
			Command_ChangeUnit(M, P, &U);
		} else if(strcmp("END_TURN", command) == 0) {
			Command_EndTurn(M, P, &U);
			Map_ClearScreen();
			break;
		} else if(strcmp("EXIT", command) == 0) {
			exit(0);
		}

		printf("Clear the screen?(1/0) : "); scanf("%d", &clrscr);
		if(clrscr == 1){
			Map_ClearScreen();
		}
	}
}
