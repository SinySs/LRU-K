#include "Doubly_connected_list.h"

//#define Test

struct List *create_list() {
  struct List *list = calloc(1, sizeof(struct List));
  list->size = 0;

  return list;
}

struct list_elem *create_elem(int data) {
  struct list_elem *new_elem;

  new_elem = malloc(sizeof(struct list_elem));
  new_elem->data = data;
  new_elem->next = NULL;
  new_elem->prev = NULL;

  return new_elem;
}

struct list_elem *first_push(struct List *list, int data) {
  assert(list);
  assert(list->size == 0);

  list->head = create_elem(data);
  list->tail = list->head;
  list->size++;

  return list->head;
}

struct list_elem *push_head(struct List *list, int data) {
  assert(list);

  if (list->size == 0) {
    return first_push(list, data);
  }

  struct list_elem *new_elem;
  new_elem = create_elem(data);

  new_elem->next = list->head;
  list->head->prev = new_elem;
  list->head = new_elem;
  list->size++;

  return new_elem;
}

struct list_elem *push_tail(struct List *list, int data) {
  assert(list);

  if (list->size == 0) {
    return first_push(list, data);
  }

  struct list_elem *new_elem;
  new_elem = create_elem(data);

  new_elem->prev = list->tail;
  list->tail->next = new_elem;
  list->tail = new_elem;
  list->size++;

  return new_elem;
}

struct list_elem *push_after(struct List *list, struct list_elem *elem,
                             int data) {
  assert(list);
  assert(elem);

  if (elem == list->tail) {
    return push_tail(list, data);
  }

  struct list_elem *new_elem;

  new_elem = create_elem(data);
  new_elem->next = elem->next;
  new_elem->prev = elem;
  elem->next = new_elem;
  new_elem->next->prev = new_elem;
  list->size++;

  return new_elem;
}

void delete_tail(struct List *list) {
  assert(list);
  if (list->size > 1) {
    list->tail = list->tail->prev;
    free(list->tail->next);
  } else {
    free(list->tail);
  }

  list->size--;
}

struct list_elem *push_before(struct List *list, struct list_elem *elem,
                              int data) {
  assert(list);

  if (list->size == 0) {
    return first_push(list, data);
  }

  if (elem->data == list->head->data) {
    return push_head(list, data);
  }

  struct list_elem *new_elem;

  new_elem = create_elem(data);
  new_elem->next = elem;
  new_elem->prev = elem->prev;
  elem->prev = new_elem;
  new_elem->prev->next = new_elem;
  list->size++;

  return new_elem;
}

void delete_list(struct List *list) {
  assert(list);

  struct list_elem *current = list->head;

  for (int i = 0; i < list->size - 1; i++) {
    current = current->next;
    free(current->prev);
  }
  free(current);
}

void delete_head(struct List *list) {
  assert(list);
  list->head = list->head->next;
  free(list->head->prev);

  list->size--;
}

void delete_elem(struct List *list, struct list_elem *elem) {
  assert(list);
  assert(elem);

  if (elem == list->head) {
    delete_head(list);
    return;
  }

  if (elem == list->tail) {
    delete_tail(list);
    return;
  }
  elem->next->prev = elem->prev;
  elem->prev->next = elem->next;
  list->size--;

  free(elem);
}

//! insert first elem from list before second
void insert_elem(struct List *list, struct list_elem *first,
                 struct list_elem *second) {
  if (second->data == first->data)
    return;

  if (second->data == list->head->data) {
    insert_head(list, first);
    return;
  }

  if (first->data != list->tail->data) {
    first->next->prev = first->prev;
  } else {
    list->tail = first->prev;
  }

  first->prev->next = first->next;

  first->prev = second->prev;
  first->next = second;
  second->prev->next = first;
  second->prev = first;
}

void insert_head(struct List *list, struct list_elem *elem) {
  assert(list);
  assert(elem);

  if (elem->data == list->head->data)
    return;

  if (elem->data == list->tail->data) {
    elem->prev->next = NULL;
    list->tail = elem->prev;
  } else {
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
  }

  elem->prev = NULL;
  elem->next = list->head;
  list->head->prev = elem;
  list->head = elem;
}

void print_list(struct List *list) {
  struct list_elem *current = list->head;
  printf("Start of printing list:\n");
  printf("Size %d\n", list->size);

  for (int i = 0; i < list->size; i++) {
    printf("%d ", current->data);
    current = current->next;
  }

  printf("\nEnd of printing list.\n");

  printf("Head: %d Tail: %d\n", list->head->data, list->tail->data);
}
#ifdef Test
int main() {
  struct List *new_list;
  struct list_elem *a;
  struct list_elem *b;
  struct list_elem *c;

  new_list = create_list();

  a = push_head(new_list, 8);
  push_head(new_list, 10);
  push_tail(new_list, 2);

  b = push_after(new_list, a, 4);
  push_after(new_list, new_list->tail, -1);
  print_list(new_list);

  push_before(new_list, b, 5);
  push_before(new_list, new_list->head, 12);
  c = push_head(new_list, 100);
  print_list(new_list);

  delete_tail(new_list);
  delete_tail(new_list);
  print_list(new_list);

  insert_elem(new_list, b, a);
  print_list(new_list);

  delete_list(new_list);

  return 0;
}

#endif // Test
