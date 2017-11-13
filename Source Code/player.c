#include <stdio.h>
#include "boolean.h"
#include "player.h"
#include "queue.h"
#include "listdp.h"

PLAYER Player_Init(int Order)
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */
{
	PLAYER P;
	P.Unit = ListU_CreateEmpty(P.Unit);
	P.Village = ListT_CreateEmpty(P.Village);
	P.Number = Order;
	P.Gold = 100;
	P.Income = 0;
	P.Upkeep = 0;

	if(Order == 1) { /* Pemain urutan 1 */
		P.Color = 'M'; /* Warna Merah */
	}
	else if(Order == 2) { /* Pemain urutan 2 */
		P.Color = 'B'; /* Warna Biru */
	}
	else if(Order == 3) { /* Pemain urutan 3 */
		P.Color = 'K'; /* Warna Kuning */
	}
	else if(Order == 4) { /* Pemain urutan 2 */
		P.Color = 'H'; /* Warna Hijau */
	}

	return P;
}

void Player_PrintTurn(PLAYER P, char *Player_Input){
	printf("Player %d's Turn\n", P.Number);
	printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", P.Gold, P.Income, P.Upkeep);
	Player_PrintUnit(P.Unit);
	printf("Your Input : "); scanf("%s",&Player_Input);
}

void Player_PrintUnit(ListU L){	
	if(!ListU_IsEmpty(L)){
		address P = First(L);
		
		while(P != Nil){
			printf("Unit : ");
			if(Unit(P).Type == 'K'){
				printf("King");
			} else if (Unit(P).Type == 'A') {
				printf("Archer");
			} else if (Unit(P).Type == 'S') {
				printf("Swordsman");
			} else if (Unit(P).Type == 'W') {
				printf("White Mage");
			}
			printf(" (%d,%d) ", Unit(P).Location.X, Unit(P).Location.Y);
			printf(" | ");
			printf("Health : %d/%d", Unit(P).Health, Unit(P).Max_Health);
			printf(" | ");
			printf("Movement Point : %d", Unit(P).Movement);
			printf("Can Attack : ");

			if(Unit(P).Attack_Chance == true){
				printf("yes\n");
			}
			else {
				printf("no\n");
			}


			P = Next(P);
		}
	}
}

boolean Player_Lose(PLAYER P)
/* Menghasilkan true jika player P sudah kalah */
/* Kalah = Raja milik Player mati */
/* Digunakan untuk menghapus elemen player dari queue */
{
	address found = ListU_SearchType(P.Unit, 'K');
	
	if(found == Nil){
		return true;
	}
	else {
		return false;
	}
}