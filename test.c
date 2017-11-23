#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int i, neff = 0;
	char toreadstring[] = "\t shandy gunawan";
	char* strArray[100];
	char *token = strtok(toreadstring, " \t");

	while(token!=NULL) {
		strArray[neff] = token;
		token = strtok(NULL, " \t");
		neff++;
	}

	for(i=0;i<neff;i++){
		printf("%s\n", strArray[i]);
	}

	return 0;
}