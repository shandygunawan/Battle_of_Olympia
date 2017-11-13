#include "player.h"
#include "boolean.h"
#include "listdp.h"

void Player_Init(PLAYER *P, int Order)
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */
{
	*P.Unit = ListU_CreateEmpty(P.Unit);
	*P.Village = ListT_CreateEmpty(P.Village);
	*P.Number = Order;
	*P.Gold = 100;
	*P.Income = 0;
	*P.Upkeep = 0;

	if(Order == 1) { /* Pemain urutan 1 */
		*P.Color = 'M'; /* Warna Merah */
	}
	else if(Order == 2) { /* Pemain urutan 2 */
		*P.Color = 'B'; /* Warna Biru */
	}
	else if(Order == 3) { /* Pemain urutan 3 */
		*P.Color = 'K'; /* Warna Kuning */
	}
	else if(Order == 4) { /* Pemain urutan 2 */
		*P.Color = 'H'; /* Warna Hijau */
	}
}

void Player_PrintTurn(PLAYER P, *char Player_Input){
	printf("Player %d's Turn\n", P.Number);
	printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", P.Gold, P.Income, P.Upkeep);
	Player_PrintUnit(P.Unit);
	printf("Your Input : "); Scanf("%s",Player_Input);
}

void Player_PrintUnit(ListU L){	
	if(!ListU_IsEmpty(L)){
		address P = First(L);
		
		while(P != Nil){
			printf("Unit : ");
			if(Unit(P).type == 'K'){
				printf("King");
			} else if (Unit(P).type == 'A') {
				printf("Archer");
			} else if (Unit(P).type == 'S') {
				printf("Swordsman");
			} else if (Unit(P).type == 'W') {
				printf("White Mage");
			}
			printf(" (%d,%d) ", Unit(P).Location.X, Unit(P).Location.Y);
			printf(" | ");
			printf("Health : %d/%d", Unit(P).Health, Unit(P).Max_Health);
			printf(" | ");
			printf("Movement Point : %d", Unit(P).Movement);
			printf("Can Attack : ");*

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

boolean Player_Lose(Player P)
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