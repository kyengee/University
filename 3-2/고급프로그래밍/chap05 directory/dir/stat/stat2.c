#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <curses.h>


main ()
{
  int status;
  struct stat statbuf;

  status = mkdir ("test", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  printf ("statbuf.st_mode %d\n", statbuf.st_mode);
  stat ("test", &statbuf);
  (S_ISDIR (statbuf.st_mode)) ? printf ("Directory exists.\n") : printf ("There is no such Dir\n");
  printf ("statbuf.st_mode %d\n", statbuf.st_mode);
  system ("ls -al");

  status = rmdir ("test");
  (!status) ? printf ("Directory deleted.\n") : printf ("Unable to delete the directory.\n");

  statbuf.st_mode &= 0;
  printf ("statbuf.st_mode %d\n", statbuf.st_mode);
  stat ("test", &statbuf);
  (S_ISDIR (statbuf.st_mode)) ? printf ("Directory exists.\n") : printf ("There is no such Dir\n");
  
}
