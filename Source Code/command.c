#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

void Command_Move(MATRIKS *M, PLAYER P[], int idx, UNIT *U, Stack *S)
{
	addressU addrU;
	int AmountMove; /* menyimpan besar pergerakan unit */
	POINT Po; Po.X = PLocationX(U); Po.Y = PLocationY(U); /* Menyimpan posisi awal unit */
	int baris,kolom; /* Menyimpan posisi target unit */
	int IdxOpp = Player_IdxOpp(idx); /* IdxOpp = idx musuh */

	/* input posisi target */
	printf("Please enter cell's coordinate x y : ");
	scanf("%d %d", &kolom, &baris);

	/* cek apakah target termasuk daerah movement */
	if(PElmt(M,baris,kolom).Unit.Type != '#') { /* target tidak termasuk daerah movement */
		printf("You can't move there.\n");
	
	} else { /* target termasuk daerah movement */

		addrU = ListU_SearchUnit(ListUnit(P[idx]), *U);
		
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
		Command_UpdateUnitPosition(&P[idx], U, baris, kolom); /* ganti posisi di list */
		PLocationX(U) = baris; 
		PLocationY(U) = kolom;
		PElmt(M,baris,kolom).Unit = *U;
		
		/* Mengurangi jumlah movement unit setelah bergerak */
		PElmt(M,baris,kolom).Unit.Movement -= AmountMove; /* Hapus di matriks */
		PMovement(U) -= AmountMove; /* Hapus di unit */
		Movement(Unit(addrU)) -= AmountMove; /* Hapus di array player */

		/* Jika movement = 0, maka unit tidak bisa menyerang */
		if(PMovement(U) == 0){
			PElmt(M,baris,kolom).Unit.Attack_Chance = false;
			PAttackChance(U) = false;
			AttackChance(Unit(addrU)) = false;	
		}

		printf("You have successfully moved to (%d,%d)\n", kolom, baris);

		/* jika unit menduduki village, village diakuisisi dan movement unit -> 0 */
		if(PElmt(M,baris,kolom).Terrain.Type == 'V' && PElmt(M,baris,kolom).Terrain.Owner != idx) {
			
			/* Perubahan properties matriks */
			
			/* Insertion dan Deletion List */
			PElmt(M,baris,kolom).Terrain.Owner = idx; /* mengubah ownership village */
			ListT_InsVFirst(&ListVillage(P[idx]), PElmt(M,baris,kolom).Terrain); /* Insert village ke list village pemain */
			ListT_DelP(&ListVillage(P[IdxOpp]), PElmt(M,baris,kolom).Terrain); /* Menghapus village musuh dari list */
			
			/* Perubahan properties player */
			PElmt(M,baris,kolom).Unit.Movement = 0; /* Mengubah movement unit matriks -> 0 */
			
			/* Perubahan properties unit */
			PMovement(U) = 0; /* Mengubah movement unit list -> 0 */
		
			printf("You also have successfully acquire the village.\n");
		}

	}
	printf("\n");
}

