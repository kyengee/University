
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include "dll.h"

#define	PATH_MAX_GUESS	1024	/* if PATH_MAX is indeterminate */

/* function type that's called for each filename */
typedef int Myfunc(const char *, const struct stat *, int);

#ifdef	PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

/* Function Prototypes */
static Myfunc	myfunc;
static int	dopath(Myfunc *);
static char     *path_alloc (int *size);

int dmr_get_dir_info (char *, Myfunc *);
int dmr_clear_superdir (char *fullpath);
int dmr_get_fs_info (char *path);
int dmr_get_working_disk (char *path);


#ifdef TEST
int main (int argc, char *argv[])
#else
int ftw_main (int argc, char *argv[])
#endif
{
  int ret;
  int i;
  char path[64];

//   if (argc < 2) {
//     printf ("usage: ftw <starting-pathname>\n");
//     exit (0);
//   }

  first = last = NULL;
  sprintf (path, "%s/DMRDATA/HDD", getenv ("HOME"));

//   for (i=1; i<argc; i++) 
//     dmr_get_dir_info (argv[i], myfunc);	/* get dir info */
     dmr_get_dir_info ("/home/bkna/DMRDATA/HDD1", myfunc);
     dmr_get_dir_info ("/home/bkna/DMRDATA/HDD0", myfunc);

  dll_show_list (first);
  ret = dmr_get_working_disk (path);

  printf ("working disk num is %d\n", ret);

//  dmr_delete_dir (first->date);	        /* delete dir */
//  dll_show_list (first);

  return 0;
}

/*
 * Descend through the hierarchy, starting at "pathname".
 * The caller's func() is called for every file.
 */

#define	FTW_F	1		/* file other than directory */
#define	FTW_D	2		/* directory */
#define	FTW_DNR	3		/* directory that can't be read */
#define	FTW_NS	4		/* file that we can't stat */

static char *fullpath; /* contains full pathname for every file */
char date[64];

/* we return whatever func() returns */
int dmr_get_dir_info (char *pathname, Myfunc *func) 
{
  fullpath = path_alloc(NULL);	/* malloc's for PATH_MAX+1 bytes */
				/* ({Prog pathalloc}) */
  strcpy (fullpath, pathname);	/* initialize fullpath */

  return (dopath(func));
}

/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it,
 * call func(), and return.  For a directory, we call ourself
 * recursively for each name in the directory.
 */

/* we return whatever func() returns */
static int dopath (Myfunc *func)
{
  struct stat statbuf;
  struct dirent	*dirp;
  DIR	*dp;
  int	ret;
  char	*ptr;
  char *ymd;

  if (stat (fullpath, &statbuf) < 0)
    return (func(fullpath, &statbuf, FTW_NS));	/* stat error */

//   if (S_ISDIR(statbuf.st_mode) == 0)
//     return (func(fullpath, &statbuf, FTW_F));	/* not a directory, file or others */

  /*
   * It's a directory.  First call func() for the directory,
   * then process each filename in the directory.
   */

  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
    return (ret);

  ptr = fullpath + strlen(fullpath);	/* point to end of fullpath */
  *ptr++ = '/';
  *ptr = 0;
  ymd = date + strlen (date);
  
  if ((dp = opendir(fullpath)) == NULL)
    return (func(fullpath, &statbuf, FTW_DNR)); /* can't read directory */

  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, ".") == 0  || strcmp(dirp->d_name, "..") == 0)
      continue; /* ignore dot and dot-dot */

    strcpy (ptr, dirp->d_name); /* append name after slash */
    strcpy (ymd, dirp->d_name);

    if ((ret = dopath(func)) != 0) /* recursive */
//      break;	/* recursive all sub-dirs. ie, /home/besta/DMRDATA/HDD0/year/month/day/hour/min/ */
      continue; /* recursive till day directories. ie. /home/besta/DMRDATA/HDD0/year/month/day */
  }
  ptr[-1] = 0;	/* erase everything from slash onwards */
  ymd[0] = 0;

  if (closedir(dp) < 0)
    printf ("can't close directory %s\n", fullpath);

  return (ret);
}


