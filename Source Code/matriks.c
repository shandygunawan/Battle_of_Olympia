#include "matriks.h"

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
  (*M).NBrsEff = NB;
  (*M).NKolEff = NK;
}

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
  return (i >= BrsMin) && (i <= BrsMax) && (j >= KolMin) && (j <= KolMax);
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
  return BrsMin;
}

indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
  return KolMin;
}

indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
  return NBrsEff(M) + BrsMin - 1;
}

indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
  return NKolEff(M) + KolMin - 1;
}

boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
  return (i >= GetFirstIdxBrs(M)) && (i <= GetLastIdxBrs(M)) && (j >= GetFirstIdxKol(M)) && (j <= GetLastIdxKol(M));
}

ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
  return Elmt(M,i,i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
  indeks i,j;

  MakeMATRIKS(NBrsEff(MIn), NKolEff(MIn), MHsl);
  for (i = GetFirstIdxBrs(MIn); IsIdxEff(MIn, i, GetFirstIdxKol(MIn)); i++) {
    for (j = GetFirstIdxKol(MIn); IsIdxEff(MIn, i, j); j++) {
      Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
    }
  }

}

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
  indeks i,j;

  MakeMATRIKS(NB, NK, M);
  for (i = GetFirstIdxBrs(*M); IsIdxEff(*M, i, GetFirstIdxKol(*M)); i++) {
    for (j = GetFirstIdxKol(*M); IsIdxEff(*M, i, j); j++) {
      scanf("%d",&Elmt(*M, i, j));
    }
  }

}

void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
  indeks i,j;

  for (i = GetFirstIdxBrs(M); IsIdxEff(M, i, GetFirstIdxKol(M)); i++) {
    for (j = GetFirstIdxKol(M); IsIdxEff(M, i, j); j++) {
      printf("%d",Elmt(M, i, j));
      if (j == GetLastIdxKol(M)) {
        if (i != GetLastIdxBrs(M)) {
          printf("\n");
        }
      } else {
        printf(" ");
      }
    }
  }

}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
{
  indeks i,j;
  MATRIKS M3;

  MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &M3);
  for (i = GetFirstIdxBrs(M1); IsIdxEff(M1, i, GetFirstIdxKol(M1)); i++) {
    for (j = GetFirstIdxKol(M1); IsIdxEff(M1, i, j); j++) {
      Elmt(M3, i, j) = Elmt(M1, i, j) + Elmt(M2, i, j);
    }
  }

  return M3;
}

MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */ 
{
  indeks i,j;
  MATRIKS M3;

  MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &M3);
  for (i = GetFirstIdxBrs(M1); IsIdxEff(M1, i, GetFirstIdxKol(M1)); i++) {
    for (j = GetFirstIdxKol(M1); IsIdxEff(M1, i, j); j++) {
      Elmt(M3, i, j) = Elmt(M1, i, j) - Elmt(M2, i, j);
    }
  }

  return M3;

}

MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
  indeks i,j,k;
  MATRIKS M3;

  MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &M3);
  for (i = GetFirstIdxBrs(M1); i <= GetLastIdxBrs(M1); i++) {
    for (j = GetFirstIdxKol(M2); j <= GetLastIdxKol(M2); j++) {
      Elmt(M3, i, j) = 0;
      for (k = GetFirstIdxKol(M1); k <= GetLastIdxKol(M1); k++) {
        Elmt(M3, i, j) += Elmt(M1, i, k) * Elmt(M2, k, j);
      }
    }
  }

  return M3;
}

MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
  indeks i,j;
  MATRIKS MHsl;

  MakeMATRIKS(NBrsEff(M), NKolEff(M), &MHsl);
  for (i = GetFirstIdxBrs(M); IsIdxEff(M, i, GetFirstIdxKol(M)); i++) {
    for (j = GetFirstIdxKol(M); IsIdxEff(M, i, j); j++) {
      Elmt(MHsl, i, j) = Elmt(M, i, j) * X;
    }
  }

  return MHsl;
}
void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
  CopyMATRIKS(KaliKons(*M, K), M);
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
  indeks i, j;
  boolean bEQ = true;

  if (NBrsEff(M1) != NBrsEff(M2) || NKolEff(M1) != NKolEff(M2)) {
    return false;
  } else {
    i = GetFirstIdxBrs(M1);
    while (bEQ && IsIdxEff(M1, i, GetFirstIdxKol(M1))) {
      j = GetFirstIdxKol(M1);
      while (bEQ && IsIdxEff(M1, i, j)) {
        if (Elmt(M1, i, j) != Elmt(M2, i, j)) {
          bEQ = false;
        }
        j++;
      }
      i++;
    }

    return bEQ;
  }
}

boolean NEQMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
  return !EQ(M1, M2);
}

boolean EQSizeMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
  return !(NBrsEff(M1) != NBrsEff(M2) || NKolEff(M1) != NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmtMatriks (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
  return NBrsEff(M) * NKolEff(M);
}