void Command_Recruit(MATRIKS *M, PLAYER P[], int idx, UNIT U)
{
	int baris,kolom;
	POINT Po;
	int unit;
	char cont;
	boolean KinginTower = true;

	if(Type(U) == 'K'){
		if (LocationX(U) != Tower(P[idx]).X || LocationY(U) != Tower(P[idx]).Y) {
			printf("You can't recruit. Your king is not in the Tower.\n");
			KinginTower = false;
		} else {
			for(;;){
				printf("Enter Coordinate of empty castle : "); scanf("%d %d", &kolom, &baris);

				/* Cek kondisi Map pada koordinat yang dipilih */
				if(PElmt(M,baris,kolom).Terrain.Type != 'C') { /* Koordinat Input bukan castle */
					printf("That is not a castle!\n");
				} else { /* Koordinat input adalah castle */
					if(PElmt(M,baris,kolom).Terrain.Owner != Number(P[idx])){ /* Castle punya pemain lain */
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
		
		if (Gold(P[idx]) >= 4){
			printf("Enter No. of unit you want to recruit : "); scanf("%d", &unit);
			if(unit == 1){
				printf("You have recruited an archer!\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('A',Po, Number(P[idx]));
				PElmt(M,baris,kolom).Unit.Owner = Number(P[idx]);
				PElmt(M,baris,kolom).Unit.Movement = 0;
				Gold(P[idx]) = Gold(P[idx])-PElmt(M,baris,kolom).Unit.Price;
				Upkeep(P[idx]) = Upkeep(P[idx])+1;
				ListU_InsULast(&ListUnit(P[idx]), PElmt(M,baris,kolom).Unit);

			} else if(unit == 2){
				printf("You have recruited a Swordsman!\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('S',Po, Number(P[idx]));
				PElmt(M,baris,kolom).Unit.Owner = Number(P[idx]);
				PElmt(M,baris,kolom).Unit.Movement = 0;
				Gold(P[idx]) = Gold(P[idx])-PElmt(M,baris,kolom).Unit.Price;
				Upkeep(P[idx]) = Upkeep(P[idx])+1;
				ListU_InsULast(&ListUnit(P[idx]), PElmt(M,baris,kolom).Unit);
			
			} else if(unit == 3){
				printf("You have recruited a White Mage!\n");
				printf("Seems that you are a big spender heh?\n");
				PElmt(M,baris,kolom).Unit = Unit_Init('W',Po,Number(P[idx]));
				PElmt(M,baris,kolom).Unit.Owner = Number(P[idx]);
				PElmt(M,baris,kolom).Unit.Movement = 0;
				Gold(P[idx]) = Gold(P[idx])-PElmt(M,baris,kolom).Unit.Price;
				Upkeep(P[idx]) = Upkeep(P[idx])+1;
				ListU_InsULast(&ListUnit(P[idx]), PElmt(M,baris,kolom).Unit);
			}
		} else {
			printf("Your Gold is not enough to recruit any new member.\n");
		}
	}
	printf("\n");
}

void Command_Attack(MATRIKS *M, PLAYER P[], int idx, UNIT *U, boolean *finalstate)
{
	int X = PLocationX(U);
	int Y = PLocationY(U);
	int count = 0;
	ListU enemy; ListU_CreateEmpty(&enemy); /* menampung enemy yang adjacent */

	/* Cek musuh di adjacent, dan kalau ada, dimasukkan ke list */
	/* cek atas */
	if(PElmt(M,X,Y-1).Unit.Owner != 0 && PElmt(M,X,Y-1).Unit.Owner != Number(P[idx])) {
		count += 1; ListU_InsULast(&enemy, PElmt(M,X,Y-1).Unit);
	}
	/* cek bawah */
	if(PElmt(M,X,Y+1).Unit.Owner != 0 && PElmt(M,X,Y+1).Unit.Owner != Number(P[idx])) {
		count += 1; ListU_InsULast(&enemy, PElmt(M,X,Y+1).Unit);
	}
	/* cek kiri */
	if(PElmt(M,X-1,Y).Unit.Owner != 0 && PElmt(M,X-1,Y).Unit.Owner != Number(P[idx])) {
		count += 1; ListU_InsULast(&enemy, PElmt(M,X-1,Y).Unit);
	}
	/* cek kanan */
	if(PElmt(M,X+1,Y).Unit.Owner != 0 && PElmt(M,X+1,Y).Unit.Owner != Number(P[idx])) {
		count += 1; ListU_InsULast(&enemy, PElmt(M,X,Y).Unit);
	}

	if(count == 0) { /* tidak ada musuh yang adjacent */
		printf("You can't attack. There is no enemy nearby.\n");
	} else { /* ada musuh yang adjacent */
		printf("Enemy that you can attack : \n");
		/* Print enemy adjacent */
		addressU addrEnemy = First(enemy);
		int i = 1, InputEnemy;
		while(addrEnemy != Nil) {
			printf("%d. ", i);
			ListU_PrintEnemy(*U, Unit(addrEnemy));
			i++;
			addrEnemy = Next(addrEnemy);	
		}

		printf("Select enemy you want to attack : "); scanf("%d", &InputEnemy);
		/* pilih enemy yang diattack */
		addrEnemy = First(enemy);
		i = 1;
		while (i < InputEnemy) {
			addrEnemy = Next(addrEnemy);
			i++;
		}
		/* Melakukan penyerangan */
		Command_Battle(M,P,idx,U, &Unit(addrEnemy), finalstate);
	}
}

void Command_Battle(MATRIKS *M, PLAYER P[], int idx, UNIT *U1, UNIT *U2, boolean *finalstate)
/* Melakukan serangan antara Unit 1 dan Unit 2 */
/* U1 menyerang U2 */
/* Rumus serangan : U2.Health = U2.Health - U1.Attack */
/* Setelah U1 menyerang : */
/* Movement U1 -> 0 */
/* Attack chance U1 -> false */
/* Kalau tipe serangan sama, U2 akan melakukan counter */ 
{
  /* Attack dari U1 */
  /* cek apakah U1 bisa menyerang */
	int IdxOpp = Player_IdxOpp(idx);

	addressU addrU1 = ListU_SearchUnit(ListUnit(P[idx]), *U1);
	addressU addrU2 = ListU_SearchUnit(ListUnit(P[IdxOpp]), *U2); /* salah karena nilai U2 = U1 */


  if(PAttackChance(U1) == true) {
  	
  	/* simpan tempat untuk operasi matriks */
  	int X1 = PLocationX(U1);
  	int X2 = PLocationX(U2);
  	int Y1 = PLocationY(U1);
  	int Y2 = PLocationY(U2);

  	POINT Po1,Po2;
  	Po1.X = X1; Po1.Y = Y1;
  	Po2.X = X2; Po2.Y = Y2;

  	/* Operasi pengurangan health musuh */
  	PElmt(M,X2,Y2).Unit.Health -= Attack(Unit(addrU1)); 
    Health(Unit(addrU2)) -= Attack(Unit(addrU1));
    Map_RemoveMovement(M,&Unit(addrU1));
    PMovement(U1) = 0;
    PElmt(M,X1,Y1).Unit.Movement = 0;
    PAttackChance(U1) = false;

    printf("Enemy's ");
    Unit_PrintType(Type(Unit(addrU2)));
    printf(" is damaged by %d.\n", PAttack(U1));

    /* Counter dari U2 */
    if(Health(Unit(addrU2)) > 0){ /* U2 masih hidup */
      if(Type(Unit(addrU2)) != 'K') {  /* U2 adalah king */
        
        if(PAttackType(U1) == AttackType(Unit(addrU2))) {
        /* Tipe attack sama & Health H2 > 0 */
        /* U1 mendapat counter sebesar attack U2 */
          printf("Enemy's ");
          Unit_PrintType(Type(Unit(addrU2)));
          printf(" retaliates.\n");
          PHealth(U1) -= Attack(Unit(addrU2));
          Health(Unit(addrU1)) -= Attack(Unit(addrU2));
          PElmt(M,X1,Y1).Unit.Health -= PAttack(U1); 
          printf("Your ");
          Unit_PrintType(PType(U1));
          printf(" is damaged by %d.\n", Attack(Unit(addrU2)));  
        
          /* U1 mati terkena counter */
          if(PHealth(U1) <= 0) {
            char UnitType = PType(U1);
            ListU_DelP(&ListUnit(P[idx]), *U1);
            PElmt(M,X1,Y1).Unit = Unit_CreateEmpty(Po1);

            printf("Your ");
            Unit_PrintType(UnitType);
            printf(" is dead :(\n");
            Upkeep(P[idx]) -= 1;
          }
        }
        /* Tipe attack tidak sama tidak ada counter */
      }
      else {
        /* U2 adalah King */
        /* King selalu bisa counter */
        PHealth(U1) -= Attack(Unit(addrU2));
        Health(Unit(addrU1)) -= Attack(Unit(addrU2));
        PElmt(M,X1,Y1).Unit.Health -= Attack(Unit(addrU2));
        printf("Enemy's king retaliates.\n");
        printf("Your ");
        Unit_PrintType(Type(Unit(addrU1)));
        printf(" is damaged by %d. \n", Attack(Unit(addrU2)));

        /* U1 mati terkena counter */
        if(PHealth(U1) <= 0) {
          char UnitType = PType(U1);
          ListU_DelP(&ListUnit(P[idx]),*U1);
          PElmt(M,X1,Y1).Unit = Unit_CreateEmpty(Po1);

          printf("Your ");
          Unit_PrintType(UnitType);
          printf(" is dead :(\n");
          Upkeep(P[idx]) -= 1;
        }
      }
    }
    else { /* U2 sudah mati */
      char EnemyType = Type(Unit(addrU2));
      ListU_DelP(&ListUnit(P[IdxOpp]), Unit(addrU2));
      PElmt(M,X2,Y2).Unit = Unit_CreateEmpty(Po2);

      printf("Enemy's ");
      Unit_PrintType(EnemyType);
      printf(" is dead :)\n");
      Upkeep(P[IdxOpp]) -= 1;
    }
  }
  else {
    printf("You can't attack.\n");
  }
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

void Command_ChangeUnit(MATRIKS *M, PLAYER P[], int idx, UNIT *U)
{
	Command_ReleaseUnit(M, P, U);
	int N, i=1;
	addressU addr = First(ListUnit(P[idx]));

	printf("== List of Unit(s) ==\n");
	while(addr != Nil) {
		printf("%d. ", i);
		Player_PrintUnit(Unit(addr));
		i++;
		addr = Next(addr);
	}
	
	printf("Please enter the no. of unit you want to select : ");
	scanf("%d", &N);

	addr = First(ListUnit(P[idx]));
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

void Command_ReplenishUnitMovement(MATRIKS *M, PLAYER *P, int idx)
{
	Player_ReplenishMovement(P, idx);
	int X,Y;
	addressU addr = First(ListUnit(P[idx]));

	while(addr != Nil){
		X = LocationX(Unit(addr));
		Y = LocationY(Unit(addr));

		PElmt(M,X,Y).Unit.Movement = Movement(Unit(addr));

		addr = Next(addr);
	}
}

void Command_UpdateUnitPosition(PLAYER *P, UNIT *U, int X, int Y)
{
    addressU addr = ListU_SearchUnit(PListUnit(P),*U); /* search unit */

    if(addr == Nil){
        printf("addr nil\n");
    } else {
        LocationX(Unit(addr)) = X;
        LocationY(Unit(addr)) = Y;
    }
}


void Command_EndTurn(MATRIKS *M, PLAYER *P, UNIT *U)
{
	Map_RemoveMovement(M,U); /* Hapus # dari map */
	Command_ReleaseUnit(M,P,U); /* ubah boolean controlled jadi false */
	printf("\n");
}

void Command_Debug(MATRIKS *M, PLAYER P[], UNIT U)
{
	int idx;
	char command[50];

	printf("idx pemain :"); scanf("%d", &idx);
	printf("Komponen yang ingin dicari : "); scanf("%s", &command);

	if(strcmp(command, "ListUnit") == 0) {
		printf("List Unit player %d : \n", idx);
		addressU addrU = First(ListUnit(P[idx]));
		while(addrU!=Nil) {
			Player_PrintUnit(Unit(addrU));
			addrU=Next(addrU);
		}
	}
	else if(strcmp(command, "ListVillage") == 0) {
		printf("List Unit player %d : \n", idx);
		addressT addrT = First(ListVillage(P[idx]));
		while(addrT!=Nil) {
			Map_PrintVillage(Terrain(addrT));
			addrT=Next(addrT);
		}	
	}
	else if(strcmp(command, "Player") == 0) {
		printf("Info Player %d : \n", idx);
		Player_PrintTurnDebug(P,U,idx);

	}
}


void Command_Input(MATRIKS *M, PLAYER P[], int idx, boolean *finalstate)
{
	Player_IncreaseMoney(P,idx);
	Player_DecreaseMoney(P,idx);
	Command_ReplenishUnitMovement(M,P,idx);

	Stack S;
	char command[50];
	int clrscr;
	UNIT U = Unit(First(ListUnit(P[idx])));

	for(;;){
		printf("-------------------------------------\n\n");
		Command_ControlUnit(M, &U);
		Player_PrintTurn(P, U, idx);
		printf("Your Input : ");
		scanf("%s", &command);

		if(strcmp("MOVE",command) == 0) {
			Command_Move(M,P,idx,&U,&S);
		} else if(strcmp("RECRUIT",command) == 0) {
			Command_Recruit(M, P, idx, U);
		} else if(strcmp("ATTACK",command) == 0) {
			Command_Attack(M, P, idx, &U, finalstate);
		} else if(strcmp("INFO", command) == 0) {
			Command_Info(*M);
		} else if(strcmp("MAP", command) == 0) {
			Map_Print(*M);
		} else if(strcmp("CHANGE_UNIT", command) == 0) {
			Command_ChangeUnit(M, P, idx, &U);
		} else if(strcmp("END_TURN", command) == 0) {
			Command_EndTurn(M, P, &U);
			Map_ClearScreen();
			break;
		} else if(strcmp("EXIT", command) == 0) {
			exit(0);
		} else if(strcmp("DEBUG", command) == 0) {
			Command_Debug(M, P, U);
		}

		printf("Clear the screen?(1/0) : "); scanf("%d", &clrscr);
		if(clrscr == 1){
			Map_ClearScreen();
		}
	}
}
