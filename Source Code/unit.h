#ifndef UNIT_H
#define UNIT_H

#include "globalconst.h"
#include "point.h"

/**************************** Definisi tipe Unit ****************************/

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

/************************* Fungsi dan Prosedur ********************************/

UNIT Unit_Init(char type, POINT P, int owner);
/* Mengirimkan stat awal untuk unit yang diinginkan berdasarkan parameter tipe, lokasi, dan pemilik */
/* Unit : King(K), Swordsman(S), Archer(A), WhiteMage(W) */

UNIT Unit_CreateEmpty();
/* Membuat Unit kosong */

void Unit_Battle(UNIT *U1, UNIT *U2);
/* Melakukan serangan antara Unit 1 dan Unit 2 */
/* U1 menyerang U2 */
/* Rumus serangan : U2.Health = U2.Health - U1.Attack */
/* Setelah U1 menyerang :
	Movement U1 -> 0
	Attack chance U1 -> false
	Kalau tipe serangan sama, U2 akan melakukan counter
*/

void Unit_Heal(UNIT *U);
/* Meningkatkan Health untuk unit-unit yang berada adjacent dengan White Mage */
/* Unit U = Unit yang akan di-heal */ 
/* Prosedur khusus untuk White Mage */


// void Unit_Lose(ListU *L, struct UNIT U);
/* Unit U mati karena Battle */
/* Unit U dihapus dari ListUnit Pemain */

#endif