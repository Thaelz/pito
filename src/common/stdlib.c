#include <common/types.h>

void *memcpy(void *dest, void *src, size_t n)
{
  int i;
  char *d = dest; 
  char *s = src; 
  for( i=0 ; i<n ; i++) {
    *d++ = *s++;
  }
  return src;
}

void bzero(void *s, size_t n)
{
  int i;
  char *p = s;
  for( i=0 ; i<n ; i++) {
    *p++ = 0;
  }
}
