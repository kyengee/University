
#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>

int list(const char *name, const struct stat *status, int type)
{
  /* ���� stat ȣ���� �����ϸ�, �׳� �����Ѵ�. */
  if (type == FTW_NS)
    return 0;
  /* �ƴϸ� ��ü �̸�, �㰡 �׸��� ���� ��ü�� ���丮�̰ų� ��¡�� ��ũ�̸� �ڿ� ��*���� ÷���Ѵ�. */
  if(type == FTW_F)
    printf("%-30s\t0%3o\n", name, status->st_mode&0777);
  else
    printf("%-30s*\t0%3o\n", name, status->st_mode&0777);

  return 0;
}

int main (int argc, char **argv)
{
  int list(const char *, const struct stat *, int);

  if (argc == 1)
    ftw (".", list, 1);
  else
    ftw (argv[1], list, 1);

  return 0;
}
