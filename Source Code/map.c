#include <stdio.h>
#include "map.h"
#include "boolean.h"


void Map_Init(MATRIKS *M, int baris, int kolom)
/* Membuat Map dengan baris x kolom */
{
	MakeMATRIKS(baris,kolom,M);
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

}