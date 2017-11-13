#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include "globalconst.h"
#include "point.h"
#include "unit.h"

/**************************** Definisi tipe ****************************/
typedef struct {
	POINT Location;
	int Owner;
	char Type;
} TERRAIN;

typedef struct MAP_ELMT {
	UNIT Unit;
	TERRAIN Terrain;
} MAP_ELMT;

/**************************** Fungsi dan Prosedur ****************************/

/************* Operasi Map ***********/
void Map_Init(MATRIKS *M, int baris, int kolom);
/* Membuat Map dengan baris x kolom */

void Map_ClearScreen();
/* Menghilangkan tampilan di Terminal */

void Map_Print(MATRIKS M);
/* Menampilkan matriks dalam bentuk peta ke layar */


/************* Operasi Castle ***********/
TERRAIN Map_CreateCastle(POINT P, int Owner);
/* Membuat Castle pada map */
/* Point di parameter menunjukkan lokasi Castle akan dibuat */

void Map_CreateAdjacentCastle(MATRIKS *M, POINT P, int Owner);
/* Membuat Castle yang adjacent dengan tower player */
/* Point Po menunjukkan lokasi Tower */
/* Dipakai di initial state */


/************* Operasi Village ***********/

void MAP_AcquiateVillage(UNIT *U, TERRAIN *V);
/* Unit mengakuisisi village yang satu petak dengan unit tersebut */
/* Setelah akuisisi :
	Owner Village = Owner Unit
	Movement Unit = 0
*/

/* void Map_SpawnVillage(MATRIKS *M); */
/* Menciptakan Village secara random pada map */

/* TERRAIN Map_CreateVillage(Point P); */
/* Membuat village pada map */
/* Point P menunjukkan lokasi village */

#endif