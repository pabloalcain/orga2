/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"
/* Atributos paginas */
/* -------------------------------------------------------------------------- */

void mmu_mapear_pagina(uint virtual, uint *cr3, uint fisica, uint attrs) {
  /* De los 32 bits de la direccion de memoria virtual, los 10 bits
     mas altos son la entrada en la el directorio de pagina, los
     siguientes 10 son la entrada en la tabla de paginas y los ultimos
     12 son la posicion dentro de la página de 4kb */
  int pde = (virtual & 0xFFC00000) >> 22;
  int pte = (virtual & 0x003FF000) >> 12;
  //int off = virtual & 0x00000FFF;
  int *idx_table = (int *) *(cr3 + pde);
  int *idx_page = idx_table + pte*4;
  *idx_page = fisica;
}

uint mmu_inicializar_dir_kernel() {
  uint pagina[1024] __attribute__((aligned(4096)));
  uint *cr3 = (uint *) rcr3();
  int i;
  /* a cero todas las entradas del PD */
  for (i = 0; i < 1024; ++i) {
    cr3[i] = 0x00000002;
  }
  cr3[0] = (uint) pagina | 3;
  for (i = 0; i < 1024; ++i) {
    mmu_mapear_pagina(0x1000*i, cr3, 0x1000*i, 0x3);
  }
  return 1;
}
      
  
  

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
