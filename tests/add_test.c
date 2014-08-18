#include "../src/istr.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("SYNTAX: %s <a> <b>\n", argv[0]);
		return -1;
	}

	istr *i = str_to_istr(argv[1], 40);
	istr *j = str_to_istr(argv[2], 40);
	printf("%40s\n+ %38s\n", istr_to_str(i), istr_to_str(j));
	printf("----------------------------------------\n");
	printf("%40s\n", istr_to_str(istr_add(i, j)));

	istr_destroy(i);
	istr_destroy(j);

	return 0;
}
