#include "listt.h"

/*********** List Village *****************/
void ListT_CreateEmpty (ListT *L)
/* I.S. L sembarang */
/* F.S. Terbentuk ListT kosong. Lihat definisi di atas. */
{
  First(*L) = Nil;
}

boolean ListT_IsEmpty (ListT L)
/* Mengirim true jika ListT kosong. Lihat definisi di atas. */
{
  return (First(L) == Nil);
}

addressT ListT_Alokasi (TERRAIN T)
/* Mengirimkan addressT hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressT tidak nil, dan misalnya */
/* menghasilkan P, maka P->info=X, P->next=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  ElmtListT* P = (ElmtListT*) malloc(sizeof(ElmtListT));

  if(P != Nil) { /* Alokasi berhasil */
    Terrain(P) = T;
    Next(P) = Nil;
    return P;
  } else { /* Alokasi gagal */
    return Nil;
  }
}

void ListT_Dealokasi (addressT P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressT P */
{
  free(P);
}

addressT ListT_SearchVillage (ListT L, TERRAIN V)
/* Mencari apakah ada elemen ListT dengan P->info= X */
/* Jika ada, mengirimkan addressT elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  boolean found = false;
  addressT P = First(L);
  addressT addfound = Nil;

  if(!ListT_IsEmpty(L)) {
    do {
      if( (Terrain(P).Location.X == V.Location.X) && (Terrain(P).Location.Y == V.Location.Y) && (Terrain(P).Type == V.Type) && (Terrain(P).Owner == V.Owner) ){
        addfound = P;
        found = true;
      } else
      {
        P = P->next;
      }

    } while((found == false) && (P != First(L)) );
  }
  return addfound;
}

void ListT_InsertFirst (ListT *L, addressT P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressT P sebagai elemen pertama */
{
  if(ListT_IsEmpty(*L)){
    Next(P) = P;
  } else {
    addressT last = L->First;
    while(Next(last) != L->First) {
      last = Next(last);
    } /* last->next = L->First ==> elemen terkahir */
    Next(P) = L->First;
    Next(last) = P;
  }
  L->First = P;
}

void ListT_InsertAfter (ListT *L, addressT P, addressT Prec)
/* I.S. Prec pastilah elemen ListT dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void ListT_InsertLast (ListT *L, addressT P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  if(ListT_IsEmpty(*L)){
    ListT_InsertFirst(&*L, P);
  } else {
    addressT Last = L->First;
    while(Last->next != L->First){
      Last = Next(Last);
    } /* last->next = L->First */
    ListT_InsertAfter(&*L,P,Last);
  }
}

void ListT_DelFirst (ListT *L, addressT *P)
/* I.S. ListT tidak kosong */
/* F.S. P adalah alamat elemen pertama ListT sebelum penghapusan */
/*      Elemen ListT berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  *P = L->First;
  if(Next(L->First) == L->First) { /* satu elemen */
    L->First = Nil;
  } else {
    addressT last = L->First;
    while(Next(last) != L->First) {
      last = Next(last);
    } /* last->next = L->First */
    L->First = Next(L->First);
    Next(last) = L->First;
  }
  Next(*P) = Nil;
}

void ListT_DelLast (ListT *L, addressT *P)
/* I.S. ListT tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListT sebelum penghapusan  */
/*      Elemen ListT berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  addressT Last = L->First;
  addressT PrecLast = Nil;

  while(Next(Last) != L->First) {
    PrecLast = Last;
    Last = Next(Last);
  }  /* last->next = L->First */
  *P = Last;
  if(PrecLast == Nil) { /* kasus satu elemen */
    L->First = Nil;
  } else {
    Next(PrecLast) = L->First;
  }
}

void ListT_DelAfter (ListT *L, addressT *Pdel, addressT Prec)
/* I.S. ListT tidak kosong. Prec adalah anggota ListT  */
/* F.S. Menghapus Prec->next: */
/*      Pdel adalah alamat elemen ListT yang dihapus  */
{
  *Pdel = Next(Prec);
  Next(Prec) = Next(Next(Prec));
  Next(*Pdel) = Nil;
}

void ListT_DelP (ListT *L, TERRAIN X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListT beraddressT P, dengan P->info=X  */
/* Maka P dihapus dari ListT dan di-dealokasi */
/* Jika tidak ada elemen ListT dengan P->info=X, maka ListT tetap */
/* ListT mungkin menjadi kosong karena penghapusan */
{
  addressT P = L->First;
  addressT Pdel;
  boolean found = false;

  if( (X.Location.X == P->terrain.Location.X) && (X.Location.Y == P->terrain.Location.Y) && (X.Owner == P->terrain.Owner) && (X.Type == P->terrain.Type) ){
    ListT_DelFirst(&*L,&P);
    ListT_Dealokasi(P);
  } else {
    while( (P->next!=L->First) && (found == false)){
      if((X.Location.X == (P->next)->terrain.Location.X) && (X.Location.Y == (P->next)->terrain.Location.Y) && (X.Owner == (P->next)->terrain.Owner) && (X.Type == (P->next)->terrain.Type) ) {
        found = true;
      } else {
        P = Next(P);
      }
    }
  }

  if(found == true){
    Pdel = Next(P);
    ListT_DelAfter(&*L,&Pdel, P);
    ListT_Dealokasi(Pdel);
  }
}

void ListT_InsVFirst (ListT *L, TERRAIN X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  addressT ins = ListT_Alokasi(X);
  if(ins != Nil){ /*alokasi berhasil */
    ListT_InsertFirst(&*L,ins);
  }
}

void ListT_InsVLast (ListT *L, TERRAIN X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListT di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  addressT ins = ListT_Alokasi(X);
  if(ins != Nil){
    ListT_InsertLast(&*L,ins);
  }
}

void ListT_DelVFirst (ListT *L, TERRAIN * X)
/* I.S. ListT L tidak kosong  */
/* F.S. Elemen pertama ListT dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  addressT del = L->First;
  ListT_DelFirst(&*L, &del);
  *X = Terrain(del);
  ListT_Dealokasi(del);
}

void ListT_DelVLast (ListT *L, TERRAIN * X)
/* I.S. ListT tidak kosong */
/* F.S. Elemen terakhir ListT dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  addressT del = L->First;
  while(del->next != L->First){
    del = Next(del);
  }
  ListT_DelLast(&*L,&del);
  *X = Terrain(del);
  ListT_Dealokasi(del);
}

void ListT_CheckandDelete(ListT *L, TERRAIN X)
/* Mencari terrain X di ListT L dan menghapusnya jika ada */
{
  addressT check = ListT_SearchVillage(*L, X);

  if(check != Nil) {
    ListT_DelP(L, X);
  }
}

int ListT_NBElmt(ListT L)
/* Menghasilkan jumlah elemen list */
{
  addressT P = First(L);
  int count = 0;

  while(P != Nil) {
    count++;
    P = Next(P);
  }
  return count;
}