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

void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs) {
  /* De los 32 bits de la direccion de memoria virtual, los 10 bits
     mas altos son la entrada en la el directorio de pagina, los
     siguientes 10 son la entrada en la tabla de paginas y los ultimos
     12 son la posicion dentro de la página de 4kb */
  pde *page_dir = (pde *) cr3;
  int pdidx = (virtual & 0xFFC00000) >> 22;
  int ptidx = (virtual & 0x003FF000) >> 12;
  //int off = virtual & 0x00000FFF;
  pte *page_table; 
  page_table = (pte *)(uint) (page_dir[pdidx].address);
  page_table[ptidx].address = fisica;
}

uint mmu_inicializar_dir_kernel() {
  pde *page_dir = (pde *) PAGE_DIR; //page_dir apunta al directorio definido
  int i;
  /* a cero todas las entradas del PD */
  for (i = 0; i < 1024; ++i) {
    page_dir[i].address = 0x0;
    page_dir[i].free = 0x0;
    page_dir[i].global = 0x0;
    page_dir[i].page_size = 0x0;
    page_dir[i].ignored = 0x0;
    page_dir[i].accessed = 0x0;
    page_dir[i].cache_dis = 0x0;
    page_dir[i].write_thru = 0x0;
    page_dir[i].user_sup = 0x0;
    page_dir[i].read_write = 0x1;
    page_dir[i].present = 0x0;
    /* Corto: page_dir[i] = 0x00000002; // Address a 0, r/w
     */
  }
  uint cr3 = (uint) page_dir;
  page_dir[0].address = PAGE_TABLE >> 12; //first page
  page_dir[0].present = 0x1;
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
