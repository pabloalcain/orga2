/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"
#include "screen.h"


/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define ADDR_COD_TAREA_A1 		0x10000
#define ADDR_COD_TAREA_A2 		0x11000
#define ADDR_COD_TAREA_B1 		0x12000
#define ADDR_COD_TAREA_B2 		0x13000
#define ADDR_COD_TAREA_IDLE 	0x16000

/* Direcciones fisicas de directorios y tablas de paginas del KERNEL */
/* -------------------------------------------------------------------------- */

void **primer_pag_libre;
void **ultima_pag_libre;
void mmu_inicializar() {
  primer_pag_libre = (void **)0x100000;
  ultima_pag_libre = (void **)0x3ff000;
}

uint mmu_proxima_pagina_fisica_libre(){
	uint dir_pag_nueva = (uint) ultima_pag_libre;
	*ultima_pag_libre = (void*)((*ultima_pag_libre)-0x1000);		
	return dir_pag_nueva;
}

void mmu_mapear_pagina(uint virtual, uint cr3, uint fisica, uint attrs) {
  /* De los 32 bits de la direccion de memoria virtual, los 10 bits
     mas altos son la entrada en la el directorio de pagina, los
     siguientes 10 son la entrada en la tabla de paginas y los ultimos
     12 son la posicion dentro de la página de 4kb */
  uint *page_dir = (uint *) cr3;
  uint *page_table; /* podemos hacerlo un puntero a pte, pero prefiero
                       mantener la aridad de la funcion de la catedra */
  int pdidx = (virtual >> 22) & 0x03FF; /* last 10 binary digits */
  int ptidx = (virtual >> 12) & 0x03FF;
  pde *page_dir_str = (pde*) page_dir;
  pde pdentry = page_dir_str[pdidx];
  if (pdentry.present){
    page_table = (uint *) (uint)(pdentry.address << 12);
    } else {
    page_table = (uint *) mmu_proxima_pagina_fisica_libre();
    page_dir[pdidx] = (uint)page_table | attrs;
  }
  page_table[ptidx] = fisica | attrs;
  tlbflush(); /* Invalidar cache de traduccion de direcciones */
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
  page_directory[0].read_write = 1;
  page_directory[0].present = 1;
  for (i = 0; i < 1024; i++) {
    mmu_mapear_pagina(i* 0x1000, (uint) page_directory, i * 0x1000, 3);
  }
  //page_directory[0].address = (uint)first_page_table >> 12;
  
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
		ptentry.present = 0;
		tlbflush();	
	}
}
  
uint mmu_inicializar_memoria_perro(perro_t *perro, int index_jugador, int index_tipo) {
  uint dir_virtual_perro;
  uint dir_fisica_perro;
	uint dir_codigo_perro;
	uint attrs = 0x5; // U/S = 1 (User); R/W = 0 (Read only); P = 1 (present) 	
	uint cr3 = mmu_proxima_pagina_fisica_libre(); // Nuevo page directory para este perro
  int i;
  for(i = 0; i < 0x400; i++){
		mmu_mapear_pagina(i*0x1000, cr3, i*0x1000, 0x3);
	}
	if (index_jugador == JUGADOR_A) {
		dir_virtual_perro = 0x800000 + (VIDEO_COLS + 2) * 0x1000; // posicion en el mapa del perro del jugador 0
		dir_fisica_perro = 0x500000 + (VIDEO_COLS + 2) * 0x1000; // posicion en el mapa del perro del jugador 0
	} else {
		dir_virtual_perro = 0x800000 + ((VIDEO_COLS * (VIDEO_FILS - 1 )) - 2) * 0x1000; // posicion en el mapa del perro del jugador 1
		dir_fisica_perro = 0x500000 + ((VIDEO_COLS * (VIDEO_FILS - 1 )) - 2) * 0x1000; // posicion en el mapa del perro del jugador 1
	}

  mmu_mapear_pagina(dir_virtual_perro, cr3, dir_fisica_perro, attrs);

	if (index_jugador == JUGADOR_A && perro->tipo == TIPO_1)
		dir_codigo_perro = ADDR_COD_TAREA_A1;
	if (index_jugador == JUGADOR_A && perro->tipo == TIPO_2)
		dir_codigo_perro = ADDR_COD_TAREA_A2;
	if (index_jugador == JUGADOR_B && perro->tipo == TIPO_1)
		dir_codigo_perro = ADDR_COD_TAREA_B1;
	if (index_jugador == JUGADOR_B && perro->tipo == TIPO_2)
		dir_codigo_perro = ADDR_COD_TAREA_B2;

	cr3 = rcr3();
	lcr3(PAGE_DIR);
	for (i = 0; i < 1024; i++) {
		((uint *)dir_fisica_perro)[i] = ((uint *)dir_codigo_perro)[i];
	}
	lcr3(cr3);
	return cr3;
}
