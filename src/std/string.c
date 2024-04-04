#include "string.h"

/******************************************************************************/
/*                            convertion functions                            */
/******************************************************************************/

/*
 * Converts a char to an int.
 * Warning: no verification is performed.
 */
int dfchartoint(const char chr) {
    return chr - '0';
}

/*
 * Converts a string to a long.
 */
long dfstrtolong(const char* str) {
    long result = 0;
    char sign = 1;

    if (*str == '-') {
        sign *= -1;
        str++;
    }
    while (dfisdigit(*str)) {
        result = result*10 + dfchartoint(*str++);
    }
    return result * sign;
}

/*
 * Converts a string to a double.
 * Warning: no verification is performed in this function so if there are
 *          characters that are not digits, the result is undefined.
 */
double dfstrtodouble(const char* str) {
    double result = 0;
    char sign = 1;

    if (*str == '-') {
        sign *= -1;
        str++;
    }
    while (dfisdigit(*str)) {
        result = result*10 + dfchartoint(*str++);
    }
    if (*str == '.') {
        str++;
    }

    double tmp = 0;
    double factor = 1;
    while (dfisdigit(*str)) {
        tmp = tmp*10 + dfchartoint(*str++);
        factor *= 10;
    }
    result += tmp / factor;

    return result * sign;
}

bool dfisdigit(const char chr) {
    return '0' <= chr && chr <= '9';
}
