#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXPATH 256

main ()
{
  char buf[MAXPATH];

  getcwd (buf, MAXPATH);
  printf ("current dir is : %s\n", buf);

}
