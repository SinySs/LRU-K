#ifndef LRU_K_H_INCLUDED
#define LRU_K_H_INCLUDED

#include "Doubly_connected_list.h"
#include "HashTable.h"

#define relative_hash_table_size 0.1

struct list_LRU {
  struct List *list;
  struct list_elem *inf;
};

/*! checks for the presence of an element in the cache and hash table
 * adds an element to the hash table if it is not there
 * adds an item to the cache
 * \param[out] 1 if elem in cache 0 if out
 */
int LRU_step(struct list_LRU *cache, struct hash_map *hash_table, int page,
             int page_num, int len_cache, int K);

struct list_LRU *create_list_LRU();

int read_number(int *number);

int lru_k(int len_cache, int number_pages, int K);

/*! search place to insert an element
 * \param[out] cache list element
 */
struct list_elem *search_place(struct list_LRU *cache, struct hash_map *table,
                               int page);

/*!inserts an element that is not in the hash table and not in the cache
 * \param[out] cache list element
 */
struct list_elem *push_elem_first(struct list_LRU *cache,
                                  struct hash_map *table, int page,
                                  int len_cache, int k);

/*! if the cache length is greater than the maximum size, then deletes the last
 * element */
void correct_len(struct list_LRU *cache, struct hash_map *table, int len_cache);

/*! determines whether there were calls to the element*/
int check_INF_status(struct hash_map *table, int page, int k);

void destruct_list_LRU(struct list_LRU *list);

#endif // LRU_K_H_INCLUDED
