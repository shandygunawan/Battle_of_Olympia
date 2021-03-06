#include "boolean.h"
#include "stackt.h"

/* #define Nol 0 */
/* #define MaxEl 10 */
/* Nol adalah stack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

/* typedef int infotype; */
/* typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
/* typedef struct {  */
/*   infotype T[MaxEl+1]; /* tabel penyimpan elemen */
/*   address TOP;  /* alamat TOP: elemen puncak */
/* } Stack; */
/* Definisi stack S kosong : S.TOP = Nol */
/* Elemen yang dipakai menyimpan Nolai Stack T[1]..T[MaxEl] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
/* #define Top(S) (S).TOP */
/* #define InfoTop(S) (S).T[(S).TOP] */

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void Stack_CreateEmpty (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnyaa antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP berNolai Nol */
{
  Top(*S) = Nol;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean Stack_IsEmpty (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
  return (Top(S) == Nol);
}

boolean Stack_IsFull (Stack S)
/* Mengirim true jika tabel penampung Nolai elemen stack penuh */
 {
  return (Top(S) == MaxElStack);
 }

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Stack_Push (Stack * S, UNIT X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
  if (Stack_IsEmpty(*S)) {
    Top(*S) = 1;
  } else {
    Top(*S)++;
  }
  InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Stack_Pop (Stack * S, UNIT* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah Nolai elemen TOP yang lama, TOP berkurang 1 */
{
  *X = InfoTop(*S);
  Top(*S)--;
}