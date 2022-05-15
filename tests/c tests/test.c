#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "LRU_K.h"

#define K 3

int main() {
  int hits, len_cache, number_pages, answer;

  FILE *answers = fopen("../python tests/lru-1/answers.txt", "r");
  FILE *data = fopen("../python tests/lru-1/data.txt", "r");

  switch (K) {
  case 1:
    answers = fopen("../python tests/lru-1/answers.txt", "r");
    data = fopen("../python tests/lru-1/data.txt", "r");
    break;
  case 2:
    answers = fopen("../python tests/lru-2/answers.txt", "r");
    data = fopen("../python tests/lru-2/data.txt", "r");
    break;
  case 3:
    answers = fopen("../python tests/lru-3/answers.txt", "r");
    data = fopen("../python tests/lru-3/data.txt", "r");
    break;
  default:
    printf("Tests not exist!\n");
    abort();
    break;
  }

  for (int i = 0; i < 5; i++) {
    read_number(&answer, answers);

    read_number(&len_cache, data);
    read_number(&number_pages, data);

    hits = lru_k(len_cache, number_pages, K, data);

    if (hits == answer)
      printf("Congratulations!\n");
    else
      printf("Failed!\n");
  }

  fclose(answers);
  fclose(data);

  return 0;
}
