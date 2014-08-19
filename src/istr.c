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

#include "istr.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print an error to the console, end program.
 */
void err(char *err) {
	printf("[ERROR]: %s\n", err);
	exit(-1);
}

/**
 * create an istr from an integer
 */
istr *int_to_istr(int num, int max_size)
{
    // check for valid values
	if(num < 0 || max_size <= 0) {
		err("Invalid arguments for int_to_istr");
	}

	istr *i = malloc(sizeof(istr));
	i->num = calloc(max_size + 1, sizeof(char));
	i->max_size = max_size;
	int k, c = 0;

	i->num[max_size] = '\0';

    // init istr with zeros
	for(k = 0; k < max_size; k++) {
		i->num[k] = '0';
	}

    // fill in digits using the parameter
	while(num > 0) {
		i->num[max_size - c - 1] = num % 10 + '0';
		num /= 10;
		c++;
	}

	i->size = c;

	return i;
}

/**
 * create an empty istr of specified size
 */
istr *istr_create(int size)
{
	return int_to_istr(0, size);
}

/**
 * create a new istr identical in value to the given istr
 */
istr *istr_copy(istr *i)
{
    // check that pointer is set
	if(i == NULL) {
		err("Pointer to istr is invlalid.");
	}

	istr *ret = istr_create(i->max_size);
	ret->size = i->size;
	ret->max_size = i->max_size;

	int k;

    // copy over istr value
	for(k = 0; k < i->size; k++) {
		set_digit(ret, k, get_digit(i, k));
	}

	return ret;
}

/**
 * destroy an istr
 */
void istr_destroy(istr *i)
{
    // check that pointer is set
	if(i == NULL) {
		err("Pointer to istr is invalid.");
	}

	free(i->num);
	free(i);
}

/**
 * get the value of a digit at index d
 */
char get_digit(istr *i, int d)
{
    // check for valid input
	if(i == NULL || d < 0 || d > i->max_size) {
		err("Invalid arguments for get_digit.");
	}

	return i->num[i->max_size - d - 1];
}

/**
 * set the value of a digit at index d to be val
 */
void set_digit(istr *i, int d, char val)
{
	// check for valid input
	if(i == NULL || d < 0 || d >= i->max_size || val < '0' || val > '9') {
		err("Invalid arguments for set_digit.");
	}

	i->num[i->max_size - d - 1] = val;
}

/**
 * convert a c string to an istr
 */
istr *str_to_istr(char *str, int max_size)
{
    // check for valid c string pointer
	if(str == NULL) {
		err("NULL string argument for str_to_istr");
	}

	istr *ret = istr_create(max_size);

	int size = 0;
	char *tmp = str;

    // count number of digits
	while(*tmp != '\0') {
		tmp++;
		size++;
	}

	ret->size = size;
	int i;

    // copy over digits from c string to istr
	for(i = 0; i < size; i++) {
		set_digit(ret, i, str[size - i - 1]);
	}

	return ret;
}

/**
 * return a c string from an istr
 */
char *istr_to_str(istr *i)
{
    // check for valid istr pointer
	if(i == NULL) {
		err("NULL istr pointer argument for istr_to_str.");
	}

    // handle special case of size 0
	if(i->size == 0) {
		return "0";
	}

	return i->num + i->max_size - i->size;
}

/**
 * add two istr
 */
istr *istr_add(istr *a, istr *b)
{
    // check for valid istr pointers
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_add.");
	}

	istr *c = istr_create(max(a->max_size, b->max_size));
	int k;
	int big_size = max(a->size, b->size);
	int small_size = min(a->size, b->size);

    // perform manual addition, digit by digit
	for(k = 0; k < small_size; k++) {

		int remainder = 0;

		do {

			int added = get_digit(a, k) - '0' + get_digit(b, k) - '0' + remainder;
			set_digit(c, k, get_digit(c, k) + added % 10);
			remainder = added / 10;

			if(remainder != 0)
				k++;

		} while(remainder > 0);
	}

	istr *big;

	if(a->size > b->size) {
		big = a;
	}
	else {
		big = b;
	}
    
    // copy over remaining, unchanged digits of the longer istr
	for(k = k; k < big_size; k++) {

		set_digit(c, k, get_digit(big, k));
	}

	c->size = k;
	return c;
}

/**
 * subtract two istr
 */
istr *istr_sub(istr *a, istr *b)
{
    // check for valid istr pointers
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_sub.");
	}
    // check that end result will most likely be positive (doesn't handle same sized istr that are still invalid)
	if(a->size < b->size) {
		err("invalide operands to istr_sub.");
	}

	istr *a_cpy = istr_copy(a);

	istr *c = istr_create(max(a->max_size, b->max_size));
	int i;

    // iterate all digits
	for(i = 0; i < b->size; i++) {

		int sub = get_digit(a_cpy, i) - get_digit(b, i);

        //check to see if an extra 10 is needed from digit to the left
		if(sub < 0) {

			set_digit(c, i, get_digit(a_cpy, i) + 10 - get_digit(b, i) + '0');
			int d = 1;
			sub = get_digit(a_cpy, i + d) - 1 - '0';

            // carry over values to the right
			while(sub < 0) {

				set_digit(a_cpy, i + d, 9 + '0');
				d++;
				sub = get_digit(a_cpy, i + d) - 1 - '0';
			}

			set_digit(a_cpy, i + d, sub + '0');
		}
		else {
			set_digit(c, i, sub + '0');
		}
	}
    
    //copy over digits
	for(i = b->size; i < a_cpy->size; i++) {
		set_digit(c, i, get_digit(a_cpy, i));
	}

    // find size of resulting value
	for(i = 0; c->num[i] == '0'; i++) {}

	c->size = c->max_size - i;
	istr_destroy(a_cpy);
	return c;
}

/**
 * multiply two istr
 */
istr *istr_mult(istr *a, istr *b)
{
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_mult.");
	}

	istr *c = istr_create(max(a->max_size, b->max_size));
	istr* tmp;

	int i, j;
	int remainder = 0;

    // iterate all combinations of digits for the two istr
	for(i = 0; i < a->size; i++) {

		tmp = istr_create(max(a->max_size, b->max_size));
		tmp->size = i;
		remainder = 0;

        // iterate all digits in second istr and multiply by a digit from first istr
		for(j = 0; j < b->size; j++) {

			int multiplied = (get_digit(a, i) - '0') * (get_digit(b, j) - '0') + remainder;
			set_digit(tmp, j + i, multiplied % 10 + '0');
			tmp->size++;
			remainder = multiplied / 10;
		}

        // account for remainder
		if(remainder != 0) {
			tmp->size++;
			set_digit(tmp, j + i, remainder + '0');

		}

		c = istr_add(c, tmp);
		istr_destroy(tmp);
	}

	return c;
}

/**
 * raise an istr to a power
 */
istr *istr_pow(istr *a, istr *b)
{
	istr *c = int_to_istr(1, a->max_size);
	istr *k = istr_copy(b);

    // perform repeated multiplication
	while(k->size > 0) {

		c = istr_mult(c, a);
		k = istr_sub(k, int_to_istr(1, 1));
	}

	istr_destroy(k);
	return c;
}

/**
 * divide two istr
 *
 * DOESN'T DIVIDE YET
 */
istr *istr_div(istr *a, istr *b)
{
	istr *c = istr_create(max(a->max_size, b->max_size));
	return c;
}
