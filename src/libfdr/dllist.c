
#include <stdio.h>    /* Basic includes and definitions */
#include "dllist.h"

/*---------------------------------------------------------------------*
 * PROCEDURES FOR MANIPULATING DOUBLY LINKED LISTS
 * Each list contains a sentinal node, so that
 * the first item in list l is l->flink.  If l is
 * empty, then l->flink = l->blink = l.
 *---------------------------------------------------------------------*/

Dllist new_dllist()
{
  Dllist d;

  d = (Dllist) malloc (sizeof(struct dllist));
  d->flink = d;
  d->blink = d;
  return d;
}

dll_insert_b(Dllist node, Jval v)       /* Inserts before a given node */
{
  Dllist newnode;

  newnode = (Dllist) malloc (sizeof(struct dllist));
  newnode->val = v;

  newnode->flink = node;
  newnode->blink = node->blink;
  newnode->flink->blink = newnode;
  newnode->blink->flink = newnode;
}

dll_insert_a(Dllist n, Jval val)        /* Inserts after a given node */
{
  dll_insert_b(n->flink, val);
}

dll_append(Dllist l, Jval val)     /* Inserts at the end of the list */
{
  dll_insert_b(l, val);
}

dll_prepend(Dllist l, Jval val)    /* Inserts at the beginning of the list */
{
  dll_insert_b(l->flink, val);
}


dll_delete_node(Dllist node)		/* Deletes an arbitrary iterm */
{
  node->flink->blink = node->blink;
  node->blink->flink = node->flink;
  free(node);
}

dll_empty(Dllist l)
{
  return (l->flink == l);
}
 
free_dllist(Dllist l)
{
  while (!dll_empty(l)) {
    dll_delete_node(dll_first(l));
  }
  free(l);
}

Jval dll_val(Dllist l)
{
  return l->val;
}
