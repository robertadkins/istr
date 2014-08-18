#include "istr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("SYNTAX: %s <a> <b>\n", argv[0]);
		return -1;
	}

	int l;

	istr *i = str_to_istr(argv[1], 10000);
	istr *j = str_to_istr(argv[2], 10000);

	printf("%110s\n", istr_to_str(i));
	printf("^ %108s\n", istr_to_str(j));

	for(l = 0; l < 22; l++) {
		printf("-----");
	}

	j = istr_pow(i, j);
	printf("\n%110s\n", istr_to_str(j));

	istr_destroy(i);
	istr_destroy(j);

	return 0;
}
