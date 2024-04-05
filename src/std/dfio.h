#ifndef DFIO_H
#define DFIO_H
#include "dflib.h"

/******************************************************************************/
/*                                  defines                                   */
/******************************************************************************/

#define stdin 0
#define stdout 1
#define stderr 2

#define FILE_MODE 0
#define BUFFER_MODE 1

/******************************************************************************/
/*                                 functions                                  */
/******************************************************************************/

int dfwrite(unsigned int fd, const char* buff, size_t count);
int dfread(unsigned int fd, char* buff, size_t count);
int dffprintf(unsigned int fd, const char *__restrict fmt, ...);
int dfprintf(const char *__restrict fmt, ...);
int dfsprintf(char *dest, size_t size, const char *__restrict fmt, ...);

#endif
