/* Nama	: Shandy */
/* NIM	: 13516097 */

#include <stdlib.h>
#include "boolean.h"
#include "stacklist.h"


/* Prototype manajemen memori */
void Alokasi (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
	*P = (ElmtStack*) malloc(sizeof(ElmtStack));

	if (*P != Nil){ /*Alokasi berhasil */
    	Info(*P) = X;
    	Next(*P) = Nil;
	} else { /*Alokasi tidak berhasil */
	    *P = Nil;
	}
}

void Dealokasi (address P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */ 
{
	free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK STACK ***************/
boolean IsEmpty (Stack S)
/* Mengirim true jika Stack kosong: Top(S) = Nil */
{
	return(Top(S) == Nil);
}

void CreateEmpty (Stack * S)
/* I.S. sembarang */ 
/* F.S. Membuat sebuah stack S yang kosong */
{
	Top(*S) = Nil;
}

void Push (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
	address ins;
	Alokasi(&ins, X);

	if(ins != Nil){
		Next(ins) = Top(*S);
		Top(*S) = ins; 
	}
}

void Pop (Stack * S, infotype * X)
/* Menghapus X dari Stack S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
	address del = Top(*S);

	*X = InfoTop(*S);
	Top(*S) = Next(Top(*S));

	Dealokasi(del);
}
