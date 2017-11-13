#include "map.h"

void Map_Init(MATRIKS *M)
/* Membuat Map dengan baris x kolom */
{
	int baris, kolom;
	printf("Pilih ukuran map yang anda inginkan, minimal 8x8.\n");
	printf("Baris : "); scanf("%d", baris);
	printf("Kolom : "); scanf("%d", kolom);

	MakeMATRIKS(baris, kolom, M);
}

void Map_ClearScreen()
/* Menghilangkan tampilan di Terminal */
{
	char buf[1024];
	char *str;

	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	fputs(str, stdout);
}

void Map_Print(MATRIKS M)
/* Menampilkan matriks dalam bentuk peta ke layar */
{
	int a,b,i,j;
    int x,y;
    int p,s;
    int count=0;
    char c;

    Map_ClearScreen();
    a=(kolom*4)+1;//kolom m
    b=(baris*4)+2;//baris n
    x=3;p=0;
    for(i=0;i<b;i++){
        y=4;s=0;
        for (j=0;j<a;j++){
            if(i==0){
                if(j==y){
                    if(s!=kolom){
                        printf("%d",s);
                        s++;
                        if(s>10){
                           y=y+3;
                        } else{y=y+4;}
                    }

                } else {
                    count++;
                    if(count<=kolom){
                        printf("%c",M[p][s].Terrain.Type);
                    }else{
                        printf("%c",M[p][s].Unit.Type);
                    }
                    if (count==2*kolom){
                        count=0;
                    }
                }
            } else {
                if(j==0){
                    if(i==x){
                        printf("%d",p);
                        p++;
                        x=x+4;
                    } else {printf("  ");}
                }
                if(i%4==1|j%4==0){
                    printf("*");
                }
                else {
                    count++;
                    if(count<=kolom){
                        printf("%c",M[p][s].terrain.type);
                    }else{
                        printf("%c",M[p][s].unit.type);
                    }
                    if (count=2*kolom){
                        count=0;
                    }
                }
            }
            printf("\n");
        }
    }
}

TERRAIN Map_CreateCastle(POINT P, int Owner)
/* Membuat Castle pada map */
/* Point di parameter menunjukkan lokasi Castle akan dibuat */
{
	int kolom = P.X;
	int baris = P.Y;

	*M[baris][kolom].Terrain.Location.X = P.X;
	*M[baris][kolom].Terrain.Location.Y = P.Y;
	*M[baris][kolom].Terrain.Owner = Owner;
	*M[baris][kolom].Terrain.Type = 'C';
}

void Map_CreateAdjacentCastle(MATRIKS *M, POINT Po, int Owner)
/* Membuat Castle yang adjacent dengan tower player */
/* Point Po menunjukkan lokasi Tower */
/* Dipakai di initial state */
{
	POINT atas,bawah,kiri,kanan;

	atas.X = Po.X;
	atas.y = Po.Y-1;
	bawah.X = Po.X;
	bawah.Y = Po.Y+1;
	kiri.X = Po.X-1;
	kiri.Y = Po.Y;
	kanan.X = Po.X+1;
	kanan.Y = Po.Y;

	Map_CreateCastle(atas, owner);
	Map_CreateCastle(bawah, owner);
	Map_CreateCastle(kiri, owner);
	Map_CreateCastle(kanan, owner);
}

void Unit_AcquiateVillage(UNIT *U, TERRAIN *V)
/* Unit mengakuisisi village yang satu petak dengan unit tersebut */
{
    V->Owner = U->Owner;
    U->Movement = 0;
}