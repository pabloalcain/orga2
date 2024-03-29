  ; ** por compatibilidad se omiten tildes **
  ; ==============================================================================
  ; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
  ; ==============================================================================

%include "imprimir.mac"
extern GDT_DESC
extern IDT_DESC
  
extern game_inicializar
extern screen_inicializar
extern idt_inicializar

extern mmu_inicializar_dir_kernel
extern mmu_inicializar
extern mmu_inicializar_memoria_perro
global start


;; Saltear seccion de datos
  jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
  PAGE_DIR equ 0x27000
  iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
  iniciando_mr_len equ    $ - iniciando_mr_msg

  iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
  iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
  ; Deshabilitar interrupciones
  cli

  ; Cambiar modo de video a 80 X 50
  mov ax, 0003h
  int 10h ; set mode 03h
  xor bx, bx
  mov ax, 1112h
  int 10h ; load 8x8 font

  ; Imprimir mensaje de bienvenida
  imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0


  ; Habilitar A20
  call habilitar_A20
  
  ; Cargar la GDT
  lgdt [GDT_DESC]
  ; Setear el bit PE del registro CR0
  mov eax, cr0
  or al, 1
  mov cr0, eax
  ; Saltar a modo protegido
  jmp (0x08*8):modoprotegido

modoprotegido:
BITS 32
  ; Establecer selectores de segmentos
  mov ax, (0x9*8)
  mov ds, ax
  mov ax, (0xB*8)
  mov es, ax
  ;mov ax, (0xC*8)
  mov gs, ax
  mov ss, ax
  
  mov ax, (0xC*8)
  mov fs, ax

  ; Establecer la base de la pila
  mov ebp, 0x27000
  mov esp, ebp

  ; Imprimir mensaje de bienvenida
  imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0
  ; Inicializar el juego
  call game_inicializar

  ; Inicializar pantalla
  xor ebx, ebx
  limpiar_pantalla:
    mov byte [fs:2*ebx], 'H'    ; caracter
    mov byte [fs:2*ebx+1], 0x1F  ; modo
    inc ebx
    cmp ebx, 4000               ; 80x50 = 4000
  jb limpiar_pantalla

  call screen_inicializar

  ; Inicializar la IDT
  call idt_inicializar

  ; Cargar IDT
  lidt [IDT_DESC]




  ; Inicializar el manejador de memoria

  call mmu_inicializar
  ; Inicializar el directorio de paginas
  call mmu_inicializar_dir_kernel

  ; Cargar directorio de paginas
  mov eax, PAGE_DIR
  mov cr3, eax

  ; Habilitar paginacion
  mov eax, cr0
  or eax, 0x80000000
  mov cr0, eax

  ; Inicializar tss

  ; Inicializar tss de la tarea Idle
  ; Inicializar el scheduler

  ; Configurar controlador de interrupciones

  ; Inicializar la IDT
  call idt_inicializar

  ; Cargar IDT
  lidt [IDT_DESC]

  ; Cargar tarea inicial

  ; Habilitar interrupciones

  ; Saltar a la primera tarea: Idle

  ; Ciclar infinitamente (por si algo sale mal...)
  mov eax, 0xFFFF
  mov ebx, 0xFFFF
  mov ecx, 0xFFFF
  mov edx, 0xFFFF
  jmp $
  jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
