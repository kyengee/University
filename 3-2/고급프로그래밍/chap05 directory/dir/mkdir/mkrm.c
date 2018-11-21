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

  status = mkdir ("test", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  status = mkdir ("./test/testa", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  system ("ls -al");

  status = rmdir ("test");
  (!status) ? printf ("Directory deleted.\n") : printf ("Unable to delete the directory.\n");
}
