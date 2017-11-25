#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include "boolean.h"
#include "globalconst.h"

/************************ Definisi tipe POINT *********************/

typedef struct { 
	int X; /* absis   */
	int Y; /* ordinat */
} POINT;

/* Macro Point */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/************************ Fungsi dan Prosedur *********************/
POINT MakePOINT (int X, int Y);
/* Membentuk sebuah POINT dari komponen-komponennya */

void BacaPOINT (POINT * P);
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */

boolean EQPOINT (POINT P1, POINT P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */

POINT PlusDelta (POINT P, int deltaX, int deltaY);
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */

#endif