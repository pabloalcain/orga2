#include "stdlib.h"
#include "stdio.h"

extern int suma_parametros(int a0, int a1, int a2, 
                           int a3, int a4, int a5, 
                           int a6, int a7);

int main(int argc, char* argv[]) {
  int a0, a1, a2, a3, a4, a5, a6, a7;
  int result;

  a0 = 1; a1 = 2; a2 = 3; a3 = 4; 
  a4 = 5; a5 = 6; a6 = 7; a7 = 8;
  result = suma_parametros(a0, a1, a2, a3, a4, a5, a6, a7);
  printf("El resultado es: %i\n", result);
  return 0;
}
