#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "globalconst.h"
#include "boolean.h"
#include "listdp.h"


/**************************** Definisi tipe Player ****************************/

typedef struct {
	ListU Unit;
	ListT Village;
	int Number; /* Urutan player kayak di PS */
	int Gold;
	int Income;
	int Upkeep;
	char Color;	
} PLAYER;

/**************************** Fungsi dan Prosedur ****************************/
PLAYER Player_Init(int Order);
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */

void Player_PrintTurn(PLAYER P, char *Player_Input);
/* Menampilkan informasi singkat mengenai pemain saat turn-nya */

void Player_PrintUnit(ListU L);
/* Menampilkan unit-unit yang dimiliki player */

boolean Player_Lose(PLAYER P);
/* Menghasilkan true jika player P sudah kalah */
/* Kalah = Raja milik Player mati */
/* Digunakan untuk menghapus elemen player dari queue */

#endif