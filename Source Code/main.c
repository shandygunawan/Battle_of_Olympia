#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"
#include "queue.h"
#include "map.h"

void Main_InitState(MATRIKS *M, int N)
/* N adalah jumlah pemain */
{
	int i;
	POINT location;

	for (i=1;i<N+1;i++){
		if(i == 1){
			/* Buat Tower Player */
			*M[1][(M->NBrsEff-1)].Terrain.Owner = i;
			*M[1][(M->NBrsEff-1)].Terrain.Type = 'T';
			*M[1][(M->NBrsEff-1)].Terrain.Location.X = 1;
			*M[1][(M->NBrsEff-1)].Terrain.Location.Y = (M->NBrsEff-1);
			location = *M[1][(M->NBrsEff-1)].Terrain.Location;
			/* Buat Castle yang adjacent dengan tower */
			/* Point yang dijadikan parameter adalah lokasi tower player */
			Map_CreateAdjacentCastle(M, location, i);
		}

		if(i == 2){
			/* Buat Tower Player */
			*M[(M->NKolEff-1)][1].Terrain.Owner = i;
			*M[(M->NKolEff-1)][1].Terrain.Type = 'T';
			*M[(M->NKolEff-1)][1].Terrain.Location.X = (M->NKolEff-1);
			*M[(M->NKolEff-1)][1].Terrain.Location.Y = 1;
			location = *M[(M->NKolEff-1)][1].Terrain.Location.Y;
			/* Buat Castle yang adjacent dengan tower */
			/* Point yang dijadikan parameter adalah lokasi tower player */
			Map_CreateAdjacentCastle(M, location, i);
		}
	}
}

int main(){
        MATRIKS M;
        Queue Q;

        int menu;
        int baris, kolom;
        char spasi;
        printf("****************************************************************************************************************\n");
        printf("****************************************************************************************************************\n");
        printf("**      WELCOME                                                                                               **\n");
        printf("**     /////////////////////////////////////////////////////////////////////////////////////////////////      **\n");
        printf("**   | |  ____   ____  _____ _____        ____    ___   ____    ___              _   _   ___     ____  | |    **\n");
        printf("**   | | |    | |    |   |     |   |     |       |   | |       |   | |    |   | | | | | |   | | |    | | |    **\n");
        printf("**   | | |====< |====|   |     |   |     |====   |   | |====   |   | |    |___| | |_| | |===/ | |====| | |    **\n");
        printf("**   | | |____/ |    |   |     |   |____ |____   |___| |       |___| |___   |   |     | |     | |    | | |    **\n");
        printf("**   | |                                                                                               | |    **\n");
        printf("**    //////////////////////////////////////////////////////////////////////////////////////////////////      **\n");
        printf("**                                                                                                            **\n");
        printf("**   __________________________________________________  _________________________________________________    **\n");
        printf("**  |                                                  ||                                                 |   **\n");
        printf("**  |   ABOUT                                          ||        CREATE BY                                |   **\n");
        printf("**  |   -----------                                    ||        ----------                               |   **\n");
        printf("**  |   Program ini ditujukan untuk menyelesaikan      ||     1. I PUTU EKA  SURYA A  (13516061)          |   **\n");
        printf("**  |	tugas besar IF2110 Algoritma dan Struktur      ||     2. IRFAN IHSANUL AMAL   (13516064)          |   **\n");
        printf("**  |   Data tahun 2017.                               ||     3. DINDA YORA ISLAMI    (13516067)          |   **\n");
        printf("**  |                                                  ||     4. SHANDY               (13516097)          |   **\n");
        printf("**  |__________________________________________________||_________________________________________________|   **\n");
        printf("**                                                                                                            **\n");
        printf("**                                                                                                            **\n");
        printf("****************************************************************************************************************\n\n");
        printf("Main Menu\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("Input Anda (Pilih 1 atau 2): ");
        scanf("%d",&menu);
        while (menu!=1 && menu!=2){
            printf("Input anda salah, anda belum bisa masuk ke dunia olympia, coba lagi ^v^\n");
            printf("Pilih 1 atau 2\n");
            printf("Main Menu\n");
            printf("1. New Game\n");
            printf("2. Load Game\n");
            printf("Input Anda : ");
            scanf("%d",&menu);
        }
        if (menu==1){
            Map_Init(&M);
            Player_InitQueue(&Q);
            Main_InitState(&M, 2);
            Map_Print(M);
        } else
        {
            LoadGame();
        }

        return 0;
}