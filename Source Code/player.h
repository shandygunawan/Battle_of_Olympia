/**************************** Definisi tipe Player ****************************/

typedef struct {
	ListUnit Unit;
	ListVillage Village;
	int Number; /* Urutan player kayak di PS */
	int Gold;
	int Income;
	int Upkeep;
	char Color;	
} PLAYER;

/**************************** Fungsi dan Prosedur ****************************/

void Player_Init(PLAYER *P);
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */

void Player_PrintTurn(PLAYER P, *char Player_Input);
/* Menampilkan informasi singkat mengenai pemain saat turn-nya */

void Player_PrintUnit(ListU L);
/* Menampilkan unit-unit yang dimiliki player */

boolean Player_Lose(PLAYER P);
/* Menghasilkan true jika player P sudah kalah */
/* Kalah = Raja milik Player mati */
/* Digunakan untuk menghapus elemen player dari queue */