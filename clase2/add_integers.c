#include "stdlib.h"
#include "stdio.h"

extern int iadd(int a, int b);

int main(int argc, char* argv[]) {
  int a, b, c;
  if (argc != 3) {
    fprintf(stderr, "usage: %s a b\n", argv[0]);
    return 1;
  }
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  c = iadd(a, b);
  printf("%i + %i = %i\n", a, b, c);
  return 0;
}
