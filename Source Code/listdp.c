/* Nama : Shandy */
/* NIM  : 13516097 */

#include "listdp.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean ListU_IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
    return ( (First(L) == Nil) && (Last(L) == Nil) );
}

/****************** PEMBUATAN LIST KOSONG ******************/
void ListU_CreateEmpty (List *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
    First(*L) = Nil;
    Last(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address ListU_Alokasi (UNIT X)
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

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address ListU_SearchType (ListU L, char type)
/* Mencari apakah ada elemen list dengan P.Unit,Type=type */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean found = false;
    address found_add = Nil;
    address P = First(L);

    if (!ListU_IsEmpty(L)){

        do{
            if (P.Unit.Type == X){
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
/* Mencari apakah ada elemen list dengan Unit(P)=U */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    boolean found = false;
    address found_add = Nil;
    address P = First(L);

    if (!ListU_IsEmpty(L)){

        do{
            if (Unit(P) == X){
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
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P = Alokasi(U);
    if (P != Nil){
        ListU_InsertLast(L, P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void ListU_DelUFirst (ListU *L, UNIT *U)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    ListU_DelFirst(L, &P);
    *U = Unit(P);
    ListU_Dealokasi(P);
}
void ListU_DelULast (List *L, UNIT *U)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    ListU_DelLast(L, &P);
    *U = Unit(P);
    ListU_Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void ListU_InsertFirst (List *L, address P)
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
void ListU_InsertLast (List *L, address P)
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

void ListU_InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list; P sudah dialokasi  */
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

void ListU_InsertBefore (List *L, address P, address Succ)
/* I.S. Succ pastilah elemen list; P sudah dialokasi  */
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
void ListU_DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = First(*L);
    First(*L) = Next(First(*L));
    if (First(*L) == Nil){  // if the new list doesnt have first element (possibly there was only 1 element)
        ListU_CreateEmpty(L);
    }
    else{
        Prev(First(*L)) = Nil;
    }
}

void ListU_DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
{
    *P = Last(*L);
    Last(*L) = Prev(Last(*L));
    if (Last(*L) == Nil){  // if the new list doesnt have last element (possibly there was only 1 element)
        ListU_CreateEmpty(L);
    }
    else{
        Next(Last(*L)) = Nil;
    }
}

void ListU_DelP (List *L, UNIT U)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
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
void ListU_DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
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

void ListU_DelBefore (List *L, address *Pdel, address Succ)
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/*      Pdel adalah alamat elemen list yang dihapus  */
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

/****************** PROSES SEMUA ELEMEN LIST ******************/
void ListU_PrintForward (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
    if (!ListU_IsEmpty(L)){

        address CP = First(L);

        do{

            printf("%d",Info(CP));

            CP = Next(CP);

            if (CP != Nil){ // last element no ','
                printf(",");
            }

        } while (CP != Nil);

    }

    printf("]");
}
void ListU_PrintBackward (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
    if (!ListU_IsEmpty(L)){

        address CP = Last(L);

        do{

            printf("%d",Info(CP));

            CP = Prev(CP);

            if (CP != Nil){ // last element no ','
                printf(",");
            }

        } while (CP != Nil);

    }

    printf("]");
}