/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Tipos basicos */
/* -------------------------------------------------------------------------- */
#define NULL                    0
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

/* Constantes basicas */
/* -------------------------------------------------------------------------- */
#define PAGE_SIZE               0x00001000
#define TASK_SIZE               4096

#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x00001200 /* direccion fisica de comienzo del kernel */


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_KERN_CODE           8
#define GDT_IDX_KERN_DATA           9
#define GDT_IDX_USER_CODE           10
#define GDT_IDX_USER_DATA           11
#define GDT_IDX_VIDEO               12

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Selectores de segmentos */
/* -------------------------------------------------------------------------- */

/* Paginacion */
/* -------------------------------------------------------------------------- */
#define PAGE_DIR       0x27000 /* direccion del page directory */
#define PAGE_TABLE     0x28000 /* direccion de la primera tabla */
#endif  /* !__DEFINES_H__ */
