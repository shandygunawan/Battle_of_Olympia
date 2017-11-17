#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "boolean.h"
#include "globalconst.h"
#include "listu.h"
#include "listt.h"

/********************* DEFINISI Tipe PLAYER **********************/

/* Definisi */
typedef struct {
	ListU Unit;
	ListT Village;
	POINT Tower;
	int Number; /* Urutan player kayak di PS */
	int Gold;
	int Income;
	int Upkeep;
	char Color;	
} PLAYER;

/* Macro PLAYER */
#define ListUnit(P) (P).Unit
#define ListVillage(P) (P).Village
#define Tower(P) (P).Tower
#define Number(P) (P).Number
#define Gold(P) (P).Gold
#define Income(P) (P).Income
#define Upkeep(P) (P).Upkeep
#define Color(P) (P).Color

#define PListUnit(P) (P)->Unit
#define PListVillage(P) (P)->Village
#define PTower(P) (P)->Tower
#define PNumber(P) (P)->Number
#define PGold(P) (P)->Gold
#define PIncome(P) (P)->Income
#define PUpkeep(P) (P)->Upkeep
#define PColor(P) (P)->Color

/********************* Fungsi dan Prosedur **********************/
PLAYER Player_Init(int Order);
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */

void Player_PrintUnit(ListU L);
/* Menampilkan Unit yang dimiliki Player */

void Player_PrintTurn(PLAYER P);
/* Menampilkan informasi mengenai Player saat turn Player yang bersangkutan */

boolean Player_Lose(PLAYER P);
/* Menghasilkan true jika player P sudah kalah */
/* Kalah = Raja milik Player mati */
/* Digunakan untuk menghapus elemen player dari queue */

#endif