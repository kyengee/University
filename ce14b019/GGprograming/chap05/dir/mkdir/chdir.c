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

int main (int argc, char **argv)
{
  int status;
  FILE *fto;
  char buf[512];

  if (argc != 2) {
    fprintf (stderr, "USAGE: filename option\n");
    return -1;
  }

  status = mkdir ("test", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  status = mkdir ("./test/testa", 0755);
  (!status) ? printf ("Directory created.\n") : printf ("Unable to create directory.\n");

  sprintf(buf, "ls -al");
  system (buf);

  status = rmdir ("test");
  (!status) ? printf ("Directory deleted.\n") : printf ("Unable to delete the directory.\n");

  status = chdir ("./test/testa");
  (!status) ? printf ("Current Working Directory is changed.\n") : printf ("Unable to change to the directory.\n");

  fto = fopen (argv[1], "w+");

  strcpy(buf, "\n\tKorea Polytechnic University \n\tDept. of Cybernetics \n\tHong gildong");
  fwrite(buf, strlen (buf), 1, fto);

  fprintf(fto, "\n\n\tClass of Advanced Programming\n");

  fclose(fto);

  sprintf(buf, "more %s", argv[1]);
  system (buf);

  status = chdir ("../..");
  (!status) ? printf ("Current Working Directory is changed.\n") : printf ("Unable to change to the directory.\n");

  sprintf (buf, "rm -rf %s", "test");
  system(buf);

  return 0;
}
