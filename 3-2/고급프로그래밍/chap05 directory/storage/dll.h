//
/* Dlinkedlist.h - structures for Doubly Linked List */
//
// Bokyun Na, bkna@besta.cc
//

#ifndef DLL_H
#define DLL_H


/* Declarations of Data Structures */

struct dllist {
  char fullpath[128];	   /* contains full pathname for every file */
  char date[64];           /* contains year month day in a unit like 20030106 */ 

  struct dllist *prev;	/* previous list */
  struct dllist *next;	/* next list */
};
typedef struct dllist DLL ;


/* Declarations of Global variables */

DLL *first, *last;


/* Declarations of Function Prototypes */

DLL *dll_make_list_sort (DLL *i, DLL *first);
void dll_display (DLL *info);
void dll_show_list (DLL *first);
int dll_store_to_file (DLL *first);
int dll_load_from_file (DLL *first, DLL *last);
DLL *dll_find (char *date); 
void dmr_delete_dir (char *date); 

#endif 
