/* NIM        : 13516097 */
/* Nama       : Shandy */
/* Topik      : ADT List Sirkuler dan Double Pointer */
/* Deskripsi  : Realisasi listsirkuler.c */

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listsirkuler.h"

/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
  return (First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  ElmtList* P = (ElmtList*) malloc(sizeof(ElmtList));

  if(P != Nil) { /* Alokasi berhasil */
    Info(P) = X;
    Next(P) = Nil;
    return P;
  } else { /* Alokasi gagal */
    return Nil;
  }
}

void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
  free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  boolean found = false;
  address P = First(L);
  address addfound = Nil;

  if(!IsEmpty(L)) {
    do {
      if(Info(P) == X) {
        addfound = P;
        found = true;
      } else
      {
        P = Next(P);
      }

    } while((found == false) && (P != First(L)) );
  }

  return addfound;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  address ins = Alokasi(X);
  if(ins != Nil){ /*alokasi berhasil */
    InsertFirst(&*L,ins);
  }
}

void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  address ins = Alokasi(X);
  if(ins != Nil){
    InsertLast(&*L,ins);
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype * X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  address del = First(*L);
  DelFirst(&*L, &del);
  *X = Info(del);
  Dealokasi(del);
}

void DelVLast (List *L, infotype * X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  address del = First(*L);
  while(Next(del) != First(*L)){
    del = Next(del);
  }
  DelLast(&*L,&del);
  *X = Info(del);
  Dealokasi(del);
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  if(IsEmpty(*L)){
    Next(P) = P;
  } else {
    address last = First(*L);
    while(Next(last) != First(*L)) {
      last = Next(last);
    } /* Next(last) = First(L) ==> elemen terkahir */
    Next(P) = First(*L);
    Next(last) = P;
  }
  First(*L) = P;
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  if(IsEmpty(*L)){
    InsertFirst(&*L, P);
  } else {
    address Last = First(*L);
    while(Next(Last) != First(*L)){
      Last = Next(Last);
    } /* Next(last) = First(L) */
    InsertAfter(&*L,P,Last);
  }
}

void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  *P = First(*L);
  if(Next(First(*L)) == First(*L)) { /* satu elemen */
    First(*L) = Nil;
  } else {
    address last = First(*L);
    while(Next(last) != First(*L)) {
      last = Next(last);
    } /* Next(last) = First(L) */
    First(*L) = Next(First(*L));
    Next(last) = First(*L);
  }
  Next(*P) = Nil;
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  address Last = First(*L);
  address PrecLast = Nil;

  while(Next(Last) != First(*L)) {
    PrecLast = Last;
    Last = Next(Last);
  }  /* Next(Last) = First(*L) */
  *P = Last;
  if(PrecLast == Nil) { /* kasus satu elemen */
    First(*L) = Nil;
  } else {
    Next(PrecLast) = First(*L);
  }
}

void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  *Pdel = Next(Prec);
  Next(Prec) = Next(Next(Prec));
  Next(*Pdel) = Nil;
}

void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
  address P = First(*L);
  address Pdel;
  boolean found = false;

  if(X == Info(P)){
    DelFirst(&*L,&P);
    Dealokasi(P);
  } else {
    while( (Next(P)!=First(*L)) && (found == false)){
      if(Info(Next(P)) == X){
        found = true;
      } else {
        P = Next(P);
      }
    }
  }

  if(found == true){
    Pdel = Next(P);
    DelAfter(&*L,&Pdel, P);
    Dealokasi(Pdel);
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  printf("[");

  if(!IsEmpty(L)){
    address P = First(L);

    while(Next(P) != First(L)) {
      printf("%d", Info(P));
      printf(",");
      P = Next(P);
    }
    printf("%d",Info(P));
  }

  printf("]");

}
