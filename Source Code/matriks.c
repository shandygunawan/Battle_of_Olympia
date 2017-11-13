/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "boolean.h"
#include "stdio.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

typedef int indeks; /* indeks baris, kolom */
typedef int ElType; 
typedef struct { 
  ElType Mem[BrsMax+1][KolMax+1];
  int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
  int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
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
boolean EQ (MATRIKS M1, MATRIKS M2)
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

boolean NEQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
  return !EQ(M1, M2);
}

boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
  return !(NBrsEff(M1) != NBrsEff(M2) || NKolEff(M1) != NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
  return NBrsEff(M) * NKolEff(M);
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
  return NBrsEff(M) == NKolEff(M);
}

boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
  indeks i, j;
  boolean bSimetri = true;

  if (!IsBujurSangkar(M)) {
    return false;
  } else {
    i = GetFirstIdxBrs(M);
    while (bSimetri && IsIdxEff(M, i, GetFirstIdxKol(M))) {
      j = GetFirstIdxKol(M);
      while (bSimetri && IsIdxEff(M, i, j)) {
        if (Elmt(M, i, j) != Elmt(M, j, i)) {
          bSimetri = false;
        }
        j++;
      }
      i++;
    }

    return bSimetri;
  }
}

boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
{
  indeks i, j;
  boolean bSatuan = true;

  if (!IsBujurSangkar(M)) {
    return false;
  } else {
    i = GetFirstIdxBrs(M);
    while (bSatuan && IsIdxEff(M, i, GetFirstIdxKol(M))) {
      j = GetFirstIdxKol(M);
      while (bSatuan && IsIdxEff(M, i, j)) {
        if (i == j) {
          if (Elmt(M, i, j) != 1) { bSatuan = false; }
        } else {
          if (Elmt(M, i, j) != 0) { bSatuan = false; }
        }
        j++;
      }
      i++;
    }

    return bSatuan;
  }
}

boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
{
  indeks i, j;
  boolean bSparse = true;
  int minSparse = 0.05 * NBElmt(M);
  int cntNotNol = 0;

  i = GetFirstIdxBrs(M);
  while (bSparse && IsIdxEff(M, i, GetFirstIdxKol(M))) {
    j = GetFirstIdxKol(M);
    while (bSparse && IsIdxEff(M, i, j)) {
      if (Elmt(M, i, j) != 0) {
        cntNotNol++;
        bSparse = cntNotNol <= minSparse;
      }
      j++;
    }
    i++;
  }

  return bSparse;
}

MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
  return KaliKons(M, -1);
}

float Determinan (MATRIKS M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
  float det = 0;
  indeks i, i_M, j_M, i_temp, j_temp;
  MATRIKS temp;

  if (NBrsEff(M) == 1 && NKolEff(M) == 1) {
    return Elmt(M, GetFirstIdxBrs(M), GetFirstIdxKol(M));
  } else {
    for (i = GetFirstIdxKol(M); i <= GetLastIdxKol(M); i++) {
      MakeMATRIKS(NBrsEff(M)-1, NKolEff(M)-1, &temp);

      i_temp = BrsMin;
      i_M    = GetFirstIdxBrs(M) + 1;
      while (i_M <= GetLastIdxBrs(M)) {
        j_temp = KolMin;
        j_M    = GetFirstIdxKol(M);
        while(j_M <= GetLastIdxKol(M)) {
          if (j_M != i) {
            Elmt(temp, i_temp, j_temp) = Elmt(M, i_M, j_M);
            j_temp++;
          }
          j_M++;
        }
        i_M++;
        i_temp++;
      }

      if (i&1) {
        det += Elmt(M, GetFirstIdxBrs(M), i) * Determinan(temp);
      } else {
        det -= Elmt(M, GetFirstIdxBrs(M), i) * Determinan(temp);
      }
    }
    return det;
  }
}

void PInverse1 (MATRIKS * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
  CopyMATRIKS(Inverse1(*M), M);
}

void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujurSangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
  indeks i,j;
  MATRIKS MHsl;

  MakeMATRIKS(NBrsEff(*M), NKolEff(*M), &MHsl);
  for (i = GetFirstIdxBrs(*M); IsIdxEff(*M, i, GetFirstIdxKol(*M)); i++) {
    for (j = GetFirstIdxKol(*M); IsIdxEff(*M, i, j); j++) {
      Elmt(MHsl, i, j) = Elmt(*M, j, i);
    }
  }

  CopyMATRIKS(MHsl, M);

}

float RataBrs (MATRIKS M, indeks i)
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
{
	indeks j;
	float fRata = 0;
	
	for (j = GetFirstIdxKol(M); IsIdxEff(M, i, j); j++) {
		fRata += Elmt(M, i, j);
	}
	
	fRata /= NKolEff(M);
	
	return fRata;
}

float RataKol (MATRIKS M, indeks j)
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
{
	indeks i;
	float fRata = 0;
	
	for (i = GetFirstIdxBrs(M); IsIdxEff(M, i, j); i++) {
		fRata += Elmt(M, i, j);
	}
	
	fRata /= NBrsEff(M);
	
	return fRata;
}

void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min)
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
{
	indeks j;
	
	*max = Elmt(M, i, GetFirstIdxKol(M));
	*min = Elmt(M, i, GetFirstIdxKol(M));
	
	j = GetFirstIdxKol(M) + 1;
	while (IsIdxEff(M, i, j)) {
		if (Elmt(M, i, j) > *max) { *max = Elmt(M, i, j); }
		if (Elmt(M, i, j) < *min) { *min = Elmt(M, i, j); }
		j++;
	}
	
}

void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min)
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
{
	indeks i;
	
	*max = Elmt(M, GetFirstIdxBrs(M), j);
	*min = Elmt(M, GetFirstIdxBrs(M), j);
	
	i = GetFirstIdxBrs(M) + 1;
	while (IsIdxEff(M, i, j)) {
		if (Elmt(M, i, j) > *max) { *max = Elmt(M, i, j); }
		if (Elmt(M, i, j) < *min) { *min = Elmt(M, i, j); }
		i++;
	}
	
}

int CountXBrs (MATRIKS M, indeks i, ElType X)
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
{
	indeks j;
	int count = 0;
	
	for (j = GetFirstIdxKol(M); IsIdxEff(M, i, j); j++) {
		if (Elmt(M, i, j) == X) { count++; }
	}
	
	return count;
}

int CountXKol (MATRIKS M, indeks j, ElType X)
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
{
	indeks i;
	int count = 0;
	
	for (i = GetFirstIdxBrs(M); IsIdxEff(M, i, j); i++) {
		if (Elmt(M, i, j) == X) { count++; }
	}
	
	return count;
}


#endif