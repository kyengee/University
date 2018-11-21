

/* Includes */
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
#include <sys/vfs.h>


static long fs_get_blocks (long blocks, long fromsize, long tosize)
{
  if (fromsize == tosize) return blocks;
  else if (fromsize > tosize) return blocks * (fromsize / tosize); 
  else return (blocks + 1) / (tosize / fromsize);
}


/* results are returned in *dfree and *dsize, in 512 byte units */

int fsusage (const char *path, long *total, long *free)
{
  struct statfs fsd;

  if (statfs (path, &fsd) < 0) return -1;
  (*total) = fs_get_blocks (fsd.f_blocks, (long)fsd.f_bsize, (long)512);
  (*free) = fs_get_blocks (fsd.f_bavail, (long)fsd.f_bsize, (long)512);

  return 0;
}


/* checking free disk space 
 * return: free space in MByte unit
 */
long int fsfree (const char *path)
{
  struct statfs fsd;
  long int free;

  if (statfs (path, &fsd) < 0) return 0;
  return fs_get_blocks (fsd.f_bavail, (long)fsd.f_bsize, (long)512) / 2048; // MByte unit
}


void mkdir_check (const char *pathname, mode_t mode)
{
  int value;
	
  value = mkdir(pathname, mode);
  if (value == 0) return;
  if (value == -1) {
    if (errno == EEXIST) return; else {
      printf("Error while creating directory");
      exit(0);
    }
  }
}


void mkdir_fpath (char *fpath, struct tm *currenttime)
{
  char filebase[255];
  char base[255];

  mkdir_check(fpath, 0755);
  chdir (fpath);
  strcpy (base, fpath);

  sprintf(filebase, "%04d/", currenttime->tm_year+1900);
  mkdir_check(filebase, 0755);
  sprintf(filebase, "%s%02d/", filebase, currenttime->tm_mon+1);
  mkdir_check(filebase, 0755);
  sprintf(filebase, "%s%02d/", filebase, currenttime->tm_mday);
  mkdir_check(filebase, 0755);
  sprintf(filebase, "%s%02d/", filebase, currenttime->tm_hour);
  mkdir_check(filebase, 0755);
  sprintf(filebase, "%s%02d/", filebase, currenttime->tm_min);
  mkdir_check(filebase, 0755);
  sprintf(filebase, "%s%02d/", filebase, currenttime->tm_sec);
  mkdir_check(filebase, 0755);

  strcat (base, filebase);
  chdir (base);
  printf ("current dir: %s\n", base);

}

void rmdir_fpath (char *fpath, struct tm *curtime)
{
  char fbase[255];
  register int i=0;
  char d[255];

  strcpy (fbase, fpath);

  while (fsfree (fpath) < 435)  {
    sprintf(fbase, "%s%04d/%02d/%02d/%02d/%02d",
	    fpath,
	    curtime->tm_year+1900,
	    // curtime->tm_mon-1,// for 2 month ago
	    // curtime->tm_mday + (i++));
	    curtime->tm_mon+1, 
	    curtime->tm_mday,
	    curtime->tm_hour,
	     (i++));
    i %= 60;
    if (curtime->tm_min < i) break;

//    remove (fbase);
//     rmdir (fbase);
     sprintf (d, "rm -rf %s", fbase);
     system (d);
  }
}


int main ()
{
  struct tm *currenttime = NULL, prevtime;
  time_t currenttimep;
  char file[255], fpath[255], filebase[255];

  sprintf(fpath, "%s/.VDO/", getenv("HOME"));

  currenttimep = time(NULL);
  currenttime = localtime (&currenttimep);
  memcpy (&prevtime, currenttime, sizeof (struct tm));
  mkdir_fpath (fpath, currenttime);

  // fopen ();

  for (;;){

    currenttimep = time(NULL);
    currenttime = localtime (&currenttimep);
//    if ((prevtime.tm_min != currenttime->tm_min) && !(currenttime->tm_min % 10)) {
    if ((prevtime.tm_sec != currenttime->tm_sec) && !(currenttime->tm_sec % 10)) {
      // fclose ();
      mkdir_fpath (fpath, currenttime);
      memcpy (&prevtime, currenttime, sizeof (struct tm));
      // fopen (); /* file open for new data file */
    }

    /* check whether disk space is available or not */
    if (fsfree (fpath) < 420) 
	rmdir_fpath (fpath, currenttime);

    // fwrite ();
  }
}
