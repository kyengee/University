
// file system usage
// checking disk space availability

#include <sys/vfs.h>
#include <stdio.h>
#include <stdlib.h>

#define CONVERT_BLOCKS(B) adjust_blocks((long)(B), (long)fsd.f_bsize, (long)512)
#define fsfreeMB(A) fsfree_MByte(A)/2048

static long adjust_blocks (long blocks, long fromsize, long tosize)
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
  (*total) = CONVERT_BLOCKS (fsd.f_blocks);
  (*free) = CONVERT_BLOCKS (fsd.f_bavail);

  return 0;
}

int fsfree (const char *path, long *free)
{
  struct statfs fsd;

  if (statfs (path, &fsd) < 0) return -1;
  (*free) = CONVERT_BLOCKS (fsd.f_bavail);

  return 0;
}

int fsfree_MByte (const char *path)
{
  struct statfs fsd;

  if (statfs (path, &fsd) < 0) return -1;

  if (fsd.f_bsize == 512) return (fsd.f_bavail);
  else if (fsd.f_bsize >(long) 512) return (fsd.f_bavail * (fsd.f_bsize / (long) 512)); 
  else return ((fsd.f_bavail + 1) / ((long) 512 / fsd.f_bsize));
}

int fsfree_MB (const char *path)
{
  return fsfree_MByte (path)/2048;
}


int main (int argc, char **argv)
{
  char fpath[255];
  long int free, total;

//  strcpy (fpath, "/home/bkna/.VDO/");

//  sprintf (fpath, "%s", getenv ("HOME"));

  sprintf (fpath, "%s", argv[1]);
  fprintf (stderr, "path %s\n", fpath);

  fsusage (fpath, &total, &free);

  printf ("Disk Space:\n");
  printf ("   total %10d MBytes\n", total/2048);
  printf ("   free  %10d MBytes\n", free/2048);

  fsfree (fpath, &free);
  printf ("   free  %10d MBytes\n", free/2048);

  fprintf (stderr, "fsfree_MB = %dMBytes\n", fsfreeMB (fpath));
}
