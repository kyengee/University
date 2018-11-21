
#include <dirent.h>

int my_double_ls (const char *name)
{
  struct dirent *d;
  DIR *dp;

  /* ���丮�� �����ϰ�, ���п��θ� ������ */
  if ((dp=opendir(name)) == NULL)
    return (-1);

  /* ���丮�� ���Ǹ鼭 ������ ����Ѵ�. �̶� inode ��ȣ�� ��ȿ�ϸ� ���丮���� ����Ʈ�Ѵ�.   */
  while (d = readdir(dp)) {
    if (d->d_ino !=0)
      printf ("%s\n", d->d_name);
  }

  /* ���� ���丮�� �������� �ǵ��ư��� ... */
  rewinddir(dp);

  /* ... �׸��� ���丮�� �ٽ� ����Ʈ�Ѵ�. */
  while (d = readdir(dp))  {
    if (d->d_ino != 0)
      printf ("%s\n", d->d_name);
  }
  closedir (dp);

  return (0);
}
