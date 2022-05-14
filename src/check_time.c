#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime.h>

#include "LRU_K.h"

#define K 1

int main() {
  int hits, len_cache, number_pages;
  clock_t start, end;
  
  read_number(&len_cache);
  read_number(&number_pages);

  start = clock();

  hits = lru_k(len_cache, number_pages, K);

  end = clock();

  printf("Hits: %d\n", hits);
  printf("Working hours: %f\n", difftime(end, start) / (CLOCKS_PER_SEC));
  printf("Probability of hitting the cache: %f\n", (float)hits / number_pages);
}