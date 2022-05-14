#include "LRU_K.h"

int check_INF_status(struct hash_map *table, int page, int k) {
  if (table->hash_table[page].history->size == k)
    return 0;

  return 1;
}

struct list_elem *push_elem_first(struct list_LRU *cache,
                                  struct hash_map *table, int page,
                                  int len_cache) {
  struct list_elem *new_elem;
  if (cache->inf == NULL) {
    new_elem = push_tail(cache->list, page);
  } else if(table->hash_table[cache->list->head->data].history->size == 1) {
    new_elem = push_head(cache->list, page);
  } else if(cache->list->size < len_cache){
    new_elem = push_tail(cache->list, page);
  } else {
      new_elem = push_before(cache->list, cache->inf, page);
  }
  cache->inf = new_elem;

  if (cache->list->size > len_cache) {
    table->hash_table[cache->list->tail->data].status = OUT;
    delete_tail(cache->list);
  }

  return new_elem;
}

struct list_LRU *create_list_LRU() {
  struct list_LRU *new_list = calloc(1, sizeof(struct list_LRU));
  new_list->list = create_list();
  new_list->inf = new_list->list->head;

  return new_list;
}

void destruct_list_LRU(struct list_LRU *list) {
  assert(list);
  delete_list(list->list);
  free(list);
}

struct list_elem *search_place(struct list_LRU *cache, struct hash_map *table,
                               int page) {

  struct list_elem *current = cache->list->head;

  for (int i = 0; i < cache->list->size; i++) {
    if (current->data == cache->inf->data)
      return current;

    if (table->hash_table[current->data].history->tail->data <=
        table->hash_table[page].history->tail->data) {
      return current;
    }

    current = current->next;
  }

  return cache->list->tail;
}

int LRU_step(struct list_LRU *cache, struct hash_map *table, int page,
             int page_num, int len_cache, int K) {
  assert(cache);
  assert(table);

  if (check_if_in_hash_map(table, page) == OUT) {

    struct list_elem *new_elem = push_elem_first(cache, table, page, len_cache);
    hash_map_insert(table, page, page_num, IN, new_elem, K);
    return 0;

  } else {
    change_history(table->hash_table[page].history, page_num, K);

    if (check_INF_status(table, page, K) == 1) {

      if (check_if_in_cache(table, page) == OUT) {
        struct list_elem *new_elem =
            push_elem_first(cache, table, page, len_cache);
        table->hash_table[page].cache_elem = new_elem;
        table->hash_table[page].status = IN;
        return 0;

      } else {
        if (cache->inf->data == table->hash_table[page].cache_elem->data)
          return 1;

        insert_elem(cache->list, table->hash_table[page].cache_elem,
                    cache->inf);
        cache->inf = cache->inf->prev;
        if (cache->list->size > len_cache) {
          table->hash_table[cache->list->tail->data].status = OUT;
          delete_tail(cache->list);
        }
        return 1;
      }

    } else {
      if (check_if_in_cache(table, page) == OUT) {
        struct list_elem *search = search_place(cache, table, page);
        struct list_elem *new_elem = push_before(cache->list, search, page);
        table->hash_table[page].cache_elem = new_elem;
        table->hash_table[page].status = IN;

        if (cache->list->size > len_cache) {
          table->hash_table[cache->list->tail->data].status = OUT;
          if (cache->list->tail->data == cache->inf->data)
            cache->inf = cache->inf->prev;
          delete_tail(cache->list);
        }
        return 0;

      } else {
        struct list_elem *search = search_place(cache, table, page);
        if (search->data == table->hash_table[page].cache_elem->data)
          return 1;

        if (cache->inf->data == table->hash_table[page].cache_elem->data)
          cache->inf = cache->inf->prev;

        insert_elem(cache->list, table->hash_table[page].cache_elem, search);
        return 1;
      }
    }
    return 1;
  }

  return 0;
}

int lru_k(int len_cache, int number_pages, int K) {
  int len_hash_table, page, hits;
  struct list_LRU *cache;
  struct hash_map *table =
      (struct hash_map *)calloc(1, sizeof(struct hash_map));
  hits = 0;

  len_hash_table = relative_hash_table_size * number_pages;

  cache = create_list_LRU();
  hash_map_construct(table, 10);

  for (int count_pages = 0; count_pages < number_pages; count_pages++) {
    read_number(&page);

    hits += LRU_step(cache, table, page, count_pages, len_cache, K);
    print_list(cache->list);
  }

  destruct_list_LRU(cache);
  hash_map_destruct(table);

  return hits;
}

int read_number(int *number) {
  int scan;

  scan = scanf("%d", number);

  assert(scan && "Input Error");

  if ((*number) < 0) {
    scan = 0;
    assert(scan && "Wrong format");
  }

  return 0;
}
