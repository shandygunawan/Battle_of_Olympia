#include "matriks.h"

/*********** Matriks *****************/
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
  (*M).NBrsEff = NB;
  (*M).NKolEff = NK;
}

void CreateEmptyMatriks(MATRIKS *M)
/* Inisialisasi semua elemen matriks dengan nilai-nilai kosong*/
{
  int i,j;
  POINT P;

  for(i=0;i<NBrsEff(*M);i++) {
    for(j=0;j<NKolEff(*M);j++) {
      P.X = i;
      P.Y = j;
      PElmt(M,i,j).Unit = Unit_CreateEmpty(P);
      PElmt(M,i,j).Terrain = Map_CreateEmptyTerrain(P);
    }
  }
}


boolean IsIdxEff (MATRIKS M, int i, int j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
  return (i >= BrsMin) && (i <= (NBrsEff(M) + BrsMin - 1) ) && (j >= KolMin) && (j <= (NKolEff(M) + KolMin - 1));
}

/*********** MAP *****************/
void Map_Init(MATRIKS *M)
/* Membuat Map dengan baris x kolom */
{
  int baris, kolom;
  printf("Pilih ukuran map yang anda inginkan, minimal 8x8.\n");
  printf("Baris : "); scanf("%d", &baris);
  printf("Kolom : "); scanf("%d", &kolom);

  MakeMATRIKS(baris, kolom, M);
}

void Map_ClearScreen()
/* Menghilangkan tampilan di Terminal */
{
  system("clear");
}

void Map_Print(MATRIKS M)
/* Menampilkan matriks dalam bentuk peta ke layar */
{
  	int i,j;
    int idxWriter=5,cR=0,cC=0,idxCol=-1,idxRow=-1,cCN=0,cN=0;
    printf("\n       "); /* Spasi untuk nomor atas */

    for (i=0;i<NKolEff(M);i++)
    {
        /* Spasi nomor atas */
        if(i<9)
        {
            printf("%d   ",i);
        }
        else
        {
            printf("%d  ",i);
        }
    }
    printf("\n");
    printf("  ");
    for (i=0;i<(5+4*(NBrsEff(M)-1));i++)
    {
      if(i%4==0)
      {
          idxRow++;
          cR=0;
      }
      for (j=-1;j<(5+4*(NKolEff(M)-1));j++)
      {

          cC++;
          /* Print nomor atas */
          if(j==-1)
          {
              if(cR==2)
              {
                  /* Nomor baris */
                  printf("%d",idxRow);
                  if(idxRow<10){
                    printf("  ");
                  } else {
                    printf(" ");
                  }
              }
              else
              {
                  printf("   ");
              }
          }
          else
          {
              /* Print Elemen Matriks */
              if(j%4==0)
              {
                  idxCol++;
              }
              if(i%4==0||j%4==0)
              {
                  printf("*");
                  cC=0;
              }
              else
              {
                if(cR==1&&cC==2)
                {
                  if(Elmt(M,idxRow,idxCol).Terrain.Owner == 1){
                      print_red(Elmt(M,idxRow,idxCol).Terrain.Type);
                  } else if(Elmt(M,idxRow,idxCol).Terrain.Owner == 2){
                      print_blue(Elmt(M,idxRow,idxCol).Terrain.Type);
                  } else if(Elmt(M,idxRow,idxCol).Terrain.Owner == 3){
                      print_yellow(Elmt(M,idxRow,idxCol).Terrain.Type);
                  } else {
                      printf("%c",Elmt(M,idxRow,idxCol).Terrain.Type);
                  }
                }
                else if (cR==2&&cC==2)
                {
                  if(Elmt(M,idxRow,idxCol).Unit.Controlled == true){
                      print_green(Elmt(M,idxRow,idxCol).Unit.Type);
                  } else {
                    if(Elmt(M,idxRow,idxCol).Unit.Owner == 1) {
                        print_red(Elmt(M,idxRow,idxCol).Unit.Type);
                    } else if(Elmt(M,idxRow,idxCol).Unit.Owner == 2){
                        print_blue(Elmt(M,idxRow,idxCol).Unit.Type);
                    }
                    else {
                        printf("%c",Elmt(M,idxRow,idxCol).Unit.Type);
                    }
                  }
                }
                else {
                    printf(" ");
                }
              }
          }
      }
      printf("\n  ");
      cR++;
      idxCol=-1;
  }
  printf ("\n");
}

void Map_CreateCastle(MATRIKS *M, POINT P, int Owner)
/* Membuat Castle pada map */
/* Point di parameter menunjukkan lokasi Castle akan dibuat */
{
  int baris = P.X;
  int kolom = P.Y;

  M->Mem[baris][kolom].Terrain.Location.X = P.X;
  M->Mem[baris][kolom].Terrain.Location.Y = P.Y;
  M->Mem[baris][kolom].Terrain.Owner = Owner;
  M->Mem[baris][kolom].Terrain.Type = 'C';
}

void Map_CreateAdjacentCastle(MATRIKS *M, POINT Po, int Owner)
/* Membuat Castle yang adjacent dengan tower player */
/* Point Po menunjukkan lokasi Tower */
/* Dipakai di initial state */
{
  POINT atas,bawah,kiri,kanan;

  atas.X = Po.X;
  atas.Y = Po.Y-1;
  bawah.X = Po.X;
  bawah.Y = Po.Y+1;
  kiri.X = Po.X-1;
  kiri.Y = Po.Y;
  kanan.X = Po.X+1;
  kanan.Y = Po.Y;

  Map_CreateCastle(M, atas, Owner);
  Map_CreateCastle(M, bawah, Owner);
  Map_CreateCastle(M, kiri, Owner);
  Map_CreateCastle(M, kanan, Owner);
}

