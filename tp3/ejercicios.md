# Paso a paso de los ejercicios del TP3

## Ejercicio 1: GDT

Para llenar la GDT hay que hacer dos cuentas: primero que nada, los
500 MB = 512000 KB los partimos de forma pareja entre los cuatro
segmentos: 500 MB / 4 = 125 MB = 125 * 2^20 b = 125 * 16^5 =
0x7D0000. Así, tenemos la entrada para cada uno de los Descriptors:


1. KERN_DATA = 0x0
2. KERN_CODE = 0x07D0000
3. USER_DATA = 0x0FA00004. USER_CODE = 0x1770000


Los últimos 4 números son Base 0:15, los siguientes 2 son Base 16:23 y
finalmente los otros 2 son Base 24:31. Para el límite, tenemos que
partir los 125 MB que ocupa cada segmento en páginas de 4kb (si no,
no podemos direccionar los 500 Mb de memoria): 125 MB / 4kB
= 3200. Así, la última página que está ocupada es la 3199 =
C7F. Luego, Limit 0:15 es C7F y Limit 16:19 es 0.

Finalmente, los flags. Los que dependen del segmento son:

1. KERN_DATA : Privil = 0; Ex = 0
2. KERN_CODE : Privil = 0; Ex = 1
3. USER_DATA : Privil = 3; Ex = 0
4. USER_CODE : Privil = 3; Ex = 1

A partir de aquí podemos obtener el "tipo" con la tabla 3-1 de Intel
en el manual del desarrollador vol. 3 parte A.

Los que son iguales para todos:

- Pr = 1
- DC = 0
- RW = 1
- Ac = 0
- Gr = 0
- Sz = 1

Finalmente, tenemos que agregar el área de video (en el índice 0xC)
como parte de la GDT. El área de video comienza en 0xB8000 y es de
80x50. Si ahora movemos el segmento a 0xC podemos imprimir un texto y
además limpiar la pantalla. Usando fs como base, la rutina de limpiar
pantalla es simplemente recorrer los 80x50=4000 píxeles y pintarlos de
negro (NOTA: cada píxel tiene 2 bytes: el primero para el caracter
ASCII, el segundo para el modo). http://wiki.osdev.org/Text_UI muestra
bien cómo quedan los colorcitos =)

### Idea: CREAR MACRO PARA GDT

## Ejercicio 2: IDT

Hay una macro que funciona bien, a la que sólo hay que setearle el
atributo (que tampoco sé cómo hacerlo) y el segmento (que tiene que
ser el segmento de código del kernel). En esta macro espera el símbolo
_idtn, declarado en asm, al que referencia con & para obtener la
dirección. Por eso es importante definirla en asm. Es un poco oscuro,
pero sigue la lógica original de la cátedra. Por cada entrada tenemos:

- IDT_ENTRY(N, 0): En el código de C, `idt.c`
- _isrN: void function, declarada en `idt.h`
- _isrN: function definida en ASM a través de la macro ISR N

Después es cuestión de crear todas las entradas de idt. Finalmente hay
que tocar los handles en `isr.asm` para que quede escribiendo el
código de interrupción.
