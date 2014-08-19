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


#ifndef _istr_h
#define _istr_h

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

typedef struct istr {
	char *num;
	int size;
	int max_size;
} istr;

// istr construction / destruction methods
istr *istr_create(int max_size);
istr *int_to_istr(int num, int max_size);
istr *str_to_istr(char *str, int max_size);
istr *istr_copy(istr *i);
void istr_destroy(istr *i);

char *istr_to_str(istr *i);
void set_digit(istr *i, int d, char val);
char get_digit(istr *i, int d);

// istr operations
istr *istr_add(istr *a, istr *b);
istr *istr_sub(istr *a, istr *b);
istr *istr_mult(istr *a, istr *b);
istr *istr_div(istr *a, istr *b);

istr *istr_mod(istr *a, istr *b);
istr *istr_pow(istr *a, istr *b);

#endif
