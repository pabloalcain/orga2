#include "stdlib.h"
#include "stdio.h"

extern void imprime_parametros(int a, double f, char* s);

int main(int argc, char* argv[]) {
  int a;
  double f;
  char *s;
  if (argc != 4) {
    fprintf(stderr, "usage: %s a f s\n", argv[0]);
    return 1;
  }
  a = atoi(argv[1]);
  f = atof(argv[2]);
  s = argv[3];
  imprime_parametros(a, f, s);
  return 0;
}
