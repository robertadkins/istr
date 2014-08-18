#include "../src/istr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("SYNTAX: %s <a> <b>\n", argv[0]);
		return -1;
	}

	int k, l;

	istr *i = str_to_istr(argv[1], 80);
	istr *j = str_to_istr(argv[2], 80);
	printf("%80s\n", istr_to_str(j));

	for(k = 0; k < 9; k++) {

		printf("x %78s\n", istr_to_str(i));
		for(l = 0; l < 16; l++) {
			printf("-----");
		}

		j = istr_mult(i, j);
		printf("\n%80s\n", istr_to_str(j));
	}

	istr_destroy(i);
	istr_destroy(j);

	return 0;
}
