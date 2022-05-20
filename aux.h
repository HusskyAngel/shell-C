#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

# ifndef __aux__ 
# define __aux__

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, int element);
void freeArray(Array *a);
#endif