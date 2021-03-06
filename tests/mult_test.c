/*
 The MIT License (MIT)
 
 Copyright (c) 2014 Robert Adkins
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


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
