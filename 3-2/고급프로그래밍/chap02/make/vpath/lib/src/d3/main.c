
#include <stdio.h>

extern void func1();
extern void func2();
extern void func3();
extern void func4();


int main ()
{
  fprintf (stdout, "main func. \n");

  func1 ();
  func2 ();
  func3 ();
  func4 ();

  return 0;
}