void Map_SpawnVillage(MATRIKS *M)
/* Membuat villages secara acak di map */
{
  int X, Y;
  boolean occupied = true;
  int i;

  for(i=0;i<3;i++){
    srand(time(NULL));
    do {
      X = rand() % NBrsEff(*M);
      Y = rand() % NKolEff(*M);

      if(PElmt(M,X,Y).Terrain.Owner == NotOwned) {
        occupied = false;
      }
    } while(occupied == true);

    PElmt(M,X,Y).Terrain.Owner = 3;
    PElmt(M,X,Y).Terrain.Type = 'V';
  }

}

void Map_AcquiateVillage(UNIT *U, TERRAIN *V)
/* Unit mengakuisisi village yang satu petak dengan unit tersebut */
{
  V->Owner = U->Owner;
  U->Movement = 0;
}

void Map_Heal(MATRIKS *M, POINT P, int N)
/* Meningkatkan health unit yang berada di Point P sebesar N */
{
  int X = P.X;
  int Y = P.Y;

  PElmt(M,X,Y).Unit.Health += N;
}

void Map_HealAdjacent(MATRIKS *M, POINT Po, int N)
/* Meningkatkan Health untuk unit-unit yang berada adjacent dengan White Mage */
/* Point P = Posisi White Mage, N = jumlah health yang diheal */ 
{
  POINT atas, bawah, kiri, kanan;

  atas.X = Po.X;
  atas.Y = Po.Y-1;
  bawah.X = Po.X;
  bawah.Y = Po.Y+1;
  kiri.X = Po.X-1;
  kiri.Y = Po.Y;
  kanan.X = Po.X+1;
  kanan.Y = Po.Y;

  Map_Heal(M, atas, N);
  Map_Heal(M, bawah, N);
  Map_Heal(M, kiri, N);
  Map_Heal(M, kanan, N);
}

TERRAIN Map_CreateEmptyTerrain(POINT P)
/* Membuat terrain kosong */
{
  TERRAIN T;
  T.Location.X = P.X;
  T.Location.Y = P.Y;
  T.Owner = 0;
  T.Type = ' ';

  return T;
}

void Map_ShowMovement(MATRIKS *M, UNIT U, int Owner)
/* Menunjukkan area pergerakan pemain ditandai dgn # */
{
  int i,x,y;

  x = LocationX(U);
  y = LocationY(U);

  /* print ke kanan */
  for(i=1;i<=Movement(U);i++) {
    if(x+i <= PNKolEff(M)) {
      if(PElmt(M,x+i,y).Unit.Type != ' '){
        if(Owner != PElmt(M,y,x+i).Unit.Owner) {
          break;
        }
      }
      else {
        PElmt(M,x+i,y).Unit.Type = '#';
      }
    }
    else {
      break;
    }
  }

  /* Print ke kiri */
  x = LocationX(U);
  for(i=1;i<=Movement(U);i++) {
    if(x-i >= 0) {
      if(PElmt(M,x-i,y).Unit.Type != ' '){
        if(Owner != PElmt(M,x-i,y).Unit.Owner) {
          break;
        }
      }
      else {
        PElmt(M,x-i,y).Unit.Type = '#';
      }
    }
    else {
      break;
    }
  }

  /* Print ke bawah */
  y = LocationY(U);
  for(i=1;i<=Movement(U);i++) {
    if(y+i <= PNBrsEff(M)) {
      if(PElmt(M,x,y+i).Unit.Type != ' ') {
        if(Owner != PElmt(M,x,y+i).Unit.Owner) {
          break;
        }
      } else {
        PElmt(M,x,y+i).Unit.Type = '#';
      }
    } else {
      break;
    }
  }
  
  y = LocationY(U);
  for(i=1;i<=Movement(U);i++) {
    if(y-i >= 0) {
      if(PElmt(M,x,y-i).Unit.Type != ' ') {
        if(Owner != PElmt(M,x,y-i).Unit.Owner) {
          break;
        }
      } else {
        PElmt(M,x,y-i).Unit.Type = '#';
      }
    } else {
      break;
    }
  }
}

void Map_RemoveMovement(MATRIKS *M, UNIT *U)
/* Menunjukkan area pergerakan pemain ditandai dgn # */
{
  int i,x,y;
  POINT P;

  x = PLocationX(U);
  y = PLocationY(U);

  /* print ke kanan */
  for(i=1;i<=PMovement(U);i++) {
    if(x+i <= PNKolEff(M)) {
      if(PElmt(M,x+i,y).Unit.Type == '#'){
        P.X = x+i; P.Y = y;
        PElmt(M,x+i,y).Unit = Unit_CreateEmpty(P);
      }
    }
  }

  /* Print ke kiri */
  x = PLocationX(U);
  for(i=1;i<=PMovement(U);i++) {
    if(x-i >= 0) {
      if(PElmt(M,x-i,y).Unit.Type == '#'){
        P.X = x-i; P.Y = y;
        PElmt(M,x-i,y).Unit = Unit_CreateEmpty(P);
      }
    }
  }

  /* Print ke bawah */
  y = PLocationY(U);
  for(i=1;i<=PMovement(U);i++) {
    if(y+i <= PNBrsEff(M)) {
      if(PElmt(M,x,y+i).Unit.Type == '#') {
        P.X = x; P.Y = y+i;
        PElmt(M,x,y+i).Unit = Unit_CreateEmpty(P);
      }
    }
  }
  
  y = PLocationY(U);
  for(i=1;i<=PMovement(U);i++) {
    if(y-i >= 0) {
      if(PElmt(M,x,y-i).Unit.Type == '#') {
        P.X = x; P.Y = y-i;
        PElmt(M,x,y-i).Unit = Unit_CreateEmpty(P);
      }
    }
  }
}