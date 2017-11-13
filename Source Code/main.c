#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"
#include "boolean.h"
#include "listdp.h"
#include "queue.h"
#include "properties.h"

/* Untuk Map */
#define NotOwned 0
#define Empty ' '

/* untuk objek game */
#define Melee 1
#define Ranged 2

void Main_Menu(Matriks *M, )

void Main_Menu(MATRIKS *M, Queue *Q){
	
	int input, baris, kolom, banyak_pemain;
	int i;

	printf("Selamat datang di Battle of Olympia!\n");
	printf("1. New Game\n");
	printf("2. Load Game\n");
	printf("Input (1 atau 2 ) : "); scanf("%d", &input);

	while(input != 1 || input != 2){
		printf("Input salah! Ulangi input!\n");
		printf("Input (1 atau 2 ) : "); scanf("%d", &input);
	}

	if(input == 1){
		printf("Masukkan ukuran baris peta : ");scanf("%d",baris);
		printf("Masukkan ukuran kolom peta : ");scanf("%d",kolom);
		while( (baris<8) && (kolom<8) ){
			printf("Ukuran tidak diperbolehkan. Silahkan ulangi!\n");
			printf("Masukkan ukuran baris peta : ");scanf("%d",baris);
			printf("Masukkan ukuran kolom peta : ");scanf("%d",kolom);
		}
		MakeMATRIKS(baris,kolom,M);

		printf("Masukkan jumlah pemain : "); scanf("%d",&banyak_pemain);
		while(banyak_pemain>4){
			printf("Maksimal pemain 4 orang. Silahkan input kembali.");
			printf("Masukkan jumlah pemain : "); scanf("%d",&banyak_pemain);
		}
		CreateEmpty(Q,banyak_pemain);
		for(i=1;i<banyak_pemain+1;i++){
			Add(Q,i);
		}

	} else {
		/* LoadExternal(); */
	}
}


void Main_InitState(Matriks *M, int N)
/* N adalah jumlah pemain */
{
	int i;
	for (i=1;i<N+1;i++){
		if(i == 1){
			/* Buat Tower Player */
			*M[(*M.NBrsEff-1)][1].Terrain.Owner = i;
			*M[(*M.NBrsEff-1)][1].Terrain.Type = 'T';
			*M[(*M.NBrsEff-1)][1].Terrain.Location.X = 1;
			*M[(*M.NBrsEff-1)][1].Terrain.Location.Y = (*M.NBrsEff-1);

			/* Buat Castle yang adjacent dengan tower */
			Map_CreateAdjacentCastle(Matriks M, POINT M[(*M.NBrsEff-1)][1].Terrain.Location);
		}

		if(i == 2){
			/* Buat Tower Player */
			*M[(*M.NBrsEff-1)][1].Terrain.Owner = i;
			*M[(*M.NBrsEff-1)][1].Terrain.Type = 'T';
			*M[(*M.NBrsEff-1)][1].Terrain.Location.X = (*M.NKolEff-1);
			*M[(*M.NBrsEff-1)][1].Terrain.Location.Y = 1;

			/* Buat Castle yang adjacent dengan tower */
			Map_CreateAdjacentCastle(Matriks M, POINT M[(*M.NBrsEff-1)][1].Terrain.Location);
		}
	}
}

int main(){
	int ArrPlayer[5];
	
	Main_Menu(&M, &Q);
	Display_MAP();

	return 0;
}