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
  struct stat statbuf, statbuf_b;

  status = mkdir ("test", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  stat ("test", &statbuf);
  (S_ISDIR (statbuf.st_mode)) ? printf ("Directory exists.\n") : printf ("There is no such Dir\n");

  system ("ls -al");

  status = rmdir ("test");
  (!status) ? printf ("Directory deleted.\n") : printf ("Unable to delete the directory.\n");

  stat ("test", &statbuf_b);
  (S_ISDIR (statbuf_b.st_mode)) ? printf ("Directory exists.\n") : printf ("There is no such Dir\n");
  
}
