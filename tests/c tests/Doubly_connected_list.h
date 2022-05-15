/*!
 *This file contains a doubly linked list and functions for working with it.
 */

#ifndef DOUBLY_CONNECTED_LIST_H_INCLUDED
#define DOUBLY_CONNECTED_LIST_H_INCLUDED

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

struct list_elem {
  int data;

  struct list_elem *next;
  struct list_elem *prev;
};

struct List {
  struct list_elem *head;
  struct list_elem *tail;

  int size;
};

struct List *create_list();

struct list_elem *create_elem(int data);

struct list_elem *first_push(struct List *list, int data);

struct list_elem *push_head(struct List *list, int data);

struct list_elem *push_tail(struct List *list, int data);

struct list_elem *push_after(struct List *list, struct list_elem *elem,
                             int data);

struct list_elem *push_before(struct List *list, struct list_elem *elem,
                              int data);
void insert_head(struct List *list, struct list_elem *elem);

void delete_head(struct List *list);

void delete_tail(struct List *list);

void delete_list(struct List *list);

//! insert first elem from list before second
void insert_elem(struct List *list, struct list_elem *first,
                 struct list_elem *second);

void print_list(struct List *list);

#endif // DOUBLY_CONNECTED_LIST_H_INCLUDED
