#ifndef MATRIKS_H
#define MATRIKS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "boolean.h"
#include "globalconst.h"
#include "pcolor.h"
#include "point.h"
#include "unit.h"

/********************* Definisi Tipe Matriks *********************/

typedef struct {
	POINT Location;
	int Owner;
	char Type;
} TERRAIN;

typedef struct MAP_ELMT {
	UNIT Unit;
	TERRAIN Terrain;
} MAP_ELMT;

typedef struct { 
  MAP_ELMT Mem[BrsMax+1][KolMax+1];
  int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
  int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;

/* Macro Matriks */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define PNBrsEff(M) (M)->NBrsEff
#define PNKolEff(M) (M)->NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]
#define PElmt(M,i,j) (M)->Mem[(i)][(j)]

/********************* Fungsi dan Prosedur *********************/


/*************** Matriks *********************/
void MakeMATRIKS (int NB, int NK, MATRIKS * M);
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

void CreateEmptyMatriks(MATRIKS *M);
/* Inisialisasi semua elemen matriks dengan nilai-nilai kosong*/

boolean IsIdxEff (MATRIKS M, int i, int j);
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */


/*************** MAP *********************/
void Map_Init(MATRIKS *M);
/* Membuat Map dengan baris x kolom */

void Map_ClearScreen();
/* Menghilangkan tampilan di Terminal */

void Map_Print(MATRIKS M);
/* Menampilkan matriks dalam bentuk peta ke layar */

void Map_CreateCastle(MATRIKS *M, POINT P, int Owner);
/* Membuat Castle pada map */
/* Point di parameter menunjukkan lokasi Castle akan dibuat */

void Map_CreateAdjacentCastle(MATRIKS *M, POINT Po, int Owner);
/* Membuat Castle yang adjacent dengan tower player */
/* Point Po menunjukkan lokasi Tower */
/* Dipakai di initial state */

void Map_SpawnVillage(MATRIKS *M);
/* Membuat villages secara acak di map */

void Map_AcquiateVillage(UNIT *U, TERRAIN *V);
/* Unit mengakuisisi village yang satu petak dengan unit tersebut */

void Map_Heal(MATRIKS *M, POINT P, int N);
/* Meningkatkan health unit yang berada di Point P sebesar N */

void Map_HealAdjacent(MATRIKS *M, POINT P, int N);
/* Meningkatkan Health untuk unit-unit yang berada adjacent dengan White Mage */
/* Point P = Posisi White Mage, N = jumlah health yang diheal */ 

TERRAIN Map_CreateEmptyTerrain(POINT P);
/* Membuat terrain kosong */

void Map_ShowMovement(MATRIKS *M, UNIT U, int Owner);
/* Menunjukkan area pergerakan pemain ditandai dgn # */

void Map_RemoveMovement(MATRIKS *M, UNIT *U);
/* Menghapus # dari pergerakan unit */

#endif