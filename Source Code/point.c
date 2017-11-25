#include "point.h"

/********************* POINT **********************/
POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;

	return P;
}

void BacaPOINT (POINT * P)
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk 
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2 
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
{
	int x, y;
	scanf("%d %d", &x, &y);

	*P = MakePOINT(x, y);
}

boolean EQPOINT (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	return ((Absis(P1) - Absis(P2)) == 0 && (Ordinat(P1) - Ordinat(P2)) == 0);
}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);
}
