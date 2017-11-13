/* #ifndef POINT_H */
/* #define POINT_H */

#include "stdio.h"
#include "boolean.h"
#include "point.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.14159265
#define rad(X) X*PI/180.0

/* typedef struct { */
/* 	float X; /* absis   */
/* 	float Y; /* ordinat */
/* } POINT; */

/* *** Notasi Akses: Selektor POINT *** */
/* #define Absis(P) (P).X */
/* #define Ordinat(P) (P).Y */
        
/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{
	POINT P;
	Absis(P) = X;
	Ordinat(P) = Y;

	return P;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
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

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                
{
	printf("(%d,%d)", Absis(P), Ordinat(P));
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQPOINT (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{
	return ((Absis(P1) - Absis(P2)) == 0 && (Ordinat(P1) - Ordinat(P2)) == 0);
}

boolean NEQPOINT (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{
	return ((Absis(P1) - Absis(P2)) != 0 || (Ordinat(P1) - Ordinat(P2)) != 0);
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P)
/* Menghasilkan true jika P adalah titik origin */
{
	return EQ(P, MakePOINT(0,0));
}

boolean IsOnSbX (POINT P)
/* Menghasilkan true jika P terletak Pada sumbu X */
{
	return (Ordinat(P) == 0);
}

boolean IsOnSbY (POINT P)
/* Menghasilkan true jika P terletak pada sumbu Y */
{
	return (Absis(P) == 0);
}

int Kuadran (POINT P)
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
{
	if (Absis(P) > 0 && Ordinat(P) > 0) { return 1; }
	if (Absis(P) < 0 && Ordinat(P) > 0) { return 2; }
	if (Absis(P) < 0 && Ordinat(P) < 0) { return 3; }
	if (Absis(P) > 0 && Ordinat(P) < 0) { return 4; }
	return -1;
}


/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */              
{
	return MakePOINT(Absis(P) + 1, Ordinat(P));
}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{
	return MakePOINT(Absis(P), Ordinat(P) + 1);
}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{
	return MakePOINT(Absis(P) + deltaX, Ordinat(P) + deltaY);
}

POINT MirrorOf (POINT P, boolean SbX)
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
{
	if (SbX) { return MakePOINT(     Absis(P), -1 * Ordinat(P)); } 
	else     { return MakePOINT(-1 * Absis(P),      Ordinat(P)); }
}

float Jarak0 (POINT P)
/* Menghitung jarak P ke (0,0) */
{
	return Panjang(P, MakePOINT(0,0));
}

float Panjang (POINT P1, POINT P2)
/* Menghitung jarak titik P1 dan P2 */
{
	return sqrt((Absis(P1) - Absis(P2))*(Absis(P1) - Absis(P2)) + (Ordinat(P1) - Ordinat(P2))*(Ordinat(P1) - Ordinat(P2)));
}

void Geser (POINT *P, int deltaX, int deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	Absis(*P) += deltaX;
	Ordinat(*P) += deltaY;
}

void GeserKeSbX (POINT *P)
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
{
	Ordinat(*P) = 0;
}

void GeserKeSbY (POINT *P)
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
{
	Absis(*P) = 0;
}

void Mirror (POINT *P, boolean SbX)
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
{
	if (SbX) { Ordinat(*P) *= -1; }
	else     { Absis(*P) *= -1; }
}

void Putar (POINT *P, float Sudut)
/* I.S. P terdefinisi */
/* F.S. P digeser sebesar Sudut derajat dengan sumbu titik (0,0) */
{
	float x = Absis(*P);
	float y = Ordinat(*P);

	Absis(*P)   = x * cos(rad(-1 * Sudut)) - y * sin(rad(-1 * Sudut));
	Ordinat(*P) = x * sin(rad(-1 * Sudut)) + y * cos(rad(-1 * Sudut));
}
