#include "stdlib.h"
#include "stdio.h"

extern double dadd(double x, double y);

int main(int argc, char* argv[]) {
  double x, y, z;
  if (argc != 3) {
    fprintf(stderr, "usage: %s x y\n", argv[0]);
    return 1;
  }
  x = atof(argv[1]); 
  y = atof(argv[2]); 
  z = dadd(x, y);
  printf("%f + %f = %f\n", x, y, z);
  return 0;
}
