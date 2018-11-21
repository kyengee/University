// KPU.h
#ifndef __KPU_H
#define __KPU_H

#include <stdio.h>

//char *dept = "Dept. of Noiri Engineering";
extern char *dept;

int func1 ();
int func2 ();
int func3 ();

#else
extern char *dept;
extern int func1 ();
extern int func2 ();
extern int func3 ();

#endif //__KPU_H
