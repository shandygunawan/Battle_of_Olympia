#include <stdio.h>
#include <stdlib.h>
#include "readinput.h"

void ReadInput () {
    FILE * pita;
    Kata Input;
    int retval;

    scanf("%s", Input.TabKata);
    pita = fopen("pitakar.txt","w");
    retval = fprintf(pita,Input.TabKata);
    retval = fprintf(pita,".");
    fclose(pita);
    STARTKATA();
}

Kata MOVE() {
    Kata Base;

    Base.Length = 4;
    Base.TabKata[1] = 'M';
    Base.TabKata[2] = 'O';
    Base.TabKata[3] = 'V';
    Base.TabKata[4] = 'E';

    return Base;
}

Kata UNDO() {
    Kata Base;

    Base.Length = 4;
    Base.TabKata[1] = 'U';
    Base.TabKata[2] = 'N';
    Base.TabKata[3] = 'D';
    Base.TabKata[4] = 'O';

    return Base;
}

Kata CHANGE_UNIT() {
    Kata Base;

    Base.Length = 11;
    Base.TabKata[1] = 'C';
    Base.TabKata[2] = 'H';
    Base.TabKata[3] = 'A';
    Base.TabKata[4] = 'N';
    Base.TabKata[5] = 'G';
    Base.TabKata[6] = 'E';
    Base.TabKata[7] = '_';
    Base.TabKata[8] = 'U';
    Base.TabKata[9] = 'N';
    Base.TabKata[10] = 'I';
    Base.TabKata[11] = 'T';

    return Base;
}

Kata RECRUIT() {
    Kata Base;

    Base.Length = 7;
    Base.TabKata[1] = 'R';
    Base.TabKata[2] = 'E';
    Base.TabKata[3] = 'C';
    Base.TabKata[4] = 'R';
    Base.TabKata[5] = 'U';
    Base.TabKata[6] = 'I';
    Base.TabKata[7] = 'T';

    return Base;
}

Kata ATTACK() {
    Kata Base;

    Base.Length = 6;
    Base.TabKata[1] = 'A';
    Base.TabKata[2] = 'T';
    Base.TabKata[3] = 'T';
    Base.TabKata[4] = 'A';
    Base.TabKata[5] = 'C';
    Base.TabKata[6] = 'K';

    return Base;
}

Kata MAP() {
    Kata Base;

    Base.Length = 3;
    Base.TabKata[1] = 'M';
    Base.TabKata[2] = 'A';
    Base.TabKata[3] = 'P';

    return Base;
}

Kata INFO() {
    Kata Base;

    Base.Length = 4;
    Base.TabKata[1] = 'I';
    Base.TabKata[2] = 'N';
    Base.TabKata[3] = 'F';
    Base.TabKata[4] = 'O';

    return Base;
}

Kata END_TURN() {
    Kata Base;

    Base.Length = 8;
    Base.TabKata[1] = 'E';
    Base.TabKata[2] = 'N';
    Base.TabKata[3] = 'D';
    Base.TabKata[4] = '_';
    Base.TabKata[5] = 'T';
    Base.TabKata[6] = 'U';
    Base.TabKata[7] = 'R';
    Base.TabKata[8] = 'N';

    return Base;
}

Kata EXIT() {
    Kata Base;

    Base.Length = 4;
    Base.TabKata[1] = 'E';
    Base.TabKata[2] = 'X';
    Base.TabKata[3] = 'I';
    Base.TabKata[4] = 'T';

    return Base;
}

Kata DEBUG() {
    Kata Base;

    Base.Length = 5;
    Base.TabKata[1] = 'D';
    Base.TabKata[2] = 'E';
    Base.TabKata[3] = 'B';
    Base.TabKata[4] = 'U';
    Base.TabKata[5] = 'G';

    return Base;
}

Kata NEXT_UNIT() {
    Kata Base;

    Base.Length = 9;
    Base.TabKata[1] = 'N';
    Base.TabKata[2] = 'E';
    Base.TabKata[3] = 'X';
    Base.TabKata[4] = 'T';
    Base.TabKata[5] = '_';
    Base.TabKata[6] = 'U';
    Base.TabKata[7] = 'N';
    Base.TabKata[8] = 'I';
    Base.TabKata[9] = 'T';

    return Base;
}



boolean IsKataSama(Kata Base) {
    int i;

    if (CKata.Length != Base.Length) {
        return false;
    } else {
        i=1;
        while (i<=CKata.Length && CKata.TabKata[i]==Base.TabKata[i]) {
            i++;
        }
        if (i<=CKata.Length) {
            return false;
        } else {
            return true;
        }
    }
}
