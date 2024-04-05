#ifndef STRING_H
#define STRING_H
#include "dflib.h"

size_t dfstrlen(const char* str);
bool dfstreq(const char *lhs, const char *rhs);

bool dfisdigit(const char chr);
int dfchartoint(const char chr);
long dfstrtolong(const char* str);
double dfstrtodouble(const char* str);
int dflongtostr(char *dest, long n, size_t max);
int dfdoubletostr(char *dest, double n, size_t max, long precision);

#endif
