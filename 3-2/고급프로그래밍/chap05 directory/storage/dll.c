//
// FILE : tds.c - Tagged Data Storing Program
//
// This program uses the Doubly-Linked List routines.
//
/* All copyrights reserved by Bokyun Na, bkna@besta.cc */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dll.h"

extern int dmr_clear_superdir (char *fullpath);


DLL *dll_make_list_sort (DLL *i, DLL *top)
{
  DLL *old, *p;

  if (last == NULL) {		// first element in list
    i->next = NULL;
    i->prev = NULL;
    last = i;
    return i;
  }

  p = top;
  old = NULL;

  while (p) {
    if (atol(p->date) < atol(i->date)) { // sorting order: "the smaller the closer to first"
      old = p;
      p = p->next;
    }
    else if (atol(p->date) == atol(i->date)) {
      int ret = strcmp (p->fullpath, i->fullpath);
      if (!ret) {
	free (i);
	return first;
      }
      else if (ret < 0) {
	old = p;
	p = p->next;
      }
      else {
	if (p->prev) {
	  p->prev->next = i;
	  i->next = p;
	  i->prev = p->prev;
	  p->prev = i;
	  return top;
	}
	i->next = p;		// new first element
	i->prev = NULL;
	p->prev = i;
	return i;
      }
    }
    else {
      if (p->prev) {
	p->prev->next = i;
	i->next = p;
	i->prev = p->prev;
	p->prev = i;
	return top;
      }
      i->next = p;		// new first element
      i->prev = NULL;
      p->prev = i;
      return i;
    }
  }
  old->next = i;					// put on end
  i->next = NULL;
  i->prev = old ;
  last = i;

  return first;
}


/* Display a directory */

void dll_display (DLL *info)
{
  printf ("%s\n", info->date);
  printf ("%s\n", info->fullpath);
}


// display dll list on the screen 

void dll_show_list (DLL *first)
{
  DLL *info;

  info = first;
  while (info) {
    dll_display (info);
    info = info->next;
  }
}


/* Save the list to a disk file */

int dll_store_to_file (DLL *first)
{
  DLL *info = NULL;
  FILE *fp;

  if (!(fp = fopen(".besta.slf", "w+"))) {
    printf("Cannot open File.\n");
    return 1;
  }
  info = first;
  while (info) {
    fwrite (info, sizeof (DLL), 1, fp);
    info = info->next;		// get next element
  }
  fclose (fp);
  return 0;
}


/* Load the list from disk file */

int dll_load_from_file (DLL *first, DLL *last)
{
  DLL *info, *temp = NULL;
  FILE *fp;

  if ((fp = fopen (".besta.slf", "rb")) == NULL) {
    printf ("can't open file\n");
    return 1;
  }

  first = (DLL *) malloc (sizeof (DLL));
  if (!first) {
    printf ("out of memory\n");
    return 1; 
  }

  info = first;
  while (!feof (fp)) {
    if (fread (info, sizeof (DLL), 1, fp) != 1) 
      break;

    /* get memory for next */
    info->next = (DLL *) malloc (sizeof (DLL));
    if (!info->next) {
      printf ("out of memory\n");
      return 0;
    }
    info->prev = temp;
    temp = info;
    info = info->next;

  }

  temp->next = NULL;		// last entry
  last = temp;

  first->prev = NULL;
  fclose (fp);

  return 0;
}


DLL *dll_find (char *date)//, DLL *first)
{
  DLL *info;
  info = first;

  while (info) {
    if (!strcmp (date, info->date))
      return info;
    info = info->next;		// get next DLL list
  }
  return NULL;			// not found
}


void dmr_delete_dir (char *date)
{
  DLL *info;
  char d[128];

  info = dll_find (date);
  if (info) {
    sprintf (d, "rm -rf %s", info->fullpath);	// rmove target directory
    system (d);
    dmr_clear_superdir (info->fullpath);

    if (first == info) {
      first = info->next;
      if (first) first->prev = NULL;
      else last = NULL;
    }
    else {
      info->prev->next = info->next;
      if (info != last)
	info->next->prev = info->prev;
      else
	last = info->prev;
    }
    free (info);		// return memory to system
  }
}
