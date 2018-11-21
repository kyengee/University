
#include <dirent.h>

int my_double_ls (const char *name)
{
  struct dirent *d;
  DIR *dp;

  /* 디렉토리를 개방하고, 실패여부를 점검함 */
  if ((dp=opendir(name)) == NULL)
    return (-1);

  /* 디렉토리를 살피면서 루프를 계속한다. 이때 inode 번호가 유효하면 디렉토리항을 프린트한다.   */
  while (d = readdir(dp)) {
    if (d->d_ino !=0)
      printf ("%s\n", d->d_name);
  }

  /* 이제 디렉토리의 시작으로 되돌아간다 ... */
  rewinddir(dp);

  /* ... 그리고 디렉토리를 다시 프린트한다. */
  while (d = readdir(dp))  {
    if (d->d_ino != 0)
      printf ("%s\n", d->d_name);
  }
  closedir (dp);

  return (0);
}
