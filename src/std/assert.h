#ifndef ASSERT_H
#define ASSERT_H
#include "dfio.h"
#include "dflib.h"

/******************************************************************************/
/*                                  function                                  */
/******************************************************************************/

#define errmsg(cond) "assert(" #cond "): failed.\n"

#define assert(cond)                                                           \
    if (!(cond)) {                                                             \
        dfwrite(stderr, errmsg(cond), sizeof(errmsg(cond)));                   \
        dfexit(1);                                                             \
    }

#endif
