#include "std/dflib.h"
#include "std/dfio.h"
#include "std/string.h"
#include "std/assert.h"

void testStringConvertion() {
    /* number to string */
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

    /* string to number */
    char buff[100];

    dflongtostr(buff, 1234, 255);
	assert(dfstreq("1234", buff));

    dflongtostr(buff, -84, 255);
	assert(dfstreq("-84", buff));

    dfdoubletostr(buff, 1234.7891, 255, 1e4);
	assert(dfstreq("1234.7891", buff));

    dfdoubletostr(buff, -323.00983209832, 255, 1e12);
	assert(dfstreq("-323.009832098320", buff));

    dfdoubletostr(buff, 323.00983209832, 255, 1e12);
	assert(dfstreq("323.009832098320", buff));

    dfdoubletostr(buff, -1.001, 255, 1e3);
	assert(dfstreq("-1.001", buff));

    dfdoubletostr(buff, -1.0002823098, 255, 1e10);
	assert(dfstreq("-1.0002823098", buff));
}

void _start(void) {
    /* test convertion functions */
    testStringConvertion();

    /* test input oupout */
    char buff[100] = {0};
    int i = 4;
    dfprintf("i: %d\n", i);
    dfwrite(stdout, "Enter a message:\n", 17);
    dfread(stdin, buff, 100);
    dfwrite(stdout, buff, 100);

    dfprintf("test\n");
    dfprintf("int: %d\n", 1);
    /* dffprintf(0, "double: %f\n", 10.0); */
    dfprintf("char: %c\n", 'c');
    dfprintf("str: %s\n", "hello, world");
    dfprintf("int: %d & char: %c\n", 1, 'f');
    dfprintf("int: %d & char: %c & str: \"%s\"\n", 1, 'd', "hello world");

    dfsprintf(buff, 100, "Hello, World!");
    dfprintf("%s\n", buff);

    dfexit(EXIT_SUCESS);
    __builtin_unreachable(); // make that the compiler doesn't put anything else
}
