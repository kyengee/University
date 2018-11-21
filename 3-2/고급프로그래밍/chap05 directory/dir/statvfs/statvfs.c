/* fsys -- 화일 시스템 정보를 프린트한다. */
/* 화일 시스템 이름이 인수로 전달된다. */
#include <sys/statvfs.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv)
{
  struct statvfs buf;

  if (argc != 2) {
    fprintf (stderr, "usage: fsys filename\n");
    exit (1);
  }
  if (statvfs (argv[1], &buf) !=0) {
    fprintf (stderr, "statvfs error\n");
    exit (2);
  }
  printf ("%s:\tfree blocks %d\tfree inodes %d\n", argv[1], buf.f_bfree, buf.f_ffree);

  return 0;
}
