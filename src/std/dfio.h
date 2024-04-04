#ifndef DFIO_H
#define DFIO_H
#include "dflib.h"

/******************************************************************************/
/*                                  defines                                   */
/******************************************************************************/

#define stdin 0
#define stdout 1
#define stderr 2

/******************************************************************************/
/*                                 functions                                  */
/******************************************************************************/

int dfwrite(unsigned int fd, const char* buff, size_t count);
int dfread(unsigned int fd, char* buff, size_t count);

#endif
