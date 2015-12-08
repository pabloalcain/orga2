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
  uint *page_table; /* podemos hacerlo un puntero a pte, pero prefiero
                       mantener la aridad de la funcion de la catedra */
  int pdidx = (virtual >> 22) & 0x03FF; /* last 10 binary digits */
  int ptidx = (virtual >> 12) & 0x03FF;
  page_table = (uint *) (uint)(page_dir[pdidx].address << 12);
  page_table[ptidx] = fisica | attrs;
}

uint mmu_inicializar_dir_kernel() {
  pde* page_directory = (pde*) PAGE_DIR;
  //uint* page_directory = (uint*) PAGE_DIR;
  
  int i;
  for (i = 0; i < 1024; i++) {
    page_directory[i].address = 0x0;
    page_directory[i].free = 0x0;
    page_directory[i].global = 0x0;
    page_directory[i].page_size = 0x0;
    page_directory[i].ignored = 0x0;
    page_directory[i].accessed = 0x0;
    page_directory[i].cache_dis = 0x0;
    page_directory[i].write_thru = 0x0;
    page_directory[i].user_sup = 0x0;
    page_directory[i].read_write = 0x1;
    page_directory[i].present = 0x0;
  }
  pte* first_page_table = (pte*) PAGE_TABLE;
  page_directory[0].address = (uint)first_page_table >> 12;
  for (i = 0; i < 1024; i++) {
    mmu_mapear_pagina(i * 0x1000, (uint) page_directory, i * 0x1000, 3);
  }
  page_directory[0].address = (uint)first_page_table >> 12;
  page_directory[0].read_write = 1;
  page_directory[0].present = 1; 
  
  return 1;
}
      
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
  pde *page_dir = (pde *) cr3;
  pte *page_table;
  int pdidx = (virtual >> 22) & 0x03FF; /* last 10 binary digits */
  int ptidx = (virtual >> 12) & 0x03FF;
	pde pdentry = page_dir[pdidx];     /* Ir a la entrada dentro del page directory*/
  pte ptentry;
	if (! pdentry.present) {
		return;
	}
	page_table = (pte *) (pdentry.address << 12);
	ptentry = page_table[ptidx];
	if (ptentry.present) {
		/* Si la entrada buscada está en el page directory */
		ptentry.present = 0;
		tlbflush();	
	}
}
  
  

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */
