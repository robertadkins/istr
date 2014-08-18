CFLAGS=-Wall -g

all: mult_test sub_test add_test pow_test

mult_test: istr.o

sub_test: istr.o

add_test: istr.o

pow_test: istr.o

clean:
	rm -f *.o mult_test sub_test
