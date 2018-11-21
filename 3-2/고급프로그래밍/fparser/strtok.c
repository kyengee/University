
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATOR (" :\t\n=")
#define MAXLINE 2048

struct f {
  char host[4][128];
  int nhost;
  int channel[4];
  int fps[4];
  int quant;
  int odo;
  int vdotype;
};

int fparser (char *fname, struct f *fs);

int main (int argc, char **argv)
{
  struct f *fs;
  int i, lineno;

  char *ptr;
  char buf[]="FEB.14,1988 \n\n ok no 1 2 3 4 \n 5 6 7 8 9";

  ptr = strtok (buf, SEPARATOR);
  fprintf (stderr, "\nThis is from memory\n");
  while (ptr != NULL) {
    printf ("ptr = %s\n", ptr);
    ptr = strtok (NULL, SEPARATOR);
  }

  fprintf (stderr, "\nThis is from a file\n");

  fs = (struct f *) calloc (1, sizeof (struct f));

  lineno = fparser ("strtok1.conf", fs);

  for (i=0; i<fs->nhost; i++) 
    fprintf (stderr, "cmdr%d= %s, fps= %d, channel= %d\n",i+1,fs->host[i],fs->fps[i],fs->channel[i]);

    fprintf (stderr, "quant = %d, vdotype = %d, audio = %d\n", fs->quant, fs->vdotype, fs->odo);

  return 0;
}

int fparser (char *fname, struct f *fs)
{
  int lineno=0;
  FILE *fp=NULL;
  char line[MAXLINE];
  char *ptr;
  int nhost=0;

  fp = fopen ("strtok.conf", "r");
  if (fp == NULL) {   /* specified file does not exist... try default file */
    sprintf(fname, "%s/dmr/%s", getenv("HOME"), fname);
    fp = fopen (fname, "r");
    if (fp == NULL) {
      sprintf(fname, "%s/dmr/.besta.conf", getenv("HOME"));
      fp = fopen (fname, "r");
      if (!fp) {	/* there is no config file.... use defaults */
	perror("No PTZF config file exists.");
	return -1;
      }
    }
  }

  while (fgets (line, MAXLINE, fp) != NULL) {
    if (((ptr = strtok (line, SEPARATOR)) == NULL) && (line[0] == '\n')) continue;
    else if (ptr[0] != '#') {
      if (!strcmp (ptr, "CMDR")) {
	ptr = strtok (NULL, SEPARATOR);
	strcpy (fs->host[fs->nhost], ptr); // "hostname"

	ptr = strtok (NULL, SEPARATOR);	// "frames/second" 
	fs->fps[fs->nhost] = atoi (ptr);

	ptr = strtok (NULL, SEPARATOR);	// "video display CHANNEL"
	fs->channel[fs->nhost] = atoi (ptr);

	fs->nhost ++;
      }
      else if(!strcmp(ptr, "QUANT")) {
	ptr = strtok (NULL, SEPARATOR);
	fs->quant = atoi (ptr);
      }
      else if(!strcmp(ptr, "ODO")) {
	ptr = strtok (NULL, SEPARATOR);
	if(!strcmp(ptr, "yes"))
	  fs->odo = 1;
	else 
	  fs->odo = 0;
      }
      else if(!strcmp(ptr, "VDO_TYPE")) {
	ptr = strtok (NULL, SEPARATOR);
	fs->vdotype = atoi (ptr);
      }
    }
    lineno++;
  }
  if (fp != NULL) 
    fclose (fp);

  return lineno;
}
