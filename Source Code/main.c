#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "globalconst.h"
#include "pcolor.h"
#include "stackt.h"
#include "point.h"
#include "unit.h"
#include "listu.h"
#include "matriks.h"
#include "listt.h"
#include "player.h"
#include "queue.h"
#include "command.h"

void Main_InitState(MATRIKS *M, PLAYER P[])
/* N adalah jumlah pemain */
{
	int i;
    POINT location;
    CreateEmptyMatriks(M);
    
    for(i=1;i<3;i++) {
        P[i] = Player_Init(i);
        if(i == 1){
            /* Buat Tower Player */
            M->Mem[(M->NKolEff-2)][1].Terrain.Owner = i;
            M->Mem[(M->NKolEff-2)][1].Terrain.Type = 'T';
            M->Mem[(M->NKolEff-2)][1].Terrain.Location.X = (M->NKolEff-2);
            M->Mem[(M->NKolEff-2)][1].Terrain.Location.Y = 1;
            location = M->Mem[(M->NKolEff-2)][1].Terrain.Location;
            Tower(P[i]) = location;
            /* Buat Castle yang adjacent dengan tower */
            /* Point yang dijadikan parameter adalah lokasi tower player */
            Map_CreateAdjacentCastle(M, location, i);
            
            /* Buat king */
            M->Mem[(M->NKolEff-2)][1].Unit = Unit_Init('K', location, i);
            M->Mem[(M->NKolEff-2)][1].Unit.Controlled = true;
            ListU_InsULast(&ListUnit(P[i]), M->Mem[(M->NKolEff-2)][1].Unit);
        }


        if(i == 2){
            /* Buat Tower Player */
            M->Mem[1][(M->NBrsEff-2)].Terrain.Owner = i;
            M->Mem[1][(M->NBrsEff-2)].Terrain.Type = 'T';
            M->Mem[1][(M->NBrsEff-2)].Terrain.Location.X = 1;
            M->Mem[1][(M->NBrsEff-2)].Terrain.Location.Y = (M->NBrsEff-2);
            location = M->Mem[1][(M->NBrsEff-2)].Terrain.Location;
            Tower(P[i]) = location;
            /* Buat Castle yang adjacent dengan tower */
            /* Point yang dijadikan parameter adalah lokasi tower player */
            Map_CreateAdjacentCastle(M, location, i);

            /* Buat king */
            M->Mem[1][(M->NBrsEff-2)].Unit = Unit_Init('K', location, i);
            ListU_InsULast(&ListUnit(P[i]), M->Mem[1][(M->NBrsEff-2)].Unit);
        }
    }
    Map_SpawnVillage(M);
}

void Main_PlayingState(MATRIKS *M, PLAYER P[])
{
    int idx;
    boolean finalstate = false;
    Queue Q;
    Queue_CreateEmpty(&Q,2); Queue_Add(&Q,1); Queue_Add(&Q,2);

    for(;;) {
        Queue_Del(&Q, &idx);
        Command_Input(M, P, idx, &finalstate);
        if(finalstate == true){
            break;
        } else {
            Queue_Add(&Q, idx);
        }
    }
}

void Main_FinalState() {
    printf("Game Over!\n");
    exit(0);
}

int main() {
	MATRIKS M;
	PLAYER P[3];

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
    printf("\n");
	Map_Init(&M);
    printf("\n");
	Main_InitState(&M, P);
    Map_ClearScreen();
    Main_PlayingState(&M, P);
    
}


/* DRIVER */
/*
int main() {
    int baris, kolom;
    Map_Init(&M);
    Main_InitState(&M, &Q);
    Map_Print(M);

    printf("-------Terrain owner-------\n")
    printf("baris : "); scanf("%d",&baris);
    printf("baris : "); scanf("%d",&kolom);
}
*/