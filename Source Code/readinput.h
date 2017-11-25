#ifndef READINPUT_H
#define READINPUT_H

#include <stdio.h>
#include "boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"

void ReadInput();

Kata MOVE();

Kata UNDO();

Kata CHANGE_UNIT();

Kata RECRUIT();

Kata ATTACK();

Kata MAP();

Kata INFO();

Kata END_TURN();

Kata EXIT();

Kata DEBUG();

Kata NEXT_UNIT();

boolean IsKataSama(Kata Base);

#endif