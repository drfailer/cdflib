#ifndef ASSERT_H
#define ASSERT_H
#include "dfio.h"
#include "dflib.h"

/******************************************************************************/
/*                                  function                                  */
/******************************************************************************/

#define linestr(line) #line

#define errmsg(cond) #cond ": at " linestr(__LINE__) " failed.\n"

#define assert(cond)                                                           \
    if (!(cond)) {                                                             \
        dfwrite(stderr, errmsg(cond), sizeof(errmsg(cond)));                   \
        dfexit(1);                                                             \
    }

#endif