static int myfunc (const char *pathname, const struct stat *statptr, int type)
{
  DLL *info;

  switch (type) {
  case FTW_F:
    switch (statptr->st_mode & S_IFMT) {
    case S_IFREG: printf ("file ...........\n");
    case S_IFBLK:
    case S_IFCHR:
    case S_IFIFO:
    case S_IFLNK:
    case S_IFSOCK: break;
    case S_IFDIR:  printf ("for S_IFDIR for %s", pathname); /* directories should have type = FTW_D */
    }
    break;

  case FTW_D:
    if (strlen (date) == 8) {
      if (!(info = (DLL *) malloc (sizeof (DLL)))) {
	printf ("Error: DLL malloc in myfunc\n");
	return 1;
      }
      strcpy (info->date, date);
      strcpy (info->fullpath, pathname);

      first = dll_make_list_sort (info, first);
      return 1;	       /* key for conditional recursive in dopath() */
    }
    break;
    
  case FTW_DNR:
    printf ("can't read directory %s\n", pathname);
    break;

  case FTW_NS:
    printf ("stat error for %s\n", pathname);
    break;

  default:
    printf ("unknown type %d for pathname %s\n", type, pathname);
  }

  return 0;
}


/* we're not guaranteed this is adequate */
/* also return allocated size, if nonnull */

static char *path_alloc (int *size)
{
  char	*ptr;

  if (pathmax == 0) {		/* first time through */
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
      if (errno == 0)
	pathmax = PATH_MAX_GUESS; /* it's indeterminate */
      else
	printf ("pathconf error for _PC_PATH_MAX\n");
    }
    else
      pathmax++;	     /* add one since it's relative to root */
  }

  if ((ptr = malloc(pathmax + 1)) == NULL)
    printf ("malloc error for pathname\n");

  if (size != NULL)
    *size = pathmax + 1;

  return (ptr);
}


/* It returns the number of how many subdir or file exist */

int dmr_clear_superdir (char *fullpath)
{
  struct stat statbuf;
  struct dirent	*dirp;
  DIR	*dp;
  int	ret=0;
  char superdir[128], d[128];
  int len;

  len = strlen (fullpath) - 2;
  strncpy (superdir, fullpath, len);
  superdir[len] = '\0';

  if (stat (superdir, &statbuf) < 0) {
    printf ("Error: stat () in dmr_clear_superdir()\n");
    return -1;
  }
  if ((dp = opendir(superdir)) == NULL) {
    printf ("Error: opendir () in dmr_clear_superdir()\n");
    return -1; /* can't read directory */
  }
  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp (dirp->d_name, ".") == 0  ||       /* ignore dot */
	strcmp (dirp->d_name, "..") == 0 ||       /* ignore dot-dot */
	strstr (dirp->d_name, "core") != NULL)    /* ignore core* */
      continue;
    ret ++;
  }
  if (closedir(dp) < 0) {
    printf ("Error: closedir () in dmr_clear_superdir()\n");
    return -1;
  }

  if (!ret) {
    sprintf (d, "rm -rf %s", superdir);	// rmove month directory
    system (d);

    len = strlen (superdir) - 3; // 2 digits for month + a digit for "/" 
    strncpy (superdir, superdir, len);
    superdir[len] = '\0';

    if (stat (superdir, &statbuf) < 0) {
      printf ("Error: 2. stat () in dmr_clear_superdir()\n");
      return -1;
    }
    if ((dp = opendir(superdir)) == NULL) {
      printf ("Error: 2. opendir () in dmr_clear_superdir()\n");
      return -1; /* can't read directory */
    }
    while ((dirp = readdir(dp)) != NULL) {
      if (strcmp (dirp->d_name, ".") == 0  ||       /* ignore dot */
	  strcmp (dirp->d_name, "..") == 0 ||       /* ignore dot-dot */
	  strstr (dirp->d_name, "core") != NULL)    /* ignore core* */
	continue;
      ret ++;
    }
    if (closedir(dp) < 0) {
      printf ("Error: 2. closedir () in dmr_clear_superdir()\n");
      return -1;
    }
    if (!ret) {
      sprintf (d, "rm -rf %s", superdir);	// rmove year directory
      system (d);
    }
  }

  return (ret);
}


int dmr_get_fs_info (char *path)
{
  char curdir[64];
  struct stat statbuf;
  int num=0;

  do {
    statbuf.st_mode &= 0;
    sprintf (curdir, "%s%d", path, num);
    stat (curdir, &statbuf);
    num ++;
  } while (S_ISDIR (statbuf.st_mode) != 0);

  return (num - 1);
}


int dmr_get_working_disk (char *path)
{
  int i, num_dir;
  char curdir[64], *ptr, ret[2];

  num_dir = dmr_get_fs_info (path);
  for (i=0; i<num_dir; i++) {
    sprintf (curdir, "%s%d", path, i);
    dmr_get_dir_info (curdir, myfunc); /* get dir info */
  }

  if ((ptr = strstr (last->fullpath, "HDD")) == NULL) return -1;
  ptr += 3;
  strncpy (ret, ptr, 1);
  ret[1] = '\0';

  return atoi (ret);
}
