#include "kpu.h"


int func2 ()
{
  printf (" Dept. of Cybernetics\n");

  return 0;
}

int func3 ()
{
  printf (" %s\n", dept);

  func2 ();

  return 0;
}
