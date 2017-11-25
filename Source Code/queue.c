#include "queue.h"

/*********** QUEUE *****************/
void Queue_CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
  (*Q).T = (int *) malloc((Max + 1) * sizeof(int));
  if ((*Q).T != NULL) {
    MaxEl(*Q) = Max;
    Head(*Q) = Nol;
    Tail(*Q) = Nol;
  } else /* alokasi gagal */ {
    MaxEl(*Q) = 0;
  }
}

boolean Queue_IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
  return ((Head(Q) == Nol) && Tail(Q) == Nol);
}

boolean Queue_IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
  return (Tail(Q) == (Head(Q) + MaxEl(Q) - 2) % MaxEl(Q) + 1);
}

int Queue_NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
  if (Queue_IsEmpty(Q)) {
    return 0;
  } else {
    return (Tail(Q) + MaxEl(Q) - Head(Q)) % MaxEl(Q) + 1;
  }
}

void Queue_DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
  free((*Q).T);
  MaxEl(*Q) = 0;
}

void Queue_Add (Queue * Q, int X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
  if (Queue_IsEmpty(*Q)) {
    Head(*Q) = 1;
    Tail(*Q) = 1;
  } else {
    Tail(*Q) = (Tail(*Q) % MaxEl(*Q)) + 1;
  }
  InfoTail(*Q) = X;
}

void Queue_Del (Queue * Q, int *X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = Nolai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
  *X = InfoHead(*Q);
  Head(*Q) = (Head(*Q) % MaxEl(*Q)) + 1;
  if (Head(*Q) == Tail(*Q) % MaxEl(*Q) + 1) {
  Head(*Q) = Nol;
  Tail(*Q) = Nol;
  }
}