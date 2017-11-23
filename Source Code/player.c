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

void Player_PrintTurn(PLAYER P[], UNIT U, int idx)
{
  int income = 5*ListT_NBElmt(ListVillage(P[idx]));

  printf("Player %d's Turn\n", Number(P[idx]));
  printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", Gold(P[idx]), income, Upkeep(P[idx]));
  Player_PrintUnit(U);
  printf("\n");
}

void Player_PrintTurnDebug(PLAYER P[], UNIT U, int idx)
{

  int income = 5*ListT_NBElmt(ListVillage(P[idx]));
  int upkeep = ListU_NBElmt(ListUnit(P[idx]))-1;

  printf("Player %d's Turn\n", Number(P[idx]));
  printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", Gold(P[idx]), income, upkeep);
  printf("\n");
}

int Player_IdxOpp(int idx)
/* Menghasilkan index untuk musuh */
{
  if(idx == 1){
    return 2;
  } else if(idx == 2) {
    return 1;
  }
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

void Player_IncreaseMoney(PLAYER P[], int idx)
/* Menambah uang player sesuai jumlah village yang diakuisisi */
{
  int amount = 5*ListT_NBElmt(ListVillage(P[idx]));
  Gold(P[idx]) = Gold(P[idx])+amount;
}


void Player_DecreaseMoney(PLAYER P[], int idx)
/* Mengurangi uang player sesuai jumlah unit yang dimiliki */
{
    Gold(P[idx]) = Gold(P[idx])-Upkeep(P[idx]);
}

void Player_ReplenishMovement(PLAYER P[], int idx)
/* Mengembalikan nilai movement unit ke nilai awal */
{
  addressU addr = First(ListUnit(P[idx]));
  UNIT U;

  while(addr != Nil) {
    if(Unit(addr).Type == 'K') {
      Unit(addr).Movement = 1;
    } else if(Unit(addr).Type == 'A') {
      Unit(addr).Movement = 2;
    } else if(Unit(addr).Type == 'S') {
      Unit(addr).Movement = 4;
    } else if(Unit(addr).Type == 'W') {
      Unit(addr).Movement = 2;
    }
    Unit(addr).Attack_Chance = true;
    addr = Next(addr);
  }
}
