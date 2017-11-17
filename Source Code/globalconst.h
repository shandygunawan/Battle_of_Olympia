/* Definisi konstanta global */

#ifndef GLOBALCONST_H
#define GLOBALCONST_H

/* Untuk Matriks */
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

/* Untuk List */
#define Nil NULL

/* Untuk Queue */
#define Nol 0

/* Untuk Map */
#define NotOwned 0
#define Empty ' '

/* untuk objek game */
#define Melee 1
#define Ranged 2


/* Macro List */
#define Unit(P) (P)->unit
#define Terrain(P) (P)->terrain
#define Next(P) (P)->next
#define Prev(P) (P)->prev
#define First(L) (L).First
#define Last(L) (L).Last


#endif