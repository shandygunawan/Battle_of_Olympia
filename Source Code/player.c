#include "player.h"

/*********** PLAYER *****************/
PLAYER Player_Init(int Order)
/* Membuat player untuk game */
/* Order menunjukkan urutan pemain */
{
  PLAYER P;
  ListU_CreateEmpty(&P.Unit);
  ListT_CreateEmpty(&P.Village);
  P.Number = Order;
  P.Gold = 100;
  P.Income = 0;
  P.Upkeep = 0;
  return P;
}


void Player_PrintTurn(PLAYER P, UNIT U){
  printf("Player %d's Turn\n", P.Number);
  printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", P.Gold, P.Income, P.Upkeep);
  Player_PrintUnit(U);
  printf("\n");
}

boolean Player_Lose(PLAYER P)
/* Menghasilkan true jika player P sudah kalah */
/* Kalah = Raja milik Player mati */
/* Digunakan untuk menghapus elemen player dari queue */
{
  addressU found = ListU_SearchType(P.Unit, 'K');
  
  if(found == Nil){
    return true;
  }
  else {
    return false;
  }
}

void Player_IncreaseMoney(PLAYER *P)
/* Menambah uang player sesuai jumlah village yang diakuisisi */
{
  PGold(P) = PGold(P)+PIncome(P);
}


void Player_DecreaseMoney(PLAYER *P)
/* Mengurangi uang player sesuai jumlah unit yang dimiliki */
{
    PGold(P) = PGold(P)-PUpkeep(P);
}