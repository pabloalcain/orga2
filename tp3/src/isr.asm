; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

msg0: db 'Int 0: Division by zero'
len0 equ $ - msg0
msg1: db 'Int 1: Debugger'
len1 equ $ - msg1
msg2: db 'Int 2: Non-maskable'
len2 equ $ - msg2
msg3: db 'Int 3: Breakpoint'
len3 equ $ - msg3
msg4: db 'Int 4: Overflow'
len4 equ $ - msg4
msg5: db 'Int 5: Bounds'
len5 equ $ - msg5
msg6: db 'Int 6: Invalid Opcode'
len6 equ $ - msg6
msg7: db 'Int 7: Coprocessor not available'
len7 equ $ - msg7
msg8: db 'Int 8: Double fault'
len8 equ $ - msg8
msg9: db 'Int 9: Coprocessor segment overrun'
len9 equ $ - msg9
msg10: db 'Int 10: Invalid Task State Segment'
len10 equ $ - msg10
msg11: db 'Int 11: Segment not present'
len11 equ $ - msg11
msg12: db 'Int 12: Stack fault'
len12 equ $ - msg12
msg13: db 'Int 13: General protection fault'
len13 equ $ - msg13
msg14: db 'Int 14: Page fault'
len14 equ $ - msg14
msg15: db 'Int 15: reserved'
len15 equ $ - msg15
msg16: db 'Int 16: Math fault'
len16 equ $ - msg16
msg17: db 'Int 17: Alignment check'
len17 equ $ - msg17
msg18: db 'Int 18: Machine check'
len18 equ $ - msg18
msg19: db 'Int 19: SIMD floating point exception'
len19 equ $ - msg19
;; PIC
extern fin_intr_pic1

;; Sched
extern sched_atender_tick
extern sched_tarea_actual


;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
  mov eax, %1
  imprimir_texto_mp msg%1, len%1, 0x07, 0, 0
  jmp $
%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
 
;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO;
; -------------------------------------------------------------------------- ;;

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
