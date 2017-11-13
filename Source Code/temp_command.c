void Recruit(Player *P, MATRIKS *M, UNIT db){
	int baris, kolom, unit;
	char cont;
	POINT Po;

	for(;;){
		printf("Enter Coordinate of empty castle : "); scanf("%d %d", &baris, &kolom);

		/* Cek kondisi Map pada koordinat yang dipilih */
		if(*M[baris][kolom].Terrain.Type != 'C'){ /* Koordinat Input bukan castle */
			printf("That is not a castle!\n");
		} else { /* Koordinat input adalah castle */
			if(*M[baris][kolom].Terrain.Owner != *P.Number){ /* Castle punya pemain lain */
				printf("That is not your castle!\n")
			} else { /* Castle punya pemain */
				if(*M[baris][kolom].Unit.type != Empty) { /* ada unit di castle */
					printf("The Castle is occupied!\n");
				} else {
					break;
				}
			}
		}

	}
	Po.X = kolom;
	Po.Y = baris;

	/* Menampilkan list recruit yang bisa direkrut */
	for(;;){
		printf("=== List Of Recruits ===\n");
		printf("1. Archer | Health 20 | ATK 4 | DEF 1 | 5G\n");
		printf("2. Swordsman | Health 20 | ATK 3 | DEF 2 | 4G\n");
		printf("3. White Mage | Health 20 | ATK 2 | DEF 2 | 20G\n");
		
		if (*P.Gold >= 4){
			printf("Enter No. of unit you want to recruit : "); scan("%d", &unit);
			if(unit == 1){
				printf("You have recruited an archer!\n");
				*M[baris][kolom].Unit = Unit_Init('A',Po,*P.Number);
				*P.Gold = *P.Gold-5;
				ListU_InsULast(P.Unit, *M[baris][kolom].Unit);

			} else if(unit == 2){
				printf("You have recruited a Swordsman!\n");
				*M[baris][kolom].Unit = Unit_Init('S',Po,*P.Number);
				*M[baris][kolom].Unit.Owner : *P.Number;
				*P.Gold = *P.Gold-4;
				ListU_InsULast(P.Unit, *M[baris][kolom].Unit);
			
			} else if(unit == 3){
				printf("You have recruited a White Mage!\n");
				printf("Seems that you are a big spender heh?\n");
				*M[baris][kolom].Unit = Unit_Init('W',Po,*P.Number);
				*M[baris][kolom].Unit.Owner : *P.Number;
				*P.Gold = *P.Gold-10;
				ListU_InsULast(P.Unit, *M[baris][kolom].Unit);
			}
		} else {
			printf("Your Gold is not enough to recruit any new member.\n");
			break;
		}

		printf("Do you want to recruit another member?(y/n)\n");
		scanf("%c", &cont);
		if(cont == 'n'){
			break;
		}
	}
}