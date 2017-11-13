/* Nama : Shandy */
/* NIM  : 13516097 */

#include "listdp.h"

/* PROTOTYPE */
/****************** TEST ListU KOSONG ******************/
boolean ListU_IsEmpty (ListU L)
/* Mengirim true jika ListU kosong. Lihat definisi di atas. */
{
    return ( (First(L) == Nil) && (Last(L) == Nil) );
}

/****************** PEMBUATAN ListU KOSONG ******************/
void ListU_CreateEmpty (ListU *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk ListU kosong. Lihat definisi di atas. */
{
    First(*L) = Nil;
    Last(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address ListU_Alokasi (UNIT U)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
    ElmtListU *P = (ElmtListU *) malloc(sizeof(ElmtListU));

    if (P != Nil){
        Unit(P) = U;
        Next(P) = Nil;
        Prev(P) = Nil;
        return P;
    }
    else {
        return Nil;
    }
}

void ListU_Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN ListU ******************/
address ListU_SearchType (ListU L, char type)
/* Mencari apakah ada elemen ListU dengan P.Unit,Type=type */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean found = false;
    address found_add = Nil;
    address P = First(L);

    if (!ListU_IsEmpty(L)){

        do{
            if (P.Unit.Type == type){
                found_add = P;
                found = true;
            }
            else{
                P = Next(P);
            }

        }while ((P != Nil) && !found);
    }

    return found_add;
}

address ListU_SearchUnit (ListU L, UNIT U)
/* Mencari apakah ada elemen ListU dengan Unit(P)=U */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean found = false;
    address found_add = Nil;
    address P = First(L);

    if (!ListU_IsEmpty(L)){

        do{
            if (Unit(P) == U){
                found_add = P;
                found = true;
            }
            else{
                P = Next(P);
            }

        }while ((P != Nil) && !found);
    }

    return found_add;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void ListU_InsUFirst (ListU *L, UNIT U)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address P = Alokasi(U);
    if (P != Nil){
        ListU_InsertFirst(L, P);
    }
}
void ListU_InsULast (ListU *L, infotype U)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListU di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P = Alokasi(U);
    if (P != Nil){
        ListU_InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void ListU_DelUFirst (ListU *L, UNIT *U)
/* I.S. ListU L tidak kosong  */
/* F.S. Elemen pertama ListU dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    ListU_DelFirst(L, &P);
    *U = Unit(P);
    ListU_Dealokasi(P);
}
void ListU_DelULast (ListU *L, UNIT *U)
/* I.S. ListU tidak kosong */
/* F.S. Elemen terakhir ListU dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    ListU_DelLast(L, &P);
    *U = Unit(P);
    ListU_Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void ListU_InsertFirst (ListU *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    if (!ListU_IsEmpty(*L))
        ListU_InsertBefore(L, P, First(*L));

    else{   // is empty, insert first element
        First(*L) = P;
        Last(*L) = P;
        Prev(P) = Nil;
        Next(P) = Nil;
    }
}
void ListU_InsertLast (ListU *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (!ListU_IsEmpty(*L))
        ListU_InsertAfter(L, P, Last(*L));

    else{   // is empty, insert first element

        First(*L) = P;
        Last(*L) = P;
        Prev(P) = Nil;
        Next(P) = Nil;
    }
}

void ListU_InsertAfter (ListU *L, address P, address Prec)
/* I.S. Prec pastilah elemen ListU; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P) = Next(Prec); // pointer P -> succ

    if (Next(Prec) != Nil){ // prec not last element
        Prev(Next(Prec)) = P;   // pointer succ -> P
    }
    else{ // Next prec is nil (prec is last element)
        Last(*L) = P;
    }

    Next(Prec) = P; // pointer prec -> P
    Prev(P) = Prec; // pointer P -> prec
}

void ListU_InsertBefore (ListU *L, address P, address Succ)
/* I.S. Succ pastilah elemen ListU; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
{
    Prev(P) = Prev(Succ); // pointer P -> prec

    if (Prev(Succ) != Nil){ // succ not first element
        Next(Prev(Succ)) = P;   // pointer prec -> P
    }
    else{ // prev succ is nil (succ is first element)
        First(*L) = P;
    }

    Prev(Succ) = P; // pointer succ -> P
    Next(P) = Succ; // pointer P -> succ
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void ListU_DelFirst (ListU *L, address *P)
/* I.S. ListU tidak kosong */
/* F.S. P adalah alamat elemen pertama ListU sebelum penghapusan */
/*      Elemen ListU berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = First(*L);
    First(*L) = Next(First(*L));
    if (First(*L) == Nil){  // if the new ListU doesnt have first element (possibly there was only 1 element)
        ListU_CreateEmpty(L);
    }
    else{
        Prev(First(*L)) = Nil;
    }
}

void ListU_DelLast (ListU *L, address *P)
/* I.S. ListU tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListU sebelum penghapusan  */
/*      Elemen ListU berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
{
    *P = Last(*L);
    Last(*L) = Prev(Last(*L));
    if (Last(*L) == Nil){  // if the new ListU doesnt have last element (possibly there was only 1 element)
        ListU_CreateEmpty(L);
    }
    else{
        Next(Last(*L)) = Nil;
    }
}

void ListU_DelP (ListU *L, UNIT U)
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListU beraddress P, dengan Info(P)=X  */
/* maka P dihapus dari ListU dan didealokasi */
/* Jika tidak ada elemen ListU dengan Info(P)=X, maka ListU tetap */
/* ListU mungkin menjadi kosong karena penghapusan */
{
    address P = ListU_SearchUnit(*L, U);

    if (P != Nil){

        if (Prev(P) != Nil) // if it's not first element
            ListU_DelAfter(L, P, Prev(P));

        else if (Next(P) != Nil)   // if it's first element
            ListU_DelBefore(L, P, Next(P));

        else // if deleted element is singular
            ListU_CreateEmpty(L);

        Dealokasi(P);
    }
}
void ListU_DelAfter (ListU *L, address *Pdel, address Prec)
/* I.S. ListU tidak kosong. Prec adalah anggota ListU. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen ListU yang dihapus  */
{
    *Pdel = Next(Prec);

    Next(Prec) = Next(*Pdel);        // prec -> succ
    if (Next(*Pdel) != Nil){         // deleted element is not last element
        Prev(Next(*Pdel)) = Prec;    // succ -> prec
    }
    else{                            // deleted is last
        Last(*L) = Prec;
    }

    Next(*Pdel) = Nil;
    Prev(*Pdel) = Nil;
}

void ListU_DelBefore (ListU *L, address *Pdel, address Succ)
/* I.S. ListU tidak kosong. Succ adalah anggota ListU. */
/* F.S. Menghapus Prev(Succ): */
/*      Pdel adalah alamat elemen ListU yang dihapus  */
{
    *Pdel = Prev(Succ);

    Prev(Succ) = Prev(*Pdel);       // succ -> prec
    if (Prev(*Pdel) != Nil){        // deleted element is not first element
        Next(Prev(*Pdel)) = Succ;   // prec -> succ
    }
    else {                          // deleted is first
        First(*L) = Succ;
    }

    Next(*Pdel) = Nil;
    Prev(*Pdel) = Nil;
}
