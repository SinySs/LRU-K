#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "LRU_K.h"

#define K 5


int main() {
  int hits, len_cache, number_pages, answer;
  
  clock_t start, end;
  FILE *data = fopen("../tests/python tests/time tests/data.txt", "r");
  FILE *answers = fopen("../tests/python tests/time tests/answers.txt", "r");
 
  read_number(&answer, answers);
    
  read_number(&len_cache, data);
  read_number(&number_pages, data);
    
  printf("FOR K = %d:\n", K);
    
  start = clock();
    
  hits = lru_k(len_cache, number_pages, K, data);
    
  end = clock();
      
    
  printf("Hits: %d\n", hits);
  printf("Working hours: %f\n", difftime(end, start) / (CLOCKS_PER_SEC));
  printf("Probability of hitting the cache: %f\n", (float)hits / number_pages);
    

  fclose(answers);
  fclose(data);
  
  

  return 0;
}
