/**************************** Definisi tipe ****************************/

typedef struct {
	UNIT Unit;
	TERRAIN Terrain;
} MAP_ELMT;

typedef struct {
	POINT Location;
	int Owner;
	char Type;
} TERRAIN;

/**************************** Fungsi dan Prosedur ****************************/

void Map_Init(MATRIKS *M, int baris, int kolom);
/* Membuat Map dengan baris x kolom */

void Map_ClearScreen();
/* Menghilangkan tampilan di Terminal */

void Map_Print(MATRIKS M);
/* Menampilkan matriks dalam bentuk peta ke layar */