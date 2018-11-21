
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define MAXHOST 16

typedef struct {
  int trigger;
  int txflag;
  int size;
  int sending[MAXHOST + 1];
  int odo_sending[MAXHOST];
  int camcon_sending[MAXHOST];
  char hostname[MAXHOST][64];
  char buf[3][32000];		// ctl, audio, and cam
} TxClass;



int main ()
{
  FILE *fp=NULL;
  char filename[2048]; 
  int i;
  TxClass tx;
  char site[MAXHOST][64];

  printf("HOME dir: %s\n", getenv("HOME"));
  printf("HOME dir: %s\n", getenv("PWD"));

  sprintf(filename, "%s/.bestarc", getenv("PWD"));
  fp = fopen (filename, "r");

  if (!fp) {   /* if specified file does not exist... try default file */
    fp = fopen (".bestarc", "r");
    if (!fp) {
      fp = fopen ("/tmp/.besta.conf", "r");
      if (!fp) {	/* there is no config file.... use defaults */
	perror("no config file");
	exit (1);
      }
    }
  }

  for (i=0; i < MAXHOST; i++) {
    fscanf (fp,"%s",tx.hostname[i]);
    fscanf (fp,"%s",site[i]);
  }

  for (i=0; i < MAXHOST; i++) {
    printf ("%2d: %s\t", i, tx.hostname[i]);
    printf ("%s\n", site[i]);
  }

  fclose (fp);
  return 0;
}
