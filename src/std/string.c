#include "string.h"
#include "dfio.h"

/******************************************************************************/
/*                                string utils                                */
/******************************************************************************/

size_t dfstrlen(const char* str) {
    size_t result = 0;

    while (*str++) {
        result++;
    }
    return result;
}

bool dfstreq(const char *lhs, const char *rhs) {
    while (*lhs && *rhs) {
        if (*lhs++ != *rhs++) {
            return false;
        }
    }
    return *lhs == 0 && *rhs == 0;
}

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

    double decimals = 0;
    double factor = 1;
    while (dfisdigit(*str)) {
        decimals = decimals*10 + dfchartoint(*str++);
        factor *= 10;
    }
    result += decimals / factor;

    return result * sign;
}

/*
 * Converts a long to a string and put the result into `dest`.
 */
int dflongtostr(char *dest, long n, size_t max) {
    char buff[256] = {0};
    int idxbuff = 0, idxdest = 0;
    bool isneg = n < 0;
    long posn = isneg ? -n : n;

    while (posn > 0) {
        buff[idxbuff++] = '0' + posn%10;
        posn /= 10;
    }
    if (isneg) {
        dest[idxdest++] = '-';
    }
    idxbuff--;
    while (idxbuff >= 0 && idxdest < max) {
        dest[idxdest++] = buff[idxbuff--];
    }
    dest[idxdest < max ? idxdest : idxdest - 1] = 0; // make sure the string is
                                                     // valid
    return idxdest;
}

/*
 * Converts a double to a string and put the result into `dest`.
 * This is not the most efficient and precise way to convert doubles to string
 * but this solution is very simple and good enough for this project.
 */
int dfdoubletostr(char *dest, double n, size_t max, long precision) {
    char decimals[100] = {0};
    int idxdest, idxdec = 1;
    long intpart = (long) n;
    long decpart = ((abs(n) + 1) * precision) - (abs(intpart) * precision);

    idxdest = dflongtostr(dest, intpart, max);
    int size  = dflongtostr(decimals, decpart, 100);

    if (idxdest < max) {
        dest[idxdest++] = '.';
    }
    while (idxdest < max && decimals[idxdec] != 0) {
        dest[idxdest++] = decimals[idxdec++];
    }
    if (idxdest >= max) {
        idxdest = max - 1;
    }
    dest[idxdest] = 0;
    return idxdest;
}

bool dfisdigit(const char chr) {
    return '0' <= chr && chr <= '9';
}
