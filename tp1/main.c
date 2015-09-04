#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
void f (char* s) {
  if( s[0] != 0 ) s[0] = 'N';
}

int main (void){
  unsigned char l1, l2;
  char p1[] = "peron";
  char p2[] = "balbin";
  bool menor;
  l1 = palabraLongitud(p1);
  l2 = palabraLongitud(p2);
  printf("La longitud de %s es %d\n", p1, l1);
  printf("La longitud de %s es %d\n", p2, l2);
  menor = palabraMenor(p1, p2);
  printf("Es %s menor a %s? %d\n", p1, p2, menor);
  fputs("Formateo la palabra ", stdout);
  palabraImprimir(p1, stdout);
  fputs(": ", stdout);
  palabraFormatear(p1, f);
  palabraImprimir(p1, stdout);
  
  palabraImprimir(p1, stdout);
  palabraImprimir(p2, stdout);

  nodo *n1 = nodoCrear(palabraCopiar(p1));
  printf("La palabra del nodo es %s\n", n1->palabra);
  nodoBorrar(n1);

  lista *o1 = oracionCrear();
  insertarAtras(o1, palabraCopiar("1"));
  insertarAtras(o1, palabraCopiar("22"));
  insertarAtras(o1, palabraCopiar("1"));
  insertarAtras(o1, palabraCopiar("333"));
  insertarAtras(o1, palabraCopiar("444"));
  oracionImprimir(o1, "/dev/stdout", palabraImprimir);
  float lm1 = longitudMedia(o1);
  printf("Longitud media = %f\n", lm1);
  oracionBorrar(o1);

  lista *o2 = oracionCrear();
  oracionImprimir(o2, "/dev/stdout", palabraImprimir);
  insertarOrdenado(o2, palabraCopiar("1"), palabraMenor);
  insertarOrdenado(o2, palabraCopiar("333"), palabraMenor);
  insertarOrdenado(o2, palabraCopiar("22"), palabraMenor);
  insertarOrdenado(o2, palabraCopiar("1"), palabraMenor);
  insertarOrdenado(o2, palabraCopiar("444"), palabraMenor);
  oracionImprimir(o2, "/dev/stdout", palabraImprimir);
  float lm2 = longitudMedia(o2);
  printf("Longitud media = %f\n", lm2);
  oracionBorrar(o2);


  lista *miLista = oracionCrear();
  insertarOrdenado( miLista, palabraCopiar( "a" ), palabraMenor);
  insertarOrdenado( miLista, palabraCopiar( "b" ), palabraMenor);
  insertarOrdenado( miLista, palabraCopiar( "c" ), palabraMenor);
  insertarOrdenado( miLista, palabraCopiar( "d" ), palabraMenor);
  insertarOrdenado( miLista, palabraCopiar( "e" ), palabraMenor);
  insertarOrdenado( miLista, palabraCopiar( "f" ), palabraMenor);
  printf("SIN FILTRO:\n");
  oracionImprimir( miLista, "/dev/stdout", palabraImprimir);
  printf("MENSAJE DIABLOICO:\n");
  descifrarMensajeDiabolico( miLista, "/dev/stdout", palabraImprimir);

  filtrarPalabra( miLista, palabraMenor, "e" );
  printf("PRIMER FILTRO:\n");
  oracionImprimir( miLista, "/dev/stdout", palabraImprimir);
  filtrarPalabra( miLista, palabraIgual, "c" );
  printf("SEGUNDO FILTRO:\n");
  oracionImprimir( miLista, "/dev/stdout", palabraImprimir);

  oracionBorrar(miLista);

  // COMPLETAR AQUI EL CODIGO
  return 0;
}
