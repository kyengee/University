/* lookup -- 화일 제한의 현재값을 표시한다. */

#include <unistd.h>
#include <stdio.h>

typedef struct table_tag{
  int val;
  char *name;
} Table;

int main()
{
  Table *tb;
  static Table options[] = {
    { _PC_LINK_MAX, "Maximum number of links"},
    { _PC_NAME_MAX, "Maximum length of a filename"},
    { _PC_PATH_MAX, "Maximum length of pathname"},
    {-1, NULL}
  };
 
  for (tb=options; tb->name != NULL; tb++)
    printf ("%-28.28s\t%ld\n", tb->name, pathconf ("/tmp", tb->val));

  return 0;
}
