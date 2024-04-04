#include "std/dflib.h"
#include "std/dfio.h"
#include "std/string.h"
#include "std/assert.h"

void testStringConvertion() {
    int basicNumber = dfstrtolong("1234");
    double basicDouble = dfstrtodouble("1234.7891");
    int negativeInt = dfstrtolong("-84");
    double negativeDouble = dfstrtodouble("-323.00983209832");
    double precision1 = dfstrtodouble("-1.001");
    double precision2 = dfstrtodouble("-1.0002823098");

	assert(1234 == basicNumber);
	assert(1234.7891 == basicDouble);
	assert(-84 == negativeInt);
	assert(-323.00983209832 == negativeDouble);
	assert(-1.001 == precision1);
	assert(-1.0002823098 == precision2);
}

void _start(void) {
    /* test convertion functions */
    testStringConvertion();

    /* test input oupout */
    char buff[100] = {0};
    dfwrite(stdout, "Enter a message:\n", 17);
    dfread(stdin, buff, 100);
    dfwrite(stdout, buff, 100);

    dfexit(EXIT_SUCESS);
    __builtin_unreachable(); // make that the compiler doesn't put anything else
}
