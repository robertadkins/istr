#include "istr.h"
#include <stdio.h>
#include <stdlib.h>

void err(char *err) {
	printf("[ERROR]: %s\n", err);
	exit(-1);
}

istr *int_to_istr(int num, int max_size)
{
	if(num < 0 || max_size <= 0) {
		err("Invalid arguments for int_to_istr");
	}

	istr *i = malloc(sizeof(istr));
	i->num = calloc(max_size + 1, sizeof(char));
	i->max_size = max_size;
	int k, c = 0;

	i->num[max_size] = '\0';

	for(k = 0; k < max_size; k++) {
		i->num[k] = '0';
	}

	while(num > 0) {
		i->num[max_size - c - 1] = num % 10 + '0';
		num /= 10;
		c++;
	}

	i->size = c;

	return i;
}

istr *istr_create(int size)
{
	return int_to_istr(0, size);
}

istr *istr_copy(istr *i)
{
	if(i == NULL) {
		err("Pointer to istr is invlalid.");
	}

	istr *ret = istr_create(i->max_size);
	ret->size = i->size;
	ret->max_size = i->max_size;

	int k;

	for(k = 0; k < i->size; k++) {
		set_digit(ret, k, get_digit(i, k));
	}

	return ret;
}

void istr_destroy(istr *i)
{
	if(i == NULL) {
		err("Pointer to istr is invalid.");
	}

	free(i->num);
	free(i);
}

char get_digit(istr *i, int d)
{
	if(i == NULL || d < 0 || d > i->max_size) {
		err("Invalid arguments for get_digit.");
	}

	return i->num[i->max_size - d - 1];
}

void set_digit(istr *i, int d, char val)
{
	//printf("setting digit %d to %c in %s\n", d, val, istr_to_str(i));
	if(i == NULL || d < 0 || d >= i->max_size || val < '0' || val > '9') {
		err("Invalid arguments for set_digit.");
	}

	i->num[i->max_size - d - 1] = val;
}

istr *str_to_istr(char *str, int max_size)
{
	if(str == NULL) {
		err("NULL string argument for str_to_istr");
	}

	istr *ret = istr_create(max_size);

	int size = 0;
	char *tmp = str;

	while(*tmp != '\0') {
		tmp++;
		size++;
	}

	ret->size = size;
	int i;

	for(i = 0; i < size; i++) {
		set_digit(ret, i, str[size - i - 1]);
	}

	return ret;
}

char *istr_to_str(istr *i)
{
	if(i == NULL) {
		err("NULL istr pointer argument for istr_to_str.");
	}

	if(i->size == 0) {
		return "0";
	}

	return i->num + i->max_size - i->size;
}

istr *istr_add(istr *a, istr *b)
{
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_add.");
	}

	istr *c = istr_create(max(a->max_size, b->max_size));
	int k;
	int big_size = max(a->size, b->size);
	int small_size = min(a->size, b->size);

	for(k = 0; k < small_size; k++) {

		int remainder = 0;

		do {

			int added = get_digit(a, k) - '0' + get_digit(b, k) - '0' + remainder;
			set_digit(c, k, get_digit(c, k) + added %10);
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
	for(k = k; k < big_size; k++) {

		set_digit(c, k, get_digit(big, k));
	}

	c->size = k;
	return c;
}

istr *istr_sub(istr *a, istr *b)
{
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_sub.");
	}
	if(a->size < b->size) {
		err("invalide operands to istr_sub.");
	}

	istr *a_cpy = istr_copy(a);

	istr *c = istr_create(max(a->max_size, b->max_size));
	int i;

	for(i = 0; i < b->size; i++) {

		int sub = get_digit(a_cpy, i) - get_digit(b, i);

		if(sub < 0) {

			set_digit(c, i, get_digit(a_cpy, i) + 10 - get_digit(b, i) + '0');
			int d = 1;
			sub = get_digit(a_cpy, i + d) - 1 - '0';

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
	for(i = b->size; i < a_cpy->size; i++) {
		set_digit(c, i, get_digit(a_cpy, i));
	}

	for(i = 0; c->num[i] == '0'; i++) {

	}

	c->size = c->max_size - i;
	istr_destroy(a_cpy);
	return c;
}

istr *istr_mult(istr *a, istr *b)
{
	if(a == NULL || b == NULL) {
		err("NULL istr pointer argument for istr_mult.");
	}

	istr *c = istr_create(max(a->max_size, b->max_size));
	istr* tmp;

	int i, j;
	int remainder = 0;

	for(i = 0; i < a->size; i++) {

		tmp = istr_create(max(a->max_size, b->max_size));
		tmp->size = i;
		remainder = 0;

		for(j = 0; j < b->size; j++) {

			int multiplied = (get_digit(a, i) - '0') * (get_digit(b, j) - '0') + remainder;
			//printf("mult: %d\n", multiplied);
			set_digit(tmp, j + i, multiplied % 10 + '0');
			tmp->size++;
			remainder = multiplied / 10;
		}

		if(remainder != 0) {
			tmp->size++;
			set_digit(tmp, j + i, remainder + '0');

		}

		c = istr_add(c, tmp);
		istr_destroy(tmp);
	}

	return c;
}

istr *istr_pow(istr *a, istr *b)
{
	istr *c = int_to_istr(1, a->max_size);
	istr *k = istr_copy(b);

	while(k->size > 0) {

		c = istr_mult(c, a);
		k = istr_sub(k, int_to_istr(1, 1));
	}

	istr_destroy(k);
	return c;
}

istr *istr_div(istr *a, istr *b)
{
	istr *c = istr_create(max(a->max_size, b->max_size));
	return c;
}
