#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "LRU_K.h"


int main() {
  int hits, len_cache, number_pages, answer;
  int K;
  clock_t start, end;
  FILE *data = fopen("../python tests/time tests/data.txt", "r");
  FILE *answers = fopen("../python tests/time tests/answers.txt", "r");
 
  for (int i = 0; i < 3; i++) {
    read_number(&answer, answers);
    data = fopen("../python tests/time tests/data.txt", "r");
    read_number(&len_cache, data);
    read_number(&number_pages, data);
    
    K = i + 1;
    
    start = clock();
    
    hits = lru_k(len_cache, number_pages, K, data);
    
    end = clock();
    
    if (hits == answer)
    {
      printf("Congratulations!\n");
    }
    else
    {
      printf("Failed!You need : %d\n", answer);
    }
      
    printf("FOR K = %d:\n", K);
    printf("Hits: %d\n", hits);
    printf("Working hours: %f\n", difftime(end, start) / (CLOCKS_PER_SEC));
    printf("Probability of hitting the cache: %f\n", (float)hits / number_pages);
    fclose(data);
  
  }

  fclose(answers);
  

  return 0;
}
