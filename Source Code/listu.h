#ifndef LISTU_H
#define LISTU_H

#include <stdio.h>
#include <stdlib.h>
#include "globalconst.h"
#include "boolean.h"
#include "unit.h"


/************************* Definisi tipe Listdp untuk Unit ************/


/******* Definisi List *************/
typedef struct tElmtlistU *addressU;
typedef struct tElmtlistU {
	UNIT unit;
	addressU next;
	addressU prev;
} ElmtListU;
	
typedef struct {
	addressU First;
	addressU Last;
} ListU;


/************************* Fungsi dan prosedur *************************/
void ListU_CreateEmpty (ListU *L);
/* I.S. L sembarang  */
/* F.S. Terbentuk ListU kosong. Lihat definisi di atas. */

boolean ListU_IsEmpty (ListU L);
/* Mengirim true jika ListU kosong. Lihat definisi di atas. */

addressU ListU_Alokasi (UNIT U);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P);=Nil, Prev(P);=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */

void ListU_Dealokasi (addressU P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

addressU ListU_SearchType (ListU L, char type);
/* Mencari apakah ada elemen ListU dengan P.Unit,Type=type */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

addressU ListU_SearchUnit (ListU L, UNIT U);
/* Mencari apakah ada elemen ListU dengan Unit(P);=U */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

void ListU_InsertBefore (ListU *L, addressU P, addressU Succ);
/* I.S. Succ pastilah elemen ListU; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */

void ListU_InsertAfter (ListU *L, addressU P, addressU Prec);
/* I.S. Prec pastilah elemen ListU; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void ListU_InsertFirst (ListU *L, addressU P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */

void ListU_InsertLast (ListU *L, addressU P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void ListU_InsUFirst (ListU *L, UNIT U);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void ListU_InsULast (ListU *L, UNIT U);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListU di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void ListU_DelAfter (ListU *L, addressU *Pdel, addressU Prec);
/* I.S. ListU tidak kosong. Prec adalah anggota ListU. */
/* F.S. Menghapus Next(Prec);: */
/*      Pdel adalah alamat elemen ListU yang dihapus  */

void ListU_DelBefore (ListU *L, addressU *Pdel, addressU Succ);
/* I.S. ListU tidak kosong. Succ adalah anggota ListU. */
/* F.S. Menghapus Prev(Succ);: */
/*      Pdel adalah alamat elemen ListU yang dihapus  */

void ListU_DelFirst (ListU *L, addressU *P);
/* I.S. ListU tidak kosong */
/* F.S. P adalah alamat elemen pertama ListU sebelum penghapusan */
/*      Elemen ListU berkurang satu (mungkin menjadi kosong); */
/* First element yg baru adalah suksesor elemen pertama yang lama */

void ListU_DelLast (ListU *L, addressU *P);
/* I.S. ListU tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListU sebelum penghapusan  */
/*      Elemen ListU berkurang satu (mungkin menjadi kosong); */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */

void ListU_DelP (ListU *L, UNIT U);
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListU beraddress P, dengan Info(P);=X  */
/* maka P dihapus dari ListU dan didealokasi */
/* Jika tidak ada elemen ListU dengan Info(P);=X, maka ListU tetap */
/* ListU mungkin menjadi kosong karena penghapusan */

void ListU_DelUFirst (ListU *L, UNIT *U);
/* I.S. ListU L tidak kosong  */
/* F.S. Elemen pertama ListU dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void ListU_DelULast (ListU *L, UNIT *U);
/* I.S. ListU tidak kosong */
/* F.S. Elemen terakhir ListU dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

#endif