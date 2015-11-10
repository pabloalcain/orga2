/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"




/* Definicion de la GDT */
/* -------------------------------------------------------------------------- */

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    [GDT_IDX_KERN_CODE] = (gdt_entry) {
      .limit_0_15 = 0xC7F,
      .limit_16_19 = 0,
      .base_0_15 = 0x0,
      .base_16_23 = 0x0,
      .base_24_31 = 0x0,
      .type = 0xA,
      .s = 1,
      .dpl = 0,
      .p = 1,
      .avl = 1,
      .l = 0,
      .db = 1,
      .g = 1,
    },
    [GDT_IDX_KERN_DATA] = (gdt_entry) {
      .limit_0_15 = 0xC7F,
      .limit_16_19 = 0x0,
      .base_0_15 = 0x0,
      .base_16_23 = 0x00,//7D,
      .base_24_31 = 0x0,
      .type = 0x2,
      .s = 0x1,
      .dpl = 0x0,
      .p = 0x1,
      .avl = 0x1,
      .l = 0x0,
      .db = 0x1,
      .g = 0x1,
    },
    [GDT_IDX_USER_CODE] = (gdt_entry) {
      .limit_0_15 = 0xC7F,
      .limit_16_19 = 0x0,
      .base_0_15 = 0x0,
      .base_16_23 = 0x00,//FA,
      .base_24_31 = 0x0,
      .type = 0xA,
      .s = 0x1,
      .dpl = 0x0,
      .p = 0x1,
      .avl = 0x1,
      .l = 0x0,
      .db = 0x1,
      .g = 0x1,
    },
    [GDT_IDX_USER_DATA] = (gdt_entry) {
      .limit_0_15 = 0xC7F,
      .limit_16_19 = 0,
      .base_0_15 = 0,
      .base_16_23 = 0x00,//77,
      .base_24_31 = 0x00,//1,
      .type = 0x2,
      .s = 0x1,
      .dpl = 0x0,
      .p = 0x1,
      .avl = 0x1,
      .l = 0x0,
      .db = 0x1,
      .g = 0x1,
    },
    [GDT_IDX_VIDEO] = (gdt_entry) {
      .limit_0_15 = 0x8000,
      .limit_16_19 = 0x0,
      .base_0_15 = 0x8000,
      .base_16_23 = 0x0B,
      .base_24_31 = 0x0,
      .type = 0x2,
      .s = 0x1,
      .dpl = 0x0,
      .p = 0x1,
      .avl = 0x1,
      .l = 0x0,
      .db = 0x1,
      .g = 0x0,
    },
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};
