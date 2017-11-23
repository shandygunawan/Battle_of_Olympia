#ifndef LISTT_H
#define LISTT_H

#include "boolean.h"
#include "globalconst.h"
#include "matriks.h"

/*********************** DEFINISI LIST TERRAIN (List Sirkuler) **********/

typedef struct tElmtListT *addressT;
typedef struct tElmtListT {
	TERRAIN terrain;
	addressT next;
} ElmtListT;

typedef struct {
	addressT First;
} ListT;

/*********************** Fungsi dan Prosedur ***************************/
void ListT_CreateEmpty (ListT *L);
/* I.S. L sembarang */
/* F.S. Terbentuk ListT kosong. Lihat definisi di atas. */

boolean ListT_IsEmpty (ListT L);
/* Mengirim true jika ListT kosong. Lihat definisi di atas. */

addressT ListT_Alokasi (TERRAIN T);
/* Mengirimkan addressT hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressT tidak nil, dan misalnya */
/* menghasilkan P, maka P->info=X, P->next=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void ListT_Dealokasi (addressT P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressT P */

addressT ListT_SearchVillage (ListT L, TERRAIN V);
/* Mencari apakah ada elemen ListT dengan P->info= X */
/* Jika ada, mengirimkan addressT elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

void ListT_InsertFirst (ListT *L, addressT P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressT P sebagai elemen pertama */

void ListT_InsertAfter (ListT *L, addressT P, addressT Prec);
/* I.S. Prec pastilah elemen ListT dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void ListT_InsertLast (ListT *L, addressT P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void ListT_DelFirst (ListT *L, addressT *P);
/* I.S. ListT tidak kosong */
/* F.S. P adalah alamat elemen pertama ListT sebelum penghapusan */
/*      Elemen ListT berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */

void ListT_DelLast (ListT *L, addressT *P);
/* I.S. ListT tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListT sebelum penghapusan  */
/*      Elemen ListT berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */

void ListT_DelAfter (ListT *L, addressT *Pdel, addressT Prec);
/* I.S. ListT tidak kosong. Prec adalah anggota ListT  */
/* F.S. Menghapus Prec->next: */
/*      Pdel adalah alamat elemen ListT yang dihapus  */

void ListT_DelP (ListT *L, TERRAIN X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListT beraddressT P, dengan P->info=X  */
/* Maka P dihapus dari ListT dan di-dealokasi */
/* Jika tidak ada elemen ListT dengan P->info=X, maka ListT tetap */
/* ListT mungkin menjadi kosong karena penghapusan */

void ListT_InsVFirst (ListT *L, TERRAIN X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void ListT_InsVLast (ListT *L, TERRAIN X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListT di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void ListT_DelVFirst (ListT *L, TERRAIN * X);
/* I.S. ListT L tidak kosong  */
/* F.S. Elemen pertama ListT dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void ListT_DelVLast (ListT *L, TERRAIN * X);
/* I.S. ListT tidak kosong */
/* F.S. Elemen terakhir ListT dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

void ListT_CheckandDelete(ListT *L, ListT *Ldel);
/* Mencari Terrain di ListT L yang merupakan anggota dari Ldel */

int ListT_NBElmt(ListT L);
/* Menghasilkan jumlah elemen list */
#endif