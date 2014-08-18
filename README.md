istr
===========

Robbie Adkins
Started: 6/30/2013
istr

Purpose:
—————————

istr solves the issue of working with very large numbers. Since an istr is only an array of chars, arbitrarily large integers can be created and manipulated.

Functionality:
—————————

An istr is a string representation of an unsigned integer. The istr.h header defines basic operations:
* Addition
* Subtraction
* Multiplication
* Division
* Modulus

istr.h also provides an integer to istr converter.
	
Properties:
—————————

An istr is defined by:
* a fixed length char array
* a size (number of digits)
* 1st digit stored at index length_of_array - 2, nth at index length_of_array - n - 2

To add:
—————————

* Signed integer functionality
* dynamically sized arrays
* bit wise operations
* power, sqrt, etc.
* compare / equal functions
* improve power algorithm to use repeated squaring
