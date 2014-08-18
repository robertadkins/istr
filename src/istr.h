#ifndef _istr_h
#define _istr_h

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

typedef struct istr {
	char *num;
	int size;
	int max_size;
} istr;

istr *istr_create(int max_size);
istr *int_to_istr(int num, int max_size);
istr *str_to_istr(char *str, int max_size);
istr *istr_copy(istr *i);
void istr_destroy(istr *i);

char *istr_to_str(istr *i);
void set_digit(istr *i, int d, char val);
char get_digit(istr *i, int d);

istr *istr_add(istr *a, istr *b);
istr *istr_sub(istr *a, istr *b);
istr *istr_mult(istr *a, istr *b);
istr *istr_div(istr *a, istr *b);

istr *istr_mod(istr *a, istr *b);
istr *istr_pow(istr *a, istr *b);

#endif
